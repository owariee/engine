#include "FilesystemVirtual.hpp"

#include <algorithm>

struct AliasComparator
{
    bool operator()(const FilesystemVirtual::SortedAlias& a1,
        const FilesystemVirtual::SortedAlias& a2) const
    {
        return a1.alias.length() > a2.alias.length();
    }
};

FilesystemVirtual::FilesystemVirtual()
{

}
FilesystemVirtual::~FilesystemVirtual()
{
    std::for_each(FilesystemVirtual::fileSystem.begin(), FilesystemVirtual::fileSystem.end(),
        [](const FileSystemMap::value_type& fs)
    {
        fs.second->shutdown();
    });
}

void FilesystemVirtual::addFileSystem(const std::string& alias, FilesystemInterface* filesystem)
{
    if (!filesystem)
    {
        return;
    }
    
    std::string a = alias;
    if (a[a.length()] == '/')
    {
        a += "/";
    }
    
    FileSystemMap::const_iterator it = FilesystemVirtual::fileSystem.find(a);
    if (it == FilesystemVirtual::fileSystem.end())
    {
        FilesystemVirtual::fileSystem[a] = filesystem;
        FilesystemVirtual::sortedAlias.push_back(SortedAlias(a, filesystem));
        FilesystemVirtual::sortedAlias.sort(AliasComparator());
    }
}
void FilesystemVirtual::removeFileSystem(const std::string& alias)
{
    std::string a = alias;
    if (a[a.length()] == '/')
    {
        a += "/";
    }
    
    FileSystemMap::const_iterator it = FilesystemVirtual::fileSystem.find(a);
    if (it == FilesystemVirtual::fileSystem.end())
    {
        FilesystemVirtual::fileSystem.erase(it);
        // TODO: remove from alias list
    }
}
bool FilesystemVirtual::isFileSystemExists(const std::string& alias) const
{
    return (FilesystemVirtual::fileSystem.find(alias) != FilesystemVirtual::fileSystem.end());
}
FileInterface* FilesystemVirtual::openFile(FileInfo& filePath, FileInterface::Mode mode)
{
    FileInterface* file = nullptr;
    std::all_of(FilesystemVirtual::sortedAlias.begin(),
        FilesystemVirtual::sortedAlias.end(),
        [&](const SortedAliasList::value_type& fs)
    {
        const std::string& alias = fs.alias;
        FilesystemInterface* filesystem = fs.filesystem;
        if (CStringUtils::StartsWith(filePath.getBasePath(), alias) &&
            filePath.getAbsolutePath().length() != alias.length())
        {
            file = filesystem->openFile(filePath, mode);
        }
        
        if (file)
        {
            uintptr_t addr = reinterpret_cast<uintptr_t>(static_cast<void*>(file));
            FilesystemVirtual::openedFiles[addr] = filesystem;
            
            return false;
        }
        
        return true;
    });
    
    return file;
}
void FilesystemVirtual::closeFile(FileInterface* file)
{
    uintptr_t addr = reinterpret_cast<uintptr_t>(static_cast<void*>(file));
    
    std::unordered_map<uintptr_t, FilesystemInterface*>::const_iterator 
        it = FilesystemVirtual::openedFiles.find(addr);
    
    if (it != FilesystemVirtual::openedFiles.end())
    {
        it->second->closeFile(file);
        FilesystemVirtual::openedFiles.erase(it);
    }
}
