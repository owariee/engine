#ifndef FILESYSTEMNATIVE_HPP
#define FILESYSTEMNATIVE_HPP

#include "FilesystemInterface.hpp"

#include <string>

class FilesystemNative final : public FilesystemInterface
{
    public:
        FilesystemNative(std::string& basePath);
        ~FilesystemNative();

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
        virtual FileList& getFileList() override;

    private:
        std::string basePath;
        bool initialized;
        FileList fileList;

        void buildFileList(std::string& path);
};

#endif//FILESYSTEMNATIVE_HPP
