#ifndef FILESYSTEMLZ4_HPP
#define FILESYSTEMLZ4_HPP

#include "FilesystemInterface.hpp"
#include "FileNative.hpp"

#include <string>

class FilesystemLZ4 final : public FilesystemInterface
{
    public:
        FilesystemLZ4(std::string& lz4Path, std::string& basePath);
        ~FilesystemLZ4();

        virtual void initialize() override;
        virtual void shutdown() override;
        
        virtual FileInterface* openFile(FileInfo& filePath, FileInterface::Mode mode) override;
        virtual void closeFile(FileInterface* file) override;
        virtual std::string& getBasePath() override;

        virtual bool isInitialized() override;
        virtual bool isReadOnly() override;
        virtual bool createFile(FileInfo& filePath) override;
        virtual bool removeFile(FileInfo& filePath) override;
        virtual bool copyFile(FileInfo& source, FileInfo& destination) override;
        virtual bool renameFile(FileInfo& source, FileInfo& destination) override;
        virtual bool isFileExists(FileInfo& filePath) override;
        virtual bool isFile(FileInfo& filePath) override;
        virtual bool isDir(FileInfo& dirPath) override;

    private:
        FileNative* file;
        std::string lz4Path;
        std::string basePath;
        bool initialized;
};

#endif//FILESYSTEMLZ4_HPP
