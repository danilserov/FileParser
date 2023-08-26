#pragma once
#include<string>
#include<mutex>
#include <fstream>
#include <iostream>
#include "IFileWritter.h"

class FileWritter : public IFileWritter
{
private:

  std::mutex writeMux_;
  const std::string outputFileName_;

  void WriteResult(const std::string_view result) override
  {
    std::unique_lock lock(writeMux_);

    std::ofstream outFile(outputFileName_, std::ios::app);

    if (outFile.is_open())
    {
      outFile << result << std::endl;
      outFile.close();
    }
    else {
      std::cerr << "Unable to write to:" << outputFileName_ << std::endl;
    }
  };

public:

  FileWritter(const std::string& outputFileName):outputFileName_(outputFileName)
  {
    
  }
};