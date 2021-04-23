#ifndef LINEARGUMENTPARSER_HPP
#define LINEARGUMENTPARSER_HPP

#include "FileInterface.hpp"

#include <bits/types/FILE.h>
#include <vector>

class LineArgumentParser
{
    public:
        LineArgumentParser(FileInterface* file);
        ~LineArgumentParser();

        bool readLine();

        std::string getArgument(int id);
        int getArgumentCount();

        std::vector<std::string> splitArgument(std::string argument, char limit);
        bool validateArgumentNumber(int min, int max);

    private:
        FileInterface* file;
        std::vector<std::string> arguments;
        size_t fileSize;
};

#endif//LINEARGUMENTPARSER_HPP
