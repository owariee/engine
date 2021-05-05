#include "FilesystemZip.hpp"

#include "FileZip.hpp"

#include <fstream>
#include <filesystem>
#include <memory>
#include <algorithm>
#include <iostream>

//std::unordered_map<std::string, Zip*> FilesystemZip::openedZips;

FilesystemZip::FilesystemZip(std::string zipPath, std::string basePath)
: zipPath(zipPath)
, basePath(basePath)
, initialized(false)
{
    FilesystemZip::initialize();
}

FilesystemZip::~FilesystemZip()
{
    
}

void FilesystemZip::initialize()
{
    if (FilesystemZip::initialized)
    {
        return;
    }

    FilesystemZip::zip = static_cast<mz_zip_archive*>(malloc(sizeof(mz_zip_archive)));
    memset(FilesystemZip::zip, 0, sizeof(mz_zip_archive));
    
    mz_bool status = mz_zip_reader_init_file((mz_zip_archive*)FilesystemZip::zip, zipPath.c_str(), 0);
    if (!status)
    {
        std::cout << "[Filesystem] Cannot open zip file: " + zipPath << std::endl;
    }
    
    for (mz_uint i = 0; i < mz_zip_reader_get_num_files((mz_zip_archive*)FilesystemZip::zip); i++)
    {
        mz_zip_archive_file_stat file_stat;
        if (!mz_zip_reader_file_stat((mz_zip_archive*)FilesystemZip::zip, i, &file_stat))
        {
            std::cout << "[Filesystem] Cannot read entry with index: " 
                    + std::to_string(i) + " from zip archive " + zipPath << std::endl;
            continue;
        }
        
        //FilesystemZip::entries.insert(file_stat.m_filename, std::make_tuple(file_stat.m_file_index, file_stat.m_uncomp_size));
        FilesystemZip::entries[file_stat.m_filename] = std::make_tuple(file_stat.m_file_index, file_stat.m_uncomp_size);
        //std::cout << file_stat.m_filename << " Index: " << std::get<0>(FilesystemZip::entries[file_stat.m_filename]) << " Uncompressed size: " << std::get<1>(FilesystemZip::entries[file_stat.m_filename]) << std::endl;
    }

    //FilesystemZip::openedZips[FilesystemZip::zipPath] = FilesystemZip::zip;
    
    // std::lock_guard<decltype(FilesystemZip::mutex)> lock(FilesystemZip::mutex);
    // FilesystemZip::zip = FilesystemZip::openedZips[FilesystemZip::zipPath];
    // if (!FilesystemZip::zip) {
    //     FilesystemZip::zip = new Zip(FilesystemZip::zipPath);
    //     
    // }
    FilesystemZip::initialized = true;   
}

void FilesystemZip::shutdown()
{
    std::lock_guard<decltype(FilesystemZip::mutex)> lock(FilesystemZip::mutex);
    free(FilesystemZip::zip);
    FilesystemZip::zip = nullptr;
    // if (FilesystemZip::openedZips.count(FilesystemZip::zipPath) == 1) {
    //     FilesystemZip::openedZips.erase(FilesystemZip::zipPath);
    // }
    FilesystemZip::fileList.clear();
    FilesystemZip::initialized = false;
}

FileInterface* FilesystemZip::openFile(FileInfo& filePath, FileInterface::Mode mode)
{
    FileInfo fileInfo(filePath.getAbsolutePath(), false);
    FileZip* file = dynamic_cast<FileZip*>(FilesystemZip::findFile(fileInfo));
    bool isExists = (file != nullptr);
    if (!isExists)
    {
        file = new FileZip(fileInfo);

        FilesystemZip::EntriesMap::const_iterator it = FilesystemZip::entries.find(fileInfo.getName());
        if (it == FilesystemZip::entries.end()) {
            std::cout << "[FilesystemZip] Cannot find the specified file in the zip entries" << std::endl;
            return nullptr;
        }
        
        uint32_t index = std::get<0>(it->second);
        uint64_t size = std::get<1>(it->second);
        file->data.resize((size_t)size);

        std::cout << fileInfo.getName() << " Index: " << index << " Uncompressed size: " << size << std::endl;
        
        bool ok = mz_zip_reader_extract_to_mem_no_alloc((mz_zip_archive*)FilesystemZip::zip,
                                                        index,
                                                        file->data.data(),
                                                        (size_t)size,
                                                        0, 0, 0);
        if(!ok)
        {
            std::cout << "[FilesystemZip] Cannot open the specified file in the zip entries" << std::endl;
        }
    }
    file->open(mode);
    
    if (!isExists && file->isOpen())
    {
        FilesystemZip::fileList.insert(file);
    }
    
    return file;
}

void FilesystemZip::closeFile(FileInterface* file)
{
    if (file)
    {
        file->close();
    }
}

std::string& FilesystemZip::getBasePath()
{
    return FilesystemZip::basePath;
}

bool FilesystemZip::isInitialized()
{
    return FilesystemZip::initialized;
}

bool FilesystemZip::isReadOnly()
{
    if (!FilesystemZip::isInitialized())
    {
        return true;
    }
    
    std::filesystem::perms zipPerms = std::filesystem::status(FilesystemZip::zipPath).permissions();
    return ((zipPerms & std::filesystem::perms::owner_write) != std::filesystem::perms::none);
    //return FilesystemZip::zip->isReadOnly();
}

bool FilesystemZip::createFile(FileInfo& filePath)
{
    bool result = false;
    if (!FilesystemZip::isFileExists(filePath))
    {
        FileInterface* file = FilesystemZip::openFile(filePath, FileInterface::Mode::ReadWrite);
        if (file)
        {
            result = true;
            file->close();
        }
    }
    else
    {
        result = true;
    }
    
    return result;
}

bool FilesystemZip::removeFile(FileInfo& filePath)
{
    return false; //Not implemented right now
}

bool FilesystemZip::copyFile(FileInfo& source, FileInfo& destination)
{
    bool result = false;
    if (!FilesystemZip::isReadOnly())
    {
        FileZip* srcFile = (FileZip*)(FilesystemZip::findFile(source));
        FileZip* dstFile = (FileZip*)(FilesystemZip::openFile(destination,
            FileInterface::Mode::Write));
        
        if (srcFile && dstFile)
        {
            dstFile->data.assign(srcFile->data.begin(), srcFile->data.end());
            dstFile->close();
            
            result = true;
        }
    }
    
    return result;
}

bool FilesystemZip::renameFile(FileInfo& source, FileInfo& destination)
{
    return false; // TODO: Filesystem, temporally not suppoted
}

bool FilesystemZip::isFileExists(FileInfo& filePath)
{
    return (FilesystemZip::findFile(filePath) != nullptr);
}

bool FilesystemZip::isFile(FileInfo& filePath)
{
    FileInterface* file = FilesystemZip::findFile(filePath);
    if (file)
    {
        return !file->getFileInfo().isDir();
    }
    
    return false;
}

bool FilesystemZip::isDir(FileInfo& dirPath)
{
    FileInterface* file = FilesystemZip::findFile(dirPath);
    if (file)
    {
        return file->getFileInfo().isDir();
    }
    
    return false;
}

FileInterface* FilesystemZip::findFile(FileInfo& fileInfo)
{
    FilesystemZip::FileList::const_iterator it = std::find_if(
        FilesystemZip::fileList.begin(),
        FilesystemZip::fileList.end(),
        [&](FileInterface* file)
    {
        return file->getFileInfo() == fileInfo;
    });
    
    if (it != FilesystemZip::fileList.end())
    {
        return *it;
    }
    
    return nullptr;
}
