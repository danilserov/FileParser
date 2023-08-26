#include <iostream>
#include <thread>
#include <fstream>
#include "FileParser.h"

FileParser::FileParser(const std::filesystem::path& filePath):
  filePath_(filePath)
{

}

FileParser::~FileParser()
{

}

bool FileParser::Parse(IFileWritter* writter)
{
  std::unordered_set<std::string> delimeters;
  std::string theString;
  std::thread::id this_id = std::this_thread::get_id();

  std::ifstream inFile(filePath_);

  if (inFile.is_open()) 
  {
    std::string line;

    if (!std::getline(inFile, theString))
    {
      return false;
    }

    while (std::getline(inFile, line)) 
    { 
      delimeters.insert(line);
    }

    inFile.close();
  }
  else 
  {
    std::cerr << "Не удалось открыть файл." << std::endl;
  }

  writter->WriteResult("hey\ntest2");
  return true;
}
