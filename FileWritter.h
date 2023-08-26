#pragma once

#include<mutex>
#include<string>
#include <fstream>
#include <iostream>
#include "IFileWritter.h"

class FileWritter : public IFileWritter
{
public:

  FileWritter(const std::string& outputFileName) :outputFileName_(outputFileName)
  {

  }

private:
  std::mutex writeMux_;
  const std::string outputFileName_;

  bool WriteResult(
    const std::vector<std::string_view>& result,
    std::string_view marker
  ) override
  {
    std::unique_lock lock(writeMux_);

    std::ofstream outFile(outputFileName_, std::ios::app);

    if (outFile.is_open())
    {
      outFile << "[" << marker  << "]" << std::endl;

      for (auto line : result)
      {
        outFile << line << std::endl;
      } 

      outFile.close();

      std::cerr << "Success:" << marker << std::endl;
      return true;
    }
    else 
    {
      std::cerr << "Unable to write to:" << outputFileName_ << std::endl;      
    }

    return false;
  };
};