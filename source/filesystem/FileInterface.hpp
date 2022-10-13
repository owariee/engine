#ifndef FILEINTERFACE_HPP
#define FILEINTERFACE_HPP

#include "FileInfo.hpp"

#include <cstdint>

class FileInterface
{
    public:
        enum Origin { Begin, Middle, End };
        enum Mode { Read = 0x1, Write = 0x2, ReadWrite = Read | Write, Append = 0x4, Truncate = 0x8 };

        FileInterface() = default;
        ~FileInterface() = default;

        virtual bool isOpen() = 0;
        virtual bool isReadOnly() = 0;

        virtual FileInfo& getFileInfo() = 0;

        virtual void close() = 0;
        virtual void open(FileInterface::Mode mode) = 0;
        
        virtual uint8_t getMode() = 0;

        virtual uint64_t getSize() = 0;       
        virtual uint64_t seek(uint64_t offset, FileInterface::Origin origin) = 0;
        virtual uint64_t tell() = 0;
        virtual uint64_t read(uint8_t* buffer, uint64_t size) = 0;
        virtual uint64_t write(uint8_t* buffer, uint64_t size) = 0;

        template<typename T>
        bool read(T& value)
        {
            return (FileInterface::read(reinterpret_cast<uint8_t*>(&value), sizeof(value)) == sizeof(value));
        }

        template<typename T>
        uint64_t write(const T& value)
        {
            return (FileInterface::write(reinterpret_cast<uint8_t*>(&value), sizeof(value)) == sizeof(value));
        }

        inline bool operator ==(FileInterface& file)
        {
            return FileInterface::getFileInfo() == file.getFileInfo();
        }
};

#endif//FILEINTERFACE_HPP

