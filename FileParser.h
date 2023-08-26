#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <filesystem>
#include "IFileWritter.h"

class FileParser
{
private:
  std::unordered_set<std::string> delimiters_;
  const std::filesystem::path filePath_;
public:
  FileParser(const std::filesystem::path& filePath);
  ~FileParser();

  bool Parse(IFileWritter* writter);
};

typedef std::shared_ptr<FileParser> FileParserPtr;