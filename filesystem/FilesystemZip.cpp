#include "FilesystemLZ4.hpp"

#include "FileLZ4.hpp"

#include <fstream>
#include <filesystem>

#include "microtar.h"

FilesystemLZ4::FilesystemLZ4(std::string& lz4Path, std::string& basePath)
: 
lz4Path(lz4Path),
basePath(basePath),
initialized(false),
file(nullptr)
{
}

FilesystemLZ4::~FilesystemLZ4()
{
    FilesystemLZ4::shutdown();
}

void FilesystemLZ4::initialize()
{
    FileInfo path(FilesystemLZ4::lz4Path);
    FilesystemLZ4::file = new FileNative(path);
    FilesystemLZ4::initialized = true;
}

void FilesystemLZ4::shutdown()
{
    if (FilesystemLZ4::initialized)
    {
        delete FilesystemLZ4::file;
        FilesystemLZ4::file = nullptr;
        FilesystemLZ4::initialized = false;
    }
}

FileInterface* FilesystemLZ4::openFile(FileInfo& filePath, FileInterface::Mode mode)
{
    if (!FilesystemLZ4::initialized)
    {
        return NULL;
    }

    FileNative* file = new FileNative(filePath);
    file->open(mode);
    return dynamic_cast<FileInterface*>(file);
}

void FilesystemLZ4::closeFile(FileInterface* file)
{
    if (!FilesystemLZ4::initialized)
    {
        return;
    }

    file->close();
}

std::string& FilesystemLZ4::getBasePath()
{
    return FilesystemLZ4::basePath;
}

bool FilesystemLZ4::isInitialized()
{
    return FilesystemLZ4::initialized;
}

bool FilesystemLZ4::isReadOnly()
{
    if (!FilesystemLZ4::initialized)
    {
        return false;
    }

    std::filesystem::perms p;

    p = std::filesystem::status(FilesystemLZ4::basePath).permissions();

    if ((p & std::filesystem::perms::owner_write) == std::filesystem::perms::none)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool FilesystemLZ4::createFile(FileInfo& filePath)
{
    if (!FilesystemLZ4::initialized || 
         FilesystemLZ4::isReadOnly() ||
         FilesystemLZ4::isFileExists(filePath))
    {
        return false;
    }

    if (filePath.isDir())
    {
        return std::filesystem::create_directory(FilesystemLZ4::basePath + filePath.getAbsolutePath());
    }
    else
    {
        std::ofstream(FilesystemLZ4::basePath + filePath.getAbsolutePath());
        return true;
    }
}

bool FilesystemLZ4::removeFile(FileInfo& filePath)
{
    if (!FilesystemLZ4::initialized || 
         FilesystemLZ4::isReadOnly() ||
        !FilesystemLZ4::isFileExists(filePath))
    {
        return false;
    }

    return std::filesystem::remove(
        FilesystemLZ4::basePath + filePath.getAbsolutePath());
}

bool FilesystemLZ4::copyFile(FileInfo& source, FileInfo& destination)
{
    if (!FilesystemLZ4::initialized || 
         FilesystemLZ4::isReadOnly() ||
        !FilesystemLZ4::isFileExists(source) ||
         FilesystemLZ4::isFileExists(destination))
    {
        return false;
    }

    std::filesystem::copy(
        FilesystemLZ4::basePath + source.getAbsolutePath(),
        FilesystemLZ4::basePath + destination.getAbsolutePath(),
        std::filesystem::copy_options::recursive);
    
    return true;
}

bool FilesystemLZ4::renameFile(FileInfo& source, FileInfo& destination)
{
    if (!FilesystemLZ4::initialized || 
         FilesystemLZ4::isReadOnly() ||
        !FilesystemLZ4::isFileExists(source) ||
         FilesystemLZ4::isFileExists(destination))
    {
        return false;
    }

    std::filesystem::rename(
        FilesystemLZ4::basePath + source.getAbsolutePath(),
        FilesystemLZ4::basePath + destination.getAbsolutePath());
    
    return true;
}

bool FilesystemLZ4::isFileExists(FileInfo& filePath)
{
    if (!FilesystemLZ4::initialized) 
    {
        return false;
    }
    
    return std::filesystem::exists(
        FilesystemLZ4::basePath + filePath.getAbsolutePath());
}

bool FilesystemLZ4::isFile(FileInfo& filePath)
{
    if (!FilesystemLZ4::initialized) 
    {
        return false;
    }

    return std::filesystem::is_regular_file(
        FilesystemLZ4::basePath + filePath.getAbsolutePath());
}

bool FilesystemLZ4::isDir(FileInfo& dirPath)
{
    if (!FilesystemLZ4::initialized) 
    {
        return false;
    }

    return std::filesystem::is_directory(
        FilesystemLZ4::basePath + dirPath.getAbsolutePath());
}
