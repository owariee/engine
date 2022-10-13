#include "FileZip.hpp"

#include <filesystem>
#include <algorithm>
#include <string>
#include <tuple>
#include <iostream>
#include <cstring>

bool FileZip::isOpen()
{
    return FileZip::opened;
}

bool FileZip::isReadOnly()
{
    return FileZip::readOnly;
}

FileInfo& FileZip::getFileInfo()
{
    return FileZip::info;
}

void FileZip::close()
{   
    FileZip::opened = false;
}

void FileZip::open(FileInterface::Mode mode)
{    
    if(!FileZip::info.isValid() || (FileZip::isOpen() && FileZip::mode == mode))
    {
        return;
    }

    FileZip::seek(0, FileInterface::Origin::Begin);

    if(mode & FileInterface::Mode::Write)
    {
        if(FileZip::readOnly)
        {
            std::cout << "[FileZip] You are trying to open in Write mode an Zip file that is read only" << std::endl;
            return;
        }
    }

    if(mode & FileInterface::Mode::Append)
    {
        if(FileZip::readOnly)
        {
            std::cout << "[FileZip] You are trying to open in Append mode an Zip file that is read only" << std::endl;
            return;
        }
        FileZip::seek(0, FileInterface::Origin::End);
    }

    if(mode & FileInterface::Mode::Truncate)
    {
        if(FileZip::readOnly)
        {
            std::cout << "[FileZip] You are trying to open in Truncate mode an Zip file that is read only" << std::endl;
            return;
        }
        FileZip::data.clear();
    }

    FileZip::mode = mode;
    FileZip::opened = true;    
}

uint8_t FileZip::getMode()
{
    return FileZip::mode;
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
    if(!FileZip::isOpen() || !(mode & FileInterface::Mode::Read))
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
    if(!FileZip::isOpen() ||
        FileZip::isReadOnly() ||
        (!(mode & FileInterface::Mode::Write) &&
         !(mode & FileInterface::Mode::Append) &&
         !(mode & FileInterface::Mode::Truncate)))
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

FileZip::FileZip(FileInfo& fileInfo, bool readOnly)
: info(fileInfo)
, readOnly(readOnly)
, opened(false)
, hasChanges(false)
, seekPos(0)
, mode(0)
{
    
}

FileZip::~FileZip()
{
    
}
