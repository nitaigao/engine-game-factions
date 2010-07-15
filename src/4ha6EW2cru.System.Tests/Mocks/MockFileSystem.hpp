/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockFileSystem.hpp
*  @date   2009/11/25
*/
#pragma once
#ifndef MOCKFILESYSTEM_HPP
#define MOCKFILESYSTEM_HPP

#include <gmock/gmock.h>

#include "IO/IFileSystem.hpp"

namespace
{
  class MockFileSystem : public IO::IFileSystem
  {

  public:

    MOCK_METHOD0(Initialize, void());
    MOCK_METHOD2(Mount, bool(const std::string&, const std::string&));
    MOCK_CONST_METHOD2(GetFile, IO::FileBuffer*(const std::string&, bool));
    MOCK_CONST_METHOD1(SaveFile, void(const IO::FileBuffer&));
    MOCK_CONST_METHOD2(FileExists, bool(const std::string&, bool));
    MOCK_CONST_METHOD3(FileSearch, IO::FileSearchResult::FileSearchResultList*(const std::string&, const std::string&, bool));
    
  };
};

#endif