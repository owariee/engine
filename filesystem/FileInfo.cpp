#include "FileInfo.hpp"

#include <iostream>

FileInfo::FileInfo(const std::string& filePath, bool isDir)
: absolutePath(filePath)
, dir(isDir)
{
    //FileInfo::absolutePath = filePath;
    //FileInfo::dir = isDir;

    std::size_t found = FileInfo::absolutePath.rfind("/");

    /*if (found == std::string::npos)
    {
        Debug::print(Debug::Flags::Error, Debug::Subsystem::Vfs,
          "While creating FileInfo instance (" + FileInfo::absolutePath +
          "), probably your path do not contain a slash(/) to determine the location");
        return;
    }*/
    
    FileInfo::basePath = FileInfo::absolutePath.substr(0, found + 1);
    FileInfo::name = FileInfo::absolutePath.substr(found + 1, FileInfo::absolutePath.length() - found - 1);

    if (!FileInfo::name.length())
    {
        std::cout << "[Filesystem] Error while creating FileInfo instance ("
                + FileInfo::absolutePath
                + "), probably your path dont have a filename or ends with a slash(/)" << std::endl;
        return;
    }

    found = FileInfo::name.rfind(".");

    FileInfo::baseName = FileInfo::name.substr(0, found);

    if (found == FileInfo::name.length() - 1 || found == std::string::npos)
    {
        FileInfo::extension = "";
    }
    else
    {
        FileInfo::extension = FileInfo::name.substr(found + 1, FileInfo::name.length() - found - 1);
    }
}

FileInfo::~FileInfo()
{
    return;
}

std::string& FileInfo::getName()
{
    return FileInfo::name;
}

std::string& FileInfo::getBaseName()
{
    return FileInfo::baseName;
}

std::string& FileInfo::getExtension()
{
    return FileInfo::extension;
}

std::string& FileInfo::getAbsolutePath()
{
    return FileInfo::absolutePath;
}

std::string& FileInfo::getBasePath()
{
    return FileInfo::basePath;
}

bool FileInfo::isDir()
{
    return FileInfo::dir;
}

bool FileInfo::isValid()
{
    return !FileInfo::absolutePath.empty();
}

bool FileInfo::operator==(FileInfo& file)
{
    return FileInfo::getAbsolutePath() == file.getAbsolutePath();
}
