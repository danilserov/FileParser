#include <chrono>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <future>
#include <queue>

#include "FileProcessor.h"
#include "FileParser.h"

using namespace std::chrono_literals;

FileProcessor::FileProcessor(const std::string& outputFileName):
  fileWritter_(new FileWritter(outputFileName))
{

}

void FileProcessor::AddFileToParse(const std::filesystem::path& filePath)
{
  FileParserPtr parserPtr(
    new FileParser(filePath,
      fileWritter_)
  );

  auto handle = 
    std::async(
      std::launch::async,
      &FileParser::Parse,
      parserPtr
    );
  results_.push(std::move(handle));
}

void FileProcessor::WaitForComplete()
{
  while (!results_.empty())
  {
    if (results_.front().wait_for(1000ms) == std::future_status::ready)
    {
      results_.pop();
    }
  }
}

