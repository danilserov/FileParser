#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include "IFileWritter.h"

class FileParser
{
public:
  FileParser(const std::filesystem::path& filePath);
  ~FileParser();
  bool Parse(IFileWritter* writter);

private:
  bool DoParse(IFileWritter* writter);

  const std::filesystem::path filePath_;

  std::vector<std::string_view> SplitString(
    const std::string& input,
    const std::vector<std::string>& delimiters
  );
};

typedef std::shared_ptr<FileParser> FileParserPtr;