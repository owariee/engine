#ifndef FILENATIVE_HPP
#define FILENATIVE_HPP

#include "FileInterface.hpp"

#include <fstream>

class FileNative final : public FileInterface
{
    public:
        FileNative(FileInfo& fileInfo);
        ~FileNative();

        bool isOpen() override;
        bool isReadOnly() override;

        void close() override;
        void open(FileInterface::Mode mode) override;

        FileInfo& getFileInfo() override;
        uint8_t getMode() override;
        uint64_t getSize() override;       
        uint64_t seek(uint64_t offset, FileInterface::Origin origin) override;
        uint64_t tell() override;
        uint64_t read(uint8_t* buffer, uint64_t size) override;
        uint64_t write(uint8_t* buffer, uint64_t size) override;

    private:
        FileInfo info;
        std::fstream file;
        bool readOnly;
        int mode;
};

#endif//FILENATIVE_HPP
