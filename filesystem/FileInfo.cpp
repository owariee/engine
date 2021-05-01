#include "FileInfo.hpp"

#include <iostream>

FileInfo::FileInfo(std::string path, bool dir)
: dir(dir)
{
    std::string name;
    std::size_t found = path.rfind("/");
    if (found == path.length() - 1 || found == std::string::npos)
    {
        FileInfo::basePath = "";
        name = path;
    }
    else
    {
        FileInfo::basePath = path.substr(0, found + 1);
        name = path.substr(found + 1, path.length() - found - 1);
    }

    if (!name.length())
    {
        std::cout << "[FileInfo] Error while creating instance (" << path <<
                "), probably your path dont have a filename or ends with a slash(/)" << std::endl;
        return;
    }

    found = name.rfind(".");
    if (found == name.length() - 1 || found == std::string::npos)
    {
        FileInfo::baseName = name;
        FileInfo::extension = "";
    }
    else
    {
        FileInfo::baseName = name.substr(0, found);
        FileInfo::extension = name.substr(found + 1, name.length() - found - 1);
    }
}

FileInfo::~FileInfo()
{
    return;
}

bool FileInfo::isDir()
{
    return FileInfo::dir;
}

bool FileInfo::isValid()
{
    return !FileInfo::getAbsolutePath().empty();
}

bool FileInfo::operator==(FileInfo& file)
{
    return FileInfo::getAbsolutePath() == file.getAbsolutePath();
}

std::string FileInfo::getName()
{
    if(!FileInfo::extension.length())
    {
        return FileInfo::baseName;
    }
    else
    {
        return FileInfo::baseName + "." + FileInfo::extension;
    }
}

std::string FileInfo::getBaseName()
{
    return FileInfo::baseName;
}

std::string FileInfo::getExtension()
{
    return FileInfo::extension;
}

std::string FileInfo::getAbsolutePath()
{
    if(!FileInfo::basePath.length())
    {
        return FileInfo::getName();
    }
    else
    {
        return FileInfo::basePath + FileInfo::getName();
    }
}

std::string FileInfo::getBasePath()
{
    return FileInfo::basePath;
}

