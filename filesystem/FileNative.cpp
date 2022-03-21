#include "FileNative.hpp"

#include <cstring>
#include <iostream>

FileNative::FileNative(FileInfo& fileInfo)
: info(fileInfo)
, readOnly(true)
, mode(0)
{
}

FileNative::~FileNative()
{
    FileNative::close();
}

bool FileNative::isOpen()
{
    return FileNative::file.is_open();
}

bool FileNative::isReadOnly()
{
    return FileNative::readOnly;
}

void FileNative::close()
{
    if (FileNative::isOpen())
    {
        FileNative::file.close();
    }
}

void FileNative::open(FileInterface::Mode mode)
{
    if (FileNative::isOpen() && FileNative::mode == mode)
    {
        FileNative::seek(0, FileInterface::Origin::Begin);
        return;
    }
    
    FileNative::mode = mode;
    FileNative::readOnly = true;
    
    std::ios_base::openmode open_mode = (std::ios_base::openmode)0x00;
    if (mode & FileInterface::Mode::Read)
    {
        open_mode |= std::fstream::in;
    }
    if (mode & FileInterface::Mode::Write)
    {
        FileNative::readOnly = false;
        open_mode |= std::fstream::out;
    }
    if (mode & FileInterface::Mode::Append)
    {
        FileNative::readOnly = false;
        open_mode |= std::fstream::app;
    }
    if (mode & FileInterface::Mode::Truncate)
    {
        open_mode |= std::fstream::trunc;
    }
    open_mode |= std::fstream::binary;
    
    FileNative::file.open(
        FileNative::info.getAbsolutePath(), open_mode);
}

FileInfo& FileNative::getFileInfo()
{
    return FileNative::info;
}

uint8_t FileNative::getMode()
{
    return FileNative::mode;
}

uint64_t FileNative::getSize()
{
    if (!FileNative::isOpen())
    {
        return 0;
    }

    uint64_t curPos = FileNative::tell();
    FileNative::seek(0, FileInterface::Origin::End);
    uint64_t size = FileNative::tell();
    FileNative::seek(curPos, FileInterface::Origin::Begin);
    return size;
}

uint64_t FileNative::seek(uint64_t offset, FileInterface::Origin origin)
{
    if (!FileNative::isOpen())
    {
        return 0;
    }
    
    std::ios_base::seekdir way;
    if (origin == FileInterface::Origin::Begin)
    {
        way = std::ios_base::beg;
    }
    else if (origin == FileInterface::Origin::End)
    {
        way = std::ios_base::end;
    }
    else
    {
        way = std::ios_base::cur;
    }
    
    if (FileNative::isReadOnly())
    {
        FileNative::file.seekg(offset, way);
    }
    else 
    {
        FileNative::file.seekp(offset, way);
    }
    
    return FileNative::tell();
}

uint64_t FileNative::tell()
{
    if (!FileNative::isOpen())
    {
        return 0;
    }

    return static_cast<uint64_t>(FileNative::file.tellg());
}

uint64_t FileNative::read(uint8_t* buffer, uint64_t size)
{
    if (!FileNative::isOpen())
    {
        return 0;
    }

    FileNative::file.clear();
    FileNative::file.read(reinterpret_cast<char*>(buffer), static_cast<std::streamsize>(size));
    if (FileNative::file)
    {
        return size;
    }
    
    return static_cast<uint64_t>(FileNative::file.gcount());
}

uint64_t FileNative::write(uint8_t* buffer, uint64_t size)
{
    if (!FileNative::isOpen() || FileNative::isReadOnly())
    {
        return 0;
    }
    
    FileNative::file.clear();
    FileNative::file.write(reinterpret_cast<const char*>(buffer), (std::streamsize)size);
    if (FileNative::file)
    {
        return size;
    }
    
    return static_cast<uint64_t>(FileNative::file.gcount());
}
