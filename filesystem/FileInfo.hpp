#ifndef FILEINFO_HPP
#define FILEINFO_HPP

#include <string>

class FileInfo
{
    private:
        std::string name;
        std::string baseName;
        std::string extension;
        std::string absolutePath;
        std::string basePath;

        bool dir;

    public:
        FileInfo(const std::string& filePath, bool isDir = false);
        ~FileInfo();
        
        std::string& getName();
        std::string& getBaseName();
        std::string& getExtension();
        std::string& getAbsolutePath();
        std::string& getBasePath();
        bool isDir();
        bool isValid();

        bool operator==(FileInfo& file);
};

#endif//FILEINFO_HPP
