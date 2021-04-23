#include "FileZip.hpp"

#include "miniz.h"

#include <filesystem>
#include <algorithm>
#include <string>
#include <tuple>
#include <iostream>

Zip::EntriesMap Zip::entries;

Zip::Zip(const std::string& zipPath)
: fileName(zipPath)
{
    Zip::zipArchive = static_cast<mz_zip_archive*>(malloc(sizeof(mz_zip_archive)));
    memset(Zip::zipArchive, 0, sizeof(mz_zip_archive));
    
    mz_bool status = mz_zip_reader_init_file((mz_zip_archive*)Zip::zipArchive, zipPath.c_str(), 0);
    if (!status)
    {
        std::cout << "[Filesystem] Cannot open zip file: " + zipPath << std::endl;
    }
    
    for (mz_uint i = 0; i < mz_zip_reader_get_num_files((mz_zip_archive*)Zip::zipArchive); i++)
    {
        mz_zip_archive_file_stat file_stat;
        if (!mz_zip_reader_file_stat((mz_zip_archive*)Zip::zipArchive, i, &file_stat))
        {
            std::cout << "[Filesystem] Cannot read entry with index: " 
                    + std::to_string(i) + " from zip archive " + zipPath << std::endl;
            continue;
        }
        
        Zip::entries[file_stat.m_filename] = std::make_tuple(file_stat.m_file_index, file_stat.m_uncomp_size);
    }
}
Zip::~Zip()
{
    free(Zip::zipArchive);
}
    
bool Zip::mapFile(const std::string& filename, std::vector<uint8_t>& data)
{
    Zip::EntriesMap::const_iterator it = Zip::entries.find(filename);
    if (it == Zip::entries.end()) {
        return false;
    }
    
    uint32_t index = std::get<0>(it->second);
    uint64_t size = std::get<1>(it->second);
    data.resize((size_t)size);
    
    bool ok = mz_zip_reader_extract_to_mem_no_alloc((mz_zip_archive*)Zip::zipArchive,
                                                    index,
                                                    data.data(),
                                                    (size_t)size,
                                                    0, 0, 0);
    return ok;
}
const std::string& Zip::getFileName() const
{
    return Zip::fileName;
}

bool Zip::isReadOnly() const
{
    std::filesystem::perms zipPerms = std::filesystem::status(Zip::fileName).permissions();
    return ((zipPerms & std::filesystem::perms::owner_write) != std::filesystem::perms::none);
}

FileZip::FileZip(FileInfo& fileInfo, Zip* zipFile)
: zipArchive(zipFile)
, info(fileInfo)
, readOnly(true)
, opened(false)
, hasChanges(false)
, seekPos(0)
, mode(0)
{
    if (FileZip::zipArchive)
    {
        std::cout << "[Filesystem] Cannot init zip file from empty zip archive" << std::endl;
    }
}
FileZip::~FileZip()
{
    
}

bool FileZip::isOpen()
{
    return FileZip::opened;
}
bool FileZip::isReadOnly()
{
    return (FileZip::zipArchive && FileZip::zipArchive->isReadOnly() && FileZip::readOnly);
}

void FileZip::close()
{   
    if (FileZip::isReadOnly() || !FileZip::hasChanges)
    {
        FileZip::opened = false;
        return;
    }
    
    FileZip::opened = false;
}
void FileZip::open(FileInterface::Mode mode)
{
    // TODO: ZIPFS - Add implementation of readwrite mode
    if ((mode & FileInterface::Mode::Write) ||
        (mode & FileInterface::Append)) {
        std::cout << "[Filesystem] Files from zip can be opened only in read only" << std::endl;
        return;
    }
    
    if (!FileZip::info.isValid() ||
        (FileZip::isOpen() && FileZip::mode == mode) ||
        !FileZip::zipArchive)
    {
        return;
    }
    
    std::string absPath = FileZip::info.getAbsolutePath();
    if (absPath[0] == '/')
    {
        absPath = absPath.substr(1, absPath.length() - 1);
    }
    
    bool ok = FileZip::zipArchive->mapFile(absPath, FileZip::data);
    if (!ok) {
        std::cout << "[Filesystem] Cannot open file: " + absPath + " from zip: "
                + FileZip::zipArchive->getFileName() << std::endl;
        return;
    }
    
    FileZip::mode = mode;
    FileZip::readOnly = true;
    FileZip::seekPos = 0;
    if (mode & FileInterface::Mode::Write)
    {
        FileZip::readOnly = false;
    }
    if (mode & FileInterface::Mode::Append)
    {
        FileZip::readOnly = false;
        FileZip::seekPos = FileZip::getSize() > 0 ? FileZip::getSize() - 1 : 0;
    }
    if (mode & FileInterface::Mode::Truncate)
    {
        FileZip::data.clear();
    }
    
    FileZip::opened = true;
}

FileInfo& FileZip::getFileInfo()
{
    return FileZip::info;
}

uint64_t FileZip::getSize()
{
    if (FileZip::isOpen())
    {
        return FileZip::data.size();
    }
    
    return 0;
}

uint64_t FileZip::seek(uint64_t offset, FileInterface::Origin origin)
{
    if (!FileZip::isOpen())
    {
        return 0;
    }
    
    if (origin == FileInterface::Begin)
    {
        FileZip::seekPos = offset;
    }
    else if (origin == FileInterface::End)
    {
        FileZip::seekPos = FileZip::getSize() - offset;
    }
    else
    {
        FileZip::seekPos += offset;
    }
    FileZip::seekPos = std::min(FileZip::seekPos, FileZip::getSize() - 1);
    
    return FileZip::tell();
}

uint64_t FileZip::tell()
{
    return FileZip::seekPos;
}

uint64_t FileZip::read(uint8_t* buffer, uint64_t size)
{
    if (!FileZip::isOpen())
    {
        return 0;
    }
    
    uint64_t bufferSize = (FileZip::getSize() - FileZip::tell());
    uint64_t maxSize = std::min(size, bufferSize);
    if (maxSize > 0)
    {
        memcpy(buffer, FileZip::data.data(), (size_t)maxSize);
    }
    else
    {
        return 0;
    }
    
    return maxSize;
}

uint64_t FileZip::write(uint8_t* buffer, uint64_t size)
{
    if (!FileZip::isOpen() || FileZip::isReadOnly())
    {
        return 0;
    }
    
    uint64_t bufferSize = (FileZip::getSize() - FileZip::tell());
    if (size > bufferSize)
    {
        FileZip::data.resize((size_t)(FileZip::data.size() + (size - bufferSize)));
    }
    memcpy(FileZip::data.data() + FileZip::tell(), buffer, (size_t)size);
    
    FileZip::hasChanges = true;
    
    return size;
}
