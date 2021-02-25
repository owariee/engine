#include "FilesystemZip.hpp"

#include "FileZip.hpp"

#include <fstream>
#include <filesystem>
#include <memory>

std::unordered_map<std::string, Zip*> FilesystemZip::openedZips;

FilesystemZip::FilesystemZip(std::string& zipPath, std::string& basePath)
: zipPath(zipPath)
, basePath(basePath)
, initialized(false)
{

}
FilesystemZip::~FilesystemZip()
{
    
}

void FilesystemZip::initialize()
{
    if (FilesystemZip::initialized)
    {
        return;
    }
    
    std::lock_guard<decltype(FilesystemZip::mutex)> lock(FilesystemZip::mutex);
    FilesystemZip::zip = FilesystemZip::openedZips[FilesystemZip::zipPath];
    if (!FilesystemZip::zip) {
        FilesystemZip::zip = new Zip(FilesystemZip::zipPath);
        FilesystemZip::openedZips[FilesystemZip::zipPath] = FilesystemZip::zip;
    }
    FilesystemZip::initialized = true;   
}
void FilesystemZip::shutdown()
{
    std::lock_guard<decltype(FilesystemZip::mutex)> lock(FilesystemZip::mutex);
    FilesystemZip::zip = nullptr;
    if (FilesystemZip::openedZips.count(FilesystemZip::zipPath) == 1) {
        FilesystemZip::openedZips.erase(FilesystemZip::zipPath);
    }
    FilesystemZip::fileList.clear();
    FilesystemZip::initialized = false;
}

FileInterface* FilesystemZip::openFile(FileInfo& filePath, FileInterface::Mode mode)
{
    FileInfo fileInfo(filePath.getAbsolutePath(), false);
    FileInterface* file = FilesystemZip::findFile(fileInfo);
    bool isExists = (file != nullptr);
    if (!isExists)
    {        
        file = new FileZip(fileInfo, FilesystemZip::zip);
    }
    file->open(mode);
    
    if (!isExists && file->isOpen())
    {
        FilesystemZip::fileList.insert(file);
    }
    
    return file;
}
void FilesystemZip::closeFile(FileInterface* file)
{
    if (file)
    {
        file->close();
    }
}
std::string& FilesystemZip::getBasePath()
{
    return FilesystemZip::basePath;
}

bool FilesystemZip::isInitialized()
{
    return FilesystemZip::initialized;
}
bool FilesystemZip::isReadOnly()
{
    if (!FilesystemZip::isInitialized())
    {
        return true;
    }
    
    return FilesystemZip::zip->isReadOnly();
}
bool FilesystemZip::createFile(FileInfo& filePath)
{
    bool result = false;
    if (!FilesystemZip::isFileExists(filePath))
    {
        FileInterface* file = FilesystemZip::openFile(filePath, FileInterface::Mode::ReadWrite);
        if (file)
        {
            result = true;
            file->close();
        }
    }
    else
    {
        result = true;
    }
    
    return result;
}
bool FilesystemZip::removeFile(FileInfo& filePath)
{
    return false; //Not implemented right now
}
bool FilesystemZip::copyFile(FileInfo& source, FileInfo& destination)
{
    bool result = false;
    if (!FilesystemZip::isReadOnly())
    {
        FileZip* srcFile = (FileZip*)(FilesystemZip::findFile(source));
        FileZip* dstFile = (FileZip*)(FilesystemZip::openFile(destination,
            FileInterface::Mode::Write));
        
        if (srcFile && dstFile)
        {
            dstFile->data.assign(srcFile->data.begin(), srcFile->data.end());
            dstFile->close();
            
            result = true;
        }
    }
    
    return result;
}
bool FilesystemZip::renameFile(FileInfo& source, FileInfo& destination)
{
    return false; // TODO: Filesystem, temporally not suppoted
}
bool FilesystemZip::isFileExists(FileInfo& filePath)
{
    return (FilesystemZip::findFile(filePath) != nullptr);
}
bool FilesystemZip::isFile(FileInfo& filePath)
{
    FileInterface* file = FilesystemZip::findFile(filePath);
    if (file)
    {
        return !file->getFileInfo().isDir();
    }
    
    return false;
}
bool FilesystemZip::isDir(FileInfo& dirPath)
{
    FileInterface* file = FilesystemZip::findFile(dirPath);
    if (file)
    {
        return file->getFileInfo().isDir();
    }
    
    return false;
}

FileInterface* FilesystemZip::findFile(FileInfo& fileInfo)
{
    FilesystemZip::FileList::const_iterator it = std::find_if(
        FilesystemZip::fileList.begin(),
        FilesystemZip::fileList.end(),
        [&](FileInterface* file)
    {
        return file->getFileInfo() == fileInfo;
    });
    
    if (it != FilesystemZip::fileList.end())
    {
        return *it;
    }
    
    return nullptr;
}
