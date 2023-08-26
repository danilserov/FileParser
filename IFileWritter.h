#pragma once
#include <string_view>
#include <vector>

struct IFileWritter
{
  virtual bool WriteResult(
    const std::vector<std::string_view>& result,
    std::string_view marker
  ) = 0;
};