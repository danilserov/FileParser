#pragma once
#include <string>
#include <filesystem>
#include <queue>
#include <future>
#include "FileWritter.h"

class FileProcessor
{
private:
  std::queue<std::future<bool>> results_;
  std::unique_ptr<FileWritter> fileWritter_;
public:
  explicit FileProcessor(const std::string& outputFileName);
  void AddFileToParse(const std::filesystem::path& filePath);
  void WaitForComplete();
};
