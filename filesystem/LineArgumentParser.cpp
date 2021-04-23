#include "LineArgumentParser.hpp"

#include "Debug.hpp"

LineArgumentParser::LineArgumentParser(FileInterface* file)
: file(file)
{
    if(!(LineArgumentParser::file->isOpen()))
    {
        Debug::print(Debug::Flags::Error, Debug::Subsystem::Vfs,
            "The file must be open for reading.");
        return;
    }

    LineArgumentParser::fileSize = LineArgumentParser::file->getSize();
}

LineArgumentParser::~LineArgumentParser()
{

}

bool LineArgumentParser::readLine()
{
    char buffer = ' ';
	std::string line = "";
	while(buffer != '\n' &&
          buffer != '\0' &&
          LineArgumentParser::file->tell() < LineArgumentParser::fileSize)
	{
		LineArgumentParser::file->read(reinterpret_cast<uint8_t*>(&buffer), sizeof(char));
		line += buffer;
	}

    if(buffer == '\n' && buffer == '\0')
    {
        line = line.substr(0, line.size()-1);
    }

    LineArgumentParser::arguments = LineArgumentParser::splitArgument(line, ' ');

    if(buffer == '\0')
    {
        return false;
    }

    return true;
}

std::string LineArgumentParser::getArgument(int id)
{
    if (id >= LineArgumentParser::getArgumentCount())
    {
        return 0;
    }

    return LineArgumentParser::arguments[id];
}

int LineArgumentParser::getArgumentCount()
{
    return LineArgumentParser::arguments.size();
}

std::vector<std::string> LineArgumentParser::splitArgument(std::string argument, char limit)
{
    std::vector<std::string> vecBuffer;
    std::string component = "";
    for(auto i = argument.begin(); i != argument.end(); i++)
    {
        if(*i == limit)
        {
            vecBuffer.push_back(component);
            component = "";
        }
        else
        {
            component += *i;
        }
    }
    return vecBuffer;
}

bool LineArgumentParser::validateArgumentNumber(int min, int max)
{
    auto argumentCount = LineArgumentParser::getArgumentCount();
    if(argumentCount < min || argumentCount > max)
    {
        Debug::print(Debug::Flags::Error, Debug::Subsystem::Graphics, 
            "Malformed command: " + LineArgumentParser::getArgument(0));
        return true;
    }
    return false;
}
