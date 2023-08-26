#pragma once

#include<mutex>
#include<string>
#include <fstream>
#include <iostream>
#include <string_view>
#include <vector>

class FileWritter
{
private:
  std::mutex writeMux_;
  const std::string outputFileName_;

public:

  FileWritter(const std::string& outputFileName) :outputFileName_(outputFileName)
  {

  }

  bool WriteResult(
    const std::vector<std::string_view>& result,
    std::string_view marker
  );  
};

typedef std::shared_ptr<FileWritter> FileWritterPtr;