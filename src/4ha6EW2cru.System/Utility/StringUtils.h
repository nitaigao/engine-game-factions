/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   StringUtils.h
*  @date   2009/08/04
*/
#pragma once
#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
#include <deque>
#include <map>

#include "../Export.hpp"

namespace Utility
{
  /*! 
   *  String Utilities
   */
  class StringUtils 
  {

  public:

    typedef std::deque<std::string> StringList;
    typedef std::map<std::string, std::string> StringMap;

    static GAMEAPI std::string ToString(int input);

    static GAMEAPI std::string Replace(const std::string& input, const std::string& oldString, const std::string& newString);

  private:

    ~StringUtils() { };

    StringUtils() { };
    StringUtils(const StringUtils & copy) { };
    StringUtils & operator = (const StringUtils & copy) { return *this; };
    
  };
};

#endif