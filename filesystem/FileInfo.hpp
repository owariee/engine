#ifndef FILEINFO_HPP
#define FILEINFO_HPP

#include <string>

class FileInfo
{
    private:
        bool dir;

        std::string baseName;
        std::string extension;
        std::string basePath;

    public:
        FileInfo(std::string path, bool dir = false);
        ~FileInfo();
        
        bool isDir();
        bool isValid();
        bool operator==(FileInfo& file);
        
        std::string getName();
        std::string getBaseName();
        std::string getExtension();
        std::string getAbsolutePath();
        std::string getBasePath();
};

#endif//FILEINFO_HPP

