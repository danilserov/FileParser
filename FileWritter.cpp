#pragma once

#include "FileWritter.h"

bool FileWritter::WriteResult(
  const std::vector<std::string_view>& result,
  std::string_view marker
)
{
  std::unique_lock lock(writeMux_);

  std::ofstream outFile(outputFileName_, std::ios::app);

  if (outFile.is_open())
  {
    outFile << "[" << marker << "]" << std::endl;

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