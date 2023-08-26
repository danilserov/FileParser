#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include "FileWritter.h"

class FileParser
{
public:
  FileParser(
    const std::filesystem::path& filePath,
    FileWritterPtr writter
  );
  ~FileParser();
  bool Parse();

private:
  bool DoParse();
  FileWritterPtr fileWritter_;
  const std::filesystem::path filePath_;

  std::vector<std::string_view> SplitString(
    const std::string& input,
    const std::vector<std::string>& delimiters
  );
};

typedef std::shared_ptr<FileParser> FileParserPtr;