#ifndef FILEZIP_HPP
#define FILEZIP_HPP

#include "FileInterface.hpp"

#include <cstdint>
#include <map>
#include <string>
#include <tuple>
#include <vector>

class Zip
{
public:
    Zip(const std::string& zipPath);
    ~Zip();
    
    bool mapFile(const std::string& filename, std::vector<uint8_t>& data);
    const std::string& getFileName() const;
    
    bool isReadOnly() const;
    
private:
    std::string fileName;
    void* zipArchive;   
    typedef std::map<std::string, std::tuple<uint32_t, uint64_t>> EntriesMap;
    static Zip::EntriesMap entries;
};

class FileZip final : public FileInterface
{
        friend class FilesystemZip;
    public:
        FileZip(FileInfo& fileInfo, Zip* zipFile);
        ~FileZip();

        virtual bool isOpen() override;
        virtual bool isReadOnly() override;

        virtual void close() override;
        virtual void open(FileInterface::Mode mode) override;

        virtual FileInfo& getFileInfo() override;
        virtual uint64_t getSize() override;       
        virtual uint64_t seek(uint64_t offset, FileInterface::Origin origin) override;
        virtual uint64_t tell() override;
        virtual uint64_t read(uint8_t* buffer, uint64_t size) override;
        virtual uint64_t write(uint8_t* buffer, uint64_t size) override;

    private:
        Zip* zipArchive;
        std::vector<uint8_t> data;
        FileInfo info;
        bool readOnly;
        bool opened;
        bool hasChanges;
        uint64_t seekPos;
        int mode;
};

#endif//FILEZIP_HP
