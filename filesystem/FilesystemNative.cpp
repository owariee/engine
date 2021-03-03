#include "FilesystemNative.hpp"

#include "FileNative.hpp"

#include <fstream>
#include <filesystem>

FilesystemNative::FilesystemNative(std::string& basePath)
: basePath(basePath)
{
}

FilesystemNative::~FilesystemNative()
{
    FilesystemNative::shutdown();
}

void FilesystemNative::initialize()
{
    FilesystemNative::initialized = true;

    if (!FilesystemNative::initialized)
    {
        FilesystemNative::buildFileList(FilesystemNative::basePath);
    }
}

void FilesystemNative::shutdown()
{
    if (FilesystemNative::initialized)
    {
        FilesystemNative::fileList.clear();
        FilesystemNative::initialized = false;
    }
}

FileInterface* FilesystemNative::openFile(FileInfo& filePath, FileInterface::Mode mode)
{
    if (!FilesystemNative::initialized)
    {
        return NULL;
    }

    FileInfo absolutePath(FilesystemNative::getBasePath() + filePath.getAbsolutePath());

    FileNative* file = new FileNative(absolutePath);
    file->open(mode);
    return dynamic_cast<FileInterface*>(file);
}

void FilesystemNative::closeFile(FileInterface* file)
{
    if (!FilesystemNative::initialized)
    {
        return;
    }

    file->close();
}

std::string& FilesystemNative::getBasePath()
{
    return FilesystemNative::basePath;
}

bool FilesystemNative::isInitialized()
{
    return FilesystemNative::initialized;
}

bool FilesystemNative::isReadOnly()
{
    if (!FilesystemNative::initialized)
    {
        return false;
    }

    std::filesystem::perms p;

    p = std::filesystem::status(FilesystemNative::basePath).permissions();

    if ((p & std::filesystem::perms::owner_write) == std::filesystem::perms::none)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool FilesystemNative::createFile(FileInfo& filePath)
{
    if (!FilesystemNative::initialized || 
         FilesystemNative::isReadOnly() ||
         FilesystemNative::isFileExists(filePath))
    {
        return false;
    }

    if (filePath.isDir())
    {
        return std::filesystem::create_directory(FilesystemNative::basePath + filePath.getAbsolutePath());
    }
    else
    {
        std::ofstream(FilesystemNative::basePath + filePath.getAbsolutePath());
        return true;
    }
}

bool FilesystemNative::removeFile(FileInfo& filePath)
{
    if (!FilesystemNative::initialized || 
         FilesystemNative::isReadOnly() ||
        !FilesystemNative::isFileExists(filePath))
    {
        return false;
    }

    return std::filesystem::remove(
        FilesystemNative::basePath + filePath.getAbsolutePath());
}

bool FilesystemNative::copyFile(FileInfo& source, FileInfo& destination)
{
    if (!FilesystemNative::initialized || 
         FilesystemNative::isReadOnly() ||
        !FilesystemNative::isFileExists(source) ||
         FilesystemNative::isFileExists(destination))
    {
        return false;
    }

    std::filesystem::copy(
        FilesystemNative::basePath + source.getAbsolutePath(),
        FilesystemNative::basePath + destination.getAbsolutePath(),
        std::filesystem::copy_options::recursive);
    
    return true;
}

bool FilesystemNative::renameFile(FileInfo& source, FileInfo& destination)
{
    if (!FilesystemNative::initialized || 
         FilesystemNative::isReadOnly() ||
        !FilesystemNative::isFileExists(source) ||
         FilesystemNative::isFileExists(destination))
    {
        return false;
    }

    std::filesystem::rename(
        FilesystemNative::basePath + source.getAbsolutePath(),
        FilesystemNative::basePath + destination.getAbsolutePath());
    
    return true;
}

bool FilesystemNative::isFileExists(FileInfo& filePath)
{
    if (!FilesystemNative::initialized) 
    {
        return false;
    }
    
    return std::filesystem::exists(
        FilesystemNative::basePath + filePath.getAbsolutePath());
}

bool FilesystemNative::isFile(FileInfo& filePath)
{
    if (!FilesystemNative::initialized) 
    {
        return false;
    }

    return std::filesystem::is_regular_file(
        FilesystemNative::basePath + filePath.getAbsolutePath());
}

bool FilesystemNative::isDir(FileInfo& dirPath)
{
    if (!FilesystemNative::initialized) 
    {
        return false;
    }

    return std::filesystem::is_directory(
        FilesystemNative::basePath + dirPath.getAbsolutePath());
}

FilesystemNative::FileList& FilesystemNative::getFileList()
{
    return FilesystemNative::fileList;
}

void FilesystemNative::buildFileList(std::string& path)
{
    for (const auto & entry : std::filesystem::directory_iterator(path))
    {
        if (entry.is_directory())
        {
            std::string entryPath = entry.path().string();
            FilesystemNative::buildFileList(entryPath);
        }
        else
        {
            FileInfo fileInfo(entry.path().string());
            FileInterface* file = new FileNative(fileInfo);
            FilesystemNative::fileList.insert(file);
        }
    }
}
