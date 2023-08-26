#pragma once
#include <string_view>

struct IFileWritter
{
  virtual void WriteResult(const std::string_view result) = 0;
};