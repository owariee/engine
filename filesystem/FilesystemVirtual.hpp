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
    
    struct SortedAlias
    {
        std::string alias;
        FilesystemInterface* filesystem;
        
        SortedAlias(const std::string& a,
                    FilesystemInterface* fs)
        : alias(a)
        , filesystem(fs)
        {}
    };
    typedef std::list<SortedAlias> SortedAliasList;

    FilesystemVirtual();
    ~FilesystemVirtual();
    
    void addFileSystem(const std::string& alias, FilesystemInterface* filesystem);
    void removeFileSystem(const std::string& alias);
    bool isFileSystemExists(const std::string& alias) const;
    FileInterface* openFile(FileInfo& filePath, FileInterface::Mode mode);
    void closeFile(FileInterface* file);
    
private:
    FileSystemMap fileSystem;
    SortedAliasList sortedAlias;
    std::unordered_map<uintptr_t, FilesystemInterface*> openedFiles;
        
};

#endif//FILESYSTEMVIRTUAL_HPP
