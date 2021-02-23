#include "FileLZ4.hpp"

#include "microtar.h"

#include <iostream>

FileLZ4::FileLZ4(FileInfo& fileInfo)
: info(fileInfo)
, readOnly(true)
, mode(0)
, file(nullptr)
{
}

FileLZ4::~FileLZ4()
{
    FileLZ4::close();
}

bool FileLZ4::isOpen()
{
    return FileLZ4::file != nullptr;
}

bool FileLZ4::isReadOnly()
{
    return FileLZ4::readOnly;
}

void FileLZ4::close()
{
    if (FileLZ4::isOpen())
    {
        delete FileLZ4::file;
        FileLZ4::file = nullptr;
    }
}

void FileLZ4::open(FileInterface::Mode mode, mtar_t* tar)
{
    if (FileLZ4::isOpen() && FileLZ4::mode == mode)
    {
        FileLZ4::seek(0, FileInterface::Origin::Begin);
        return;
    }
    
    FileLZ4::mode = mode;
    FileLZ4::readOnly = true;
    
    std::ios_base::openmode open_mode = (std::ios_base::openmode)0x00;
    if (mode & FileInterface::Mode::Read)
    {
        open_mode |= std::fstream::in;
    }
    if (mode & FileInterface::Mode::Write)
    {
        FileLZ4::readOnly = false;
        open_mode |= std::fstream::out;
    }
    if (mode & FileInterface::Mode::Append)
    {
        FileLZ4::readOnly = false;
        open_mode |= std::fstream::app;
    }
    if (mode & FileInterface::Mode::Truncate)
    {
        open_mode |= std::fstream::trunc;
    }

    mtar_header_t header;
    mtar_find(tar, FileLZ4::info.getAbsolutePath().c_str(), &header);
    FileLZ4::file = (char*)calloc(1, header.size + 1);
    mtar_read_data(tar, FileLZ4::file, header.size);
    FileLZ4::size = header.size;
}

FileInfo& FileLZ4::getFileInfo()
{
    return FileLZ4::info;
}

uint64_t FileLZ4::getSize()
{
    if (!FileLZ4::isOpen())
    {
        return 0;
    }

    uint64_t curPos = FileLZ4::tell();
    FileLZ4::seek(0, FileInterface::Origin::End);
    uint64_t size = FileLZ4::tell();
    FileLZ4::seek(curPos, FileInterface::Origin::Begin);
    return size;
}

uint64_t FileLZ4::seek(uint64_t offset, FileInterface::Origin origin)
{
    if (!FileLZ4::isOpen())
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
    
    FileLZ4::file.seekg(offset, way);
    FileLZ4::file.seekp(offset, way);
    
    return FileLZ4::tell();
}

uint64_t FileLZ4::tell()
{
    if (!FileLZ4::isOpen())
    {
        return 0;
    }

    return static_cast<uint64_t>(FileLZ4::file.tellg());
}

uint64_t FileLZ4::read(uint8_t* buffer, uint64_t size)
{
    if (!FileLZ4::isOpen())
    {
        return 0;
    }

    mtar_read_data(&tar, buffer, size);
    
    return size;
}

uint64_t FileLZ4::write(uint8_t* buffer, uint64_t size)
{
    if (!FileLZ4::isOpen() || FileLZ4::isReadOnly())
    {
        return 0;
    }
    
    mtar_write_data(&tar, buffer, size);
    
    return size;
}
