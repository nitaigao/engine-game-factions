#include "precompiled.h"

#include "StringUtils.h"

#include <sstream>

namespace Utility
{
  std::string StringUtils::Replace(const std::string& input, const std::string& oldString, const std::string& newString)
  {
    std::string result = input;

    int index = result.find(oldString);

    for(; index != std::string::npos; )
    {
      if(newString.empty())
      {
        result.erase(index, oldString.length());
      }
      else
      {
        result.replace(index, newString.length(), newString.c_str());
      }

      index = result.find(oldString, index + newString.length());
    }

    return result;
  }

  std::string StringUtils::ToString(int input)
  {
    std::stringstream result;
    result <<input;
    return result.str();
  }
}