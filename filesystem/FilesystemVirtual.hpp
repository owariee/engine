#ifndef FILESYSTEMVIRTUAL_HPP
#define FILESYSTEMVIRTUAL_HPP

#include "FilesystemInterface.hpp"
#include "FileInterface.hpp"

#include <string>
#include <unordered_map>

class FilesystemVirtual final
{
public:
    typedef std::list<FilesystemInterface*> FileSystemList;
    typedef std::unordered_map<std::string, FilesystemInterface*> FileSystemMap;
    
    struct SSortedAlias
    {
        std::string alias;
        IFileSystemPtr filesystem;
        
        SSortedAlias(const std::string& a,
                     IFileSystemPtr fs)
        : alias(a)
        , filesystem(fs)
        {}
    };
    typedef std::list<SSortedAlias> TSortedAliasList;

    FilesystemVirtual();
    ~FilesystemVirtual();
    
    void addFileSystem(const std::string& alias, FilesystemInterface* filesystem);
    void removeFileSystem(const std::string& alias);
    bool isFileSystemExists(const std::string& alias) const;
    FilesystemInterface* getFilesystem(const std::string& alias);
    FileInteface* openFile(const FileInfo& filePath, FileInterface::Mode mode);
    void closeFile(FileInterface* file);
    
private:
    FileSystemMap m_FileSystem;
    TSortedAliasList m_SortedAlias;
    std::unordered_map<uintptr_t, FilesystemInterface*> m_OpenedFiles;
        
};

#endif//FILESYSTEMVIRTUAL_HPP
