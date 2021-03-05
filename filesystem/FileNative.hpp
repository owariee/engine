#ifndef FILENATIVE_HPP
#define FILENATIVE_HPP

#include "FileInterface.hpp"

#include <fstream>

class FileNative final : public FileInterface
{
    public:
        FileNative(FileInfo& fileInfo);
        ~FileNative();

        virtual bool isOpen() override;
        virtual bool isReadOnly() override;

        virtual void close() override;
        virtual void open(FileInterface::Mode mode) override;

        virtual FileInfo& getFileInfo() override;
        virtual uint64_t getSize() override;       
        virtual uint64_t seek(uint64_t offset, FileInterface::Origin origin) override;
        virtual uint64_t tell() override;
        virtual uint64_t read(uint8_t* buffer, uint64_t size) override;
        virtual uint64_t write(uint8_t* buffer, uint64_t size) override;

    private:
        FileInfo info;
        std::fstream file;
        bool readOnly;
        int mode;
};

#endif//FILENATIVE_HPP
