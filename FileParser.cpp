#include <iostream>
#include <fstream>
#include "FileParser.h"

FileParser::FileParser(const std::filesystem::path& filePath):
  filePath_(filePath)
{

}

FileParser::~FileParser()
{

}

std::vector<std::string_view> FileParser::SplitString(
  const std::string& input,
  const std::vector<std::string>& delimiters
) 
{
  std::vector<std::string_view> tokens;
  size_t start = 0, end = 0;

  while (start < input.length()) 
  {
    end = input.length();

    for (const std::string& delimiter : delimiters) 
    {
      size_t pos = input.find(delimiter, start);

      if (pos != std::string::npos && pos < end) 
      {
        end = pos;
      }
    }

    if (end != start) 
    {
      tokens.push_back(std::string_view(input).substr(start, end - start));
    }

    if (end == input.length()) 
    {
      break;
    }

    start = end + 1;
  }

  return tokens;
}

bool FileParser::DoParse(IFileWritter* writter)
{
  bool result = false;

  std::vector<std::string> delimeters;
  std::string theString;

  std::ifstream inFile(filePath_);

  if (inFile.is_open())
  {
    std::string line;

    if (!std::getline(inFile, theString))
    {
      return result;
    }

    while (std::getline(inFile, line))
    {
      delimeters.push_back(line);
    }

    std::thread::id threadId = std::this_thread::get_id();
    std::stringstream ss;
    ss << "thread:" << threadId << " file:" << filePath_;
    std::string threadIdStr = ss.str();

    result = writter->WriteResult(
      SplitString(theString, delimeters),
      std::string_view(ss.str())
    );
    inFile.close();
  }
  else
  {
    std::cerr << "Unable to open file:" << filePath_ << std::endl;
  }

  return result;
}

bool FileParser::Parse(IFileWritter* writter)
{
  try
  {
    return DoParse(writter);
  }
  catch (std::exception& ex)
  {
    std::cerr << "exception " << ex.what() << " while parsing:" << filePath_ << std::endl;
  }
  return false;
}
