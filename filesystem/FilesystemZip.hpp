#ifndef FILESYSTEMZIP_HPP
#define FILESYSTEMZIP_HPP

#include "miniz.h"

#include "FilesystemInterface.hpp"
#include "FileNative.hpp"
#include "FileZip.hpp"

#include <string>
#include <mutex>
#include <unordered_map>
#include <map>

class FilesystemZip final : public FilesystemInterface
{
    public:
        FilesystemZip(std::string zipPath, std::string basePath);
        ~FilesystemZip();

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
        mz_zip_archive* zip;
        FileInterface* file;
        std::string zipPath;
        std::string basePath;
        bool initialized;
        typedef std::map<std::string, std::tuple<uint32_t, uint64_t>> EntriesMap;
        EntriesMap entries;
        std::mutex mutex;
        FileList fileList;

        FileInterface* findFile(FileInfo& fileInfo);
        
};

#endif//FILESYSTEMZIP_HPP
