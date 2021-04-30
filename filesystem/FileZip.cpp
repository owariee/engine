#include "FileZip.hpp"

#include <filesystem>
#include <algorithm>
#include <string>
#include <tuple>
#include <iostream>

FileZip::FileZip(FileInfo& fileInfo)
: info(fileInfo)
, readOnly(true)
, opened(false)
, hasChanges(false)
, seekPos(0)
, mode(0)
{
    
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
    return FileZip::readOnly;
}

void FileZip::close()
{   
    if(!FileZip::isOpen())
    {
        return;
    }

    FileZip::opened = false;

    if(FileZip::isReadOnly() || !FileZip::hasChanges)
    {
        return;
    }
    
    // save modifications using the FilesystemZip instance
}

void FileZip::open(FileInterface::Mode mode)
{    
    if(!FileZip::info.isValid() || (FileZip::isOpen() && FileZip::mode == mode))
    {
        return;
    }

    FileZip::opened = true;
    
    FileZip::mode = mode;
    FileZip::readOnly = true;
    FileZip::seek(0, FileInterface::Origin::Begin);

    if(mode & FileInterface::Mode::Write)
    {
        FileZip::readOnly = false;
    }

    if(mode & FileInterface::Mode::Append)
    {
        FileZip::readOnly = false;
        FileZip::seek(0, FileInterface::Origin::End);
    }

    if(mode & FileInterface::Mode::Truncate)
    {
        FileZip::data.clear();
        FileZip::seek(0, FileInterface::Origin::Begin);
    }
}

FileInfo& FileZip::getFileInfo()
{
    return FileZip::info;
}

uint64_t FileZip::getSize()
{
    if(FileZip::isOpen())
    {
        return FileZip::data.size() - 1;
    }
    
    return 0;
}

uint64_t FileZip::seek(uint64_t offset, FileInterface::Origin origin)
{
    if(!FileZip::isOpen())
    {
        return 0;
    }
    
    if(origin == FileInterface::Begin)
    {
        FileZip::seekPos = offset;
    }
    else if(origin == FileInterface::End)
    {
        FileZip::seekPos = FileZip::getSize() - offset;
    }
    else
    {
        FileZip::seekPos += offset;
    }

    FileZip::seekPos = std::min(FileZip::seekPos, FileZip::getSize());
    
    return FileZip::tell();
}

uint64_t FileZip::tell()
{
    return FileZip::seekPos;
}

uint64_t FileZip::read(uint8_t* buffer, uint64_t size)
{
    if(!FileZip::isOpen())
    {
        return 0;
    }

    size = std::min(size, FileZip::getSize() - FileZip::tell());
    memcpy(buffer, FileZip::data.data() + FileZip::tell(), (size_t)size);
    FileZip::seek(size, FileInterface::Origin::Middle);
    return size;
}

uint64_t FileZip::write(uint8_t* buffer, uint64_t size)
{
    if(!FileZip::isOpen() || FileZip::isReadOnly())
    {
        return 0;
    }
    
    uint64_t bufferSize = FileZip::getSize() - FileZip::tell();
    if(size > bufferSize)
    {
        FileZip::data.resize((size_t)(FileZip::data.size() + (size - bufferSize)));
    }

    memcpy(FileZip::data.data() + FileZip::tell(), buffer, (size_t)size);

    FileZip::seek(size, FileInterface::Origin::Middle);
    FileZip::hasChanges = true;
    return size;
}
