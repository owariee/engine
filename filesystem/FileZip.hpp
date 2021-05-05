#ifndef FILEZIP_HPP
#define FILEZIP_HPP

#include "FileInterface.hpp"
#include "FilesystemZip.hpp"

#include <cstdint>
#include <map>
#include <string>
#include <tuple>
#include <vector>

class FileZip final : public FileInterface
{
    public:
        FileZip(FileInfo& fileInfo);
        ~FileZip();

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
        std::vector<uint8_t> data;
        FileInfo info;
        bool readOnly;
        bool opened;
        bool hasChanges;
        uint64_t seekPos;
        int mode;

        friend class FilesystemZip;
};

#endif//FILEZIP_HPP
