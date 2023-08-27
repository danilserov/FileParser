#pragma once

#include<mutex>
#include<string>
#include <fstream>
#include <iostream>
#include <string_view>
#include <vector>

class FileWritter;
typedef std::shared_ptr<FileWritter> FileWritterPtr;

class FileWritter
{
private:
  std::mutex writeMux_;
  const std::string outputFileName_;
  static FileWritterPtr instance_;
  FileWritter() {};
  FileWritter(const std::string& outputFileName)
    :outputFileName_(outputFileName)
  {
  }
  ~FileWritter() {};

  static void CustomDeleter (FileWritter* ptr);
public:
  static FileWritterPtr getInstance(const std::string& outputFileName);

  bool WriteResult(
    const std::vector<std::string_view>& result,
    std::string_view marker
  );  
};

