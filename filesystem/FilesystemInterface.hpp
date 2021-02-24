#ifndef FILESYSTEMINTERFACE_HPP
#define FILESYSTEMINTERFACE_HPP

#include "FileInterface.hpp"

#include <set>
#include <string>

class FilesystemInterface
{
    public:
        typedef std::set<FileInterface*> FileList;

        FilesystemInterface() = default;
        ~FilesystemInterface() = default;

        virtual void initialize() = 0;
        virtual void shutdown() = 0;
        
        virtual FileInterface* openFile(FileInfo& filePath, FileInterface::Mode mode) = 0;
        virtual void closeFile(FileInterface* file) = 0;
        virtual std::string& getBasePath() = 0;

        virtual bool isInitialized() = 0;
        virtual bool isReadOnly() = 0;
        virtual bool createFile(FileInfo& filePath) = 0;
        virtual bool removeFile(FileInfo& filePath) = 0;
        virtual bool copyFile(FileInfo& source, FileInfo& destination) = 0;
        virtual bool renameFile(FileInfo& source, FileInfo& destination) = 0;
        virtual bool isFileExists(FileInfo& filePath) = 0;
        virtual bool isFile(FileInfo& filePath) = 0;
        virtual bool isDir(FileInfo& dirPath) = 0;
        virtual FileList& getFileList() = 0;
};

#endif//FILESYSTEMINTERFACE_HPP
