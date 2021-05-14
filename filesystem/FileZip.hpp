#ifndef FILEZIP_HPP
#define FILEZIP_HPP

#include "FileInterface.hpp"

#include <cstdint>
#include <vector>

class FileZip final : public FileInterface
{
    public:
        virtual bool isOpen() override; //Okay 
        virtual bool isReadOnly() override; //Okay

        virtual FileInfo& getFileInfo() override; //Okay

        virtual void close() override; //Okay
        virtual void open(FileInterface::Mode mode) override; //Okay

        virtual uint8_t getMode() override; //Okay

        virtual uint64_t getSize() override; //Okay
        virtual uint64_t seek(uint64_t offset, FileInterface::Origin origin) override; //Okay
        virtual uint64_t tell() override; //Okay
        virtual uint64_t read(uint8_t* buffer, uint64_t size) override; //Okay
        virtual uint64_t write(uint8_t* buffer, uint64_t size) override; //Okay

    private:
        FileZip(FileInfo& fileInfo, bool readOnly);
        ~FileZip();

        bool readOnly;                              //Okay
        bool opened;                                //Okay
        bool hasChanges;                            //Okay
        
        FileInfo info;                              //Okay
        std::vector<uint8_t> data;

        uint8_t mode;                               //Okay
        uint64_t seekPos;                           //Okay

        friend class FilesystemZip;
};

#endif//FILEZIP_HPP

