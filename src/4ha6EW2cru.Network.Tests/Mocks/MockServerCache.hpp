/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockServerCache.hpp
*  @date   2009/08/20
*/
#pragma once
#ifndef MOCKSERVERCACHE_HPP
#define MOCKSERVERCACHE_HPP

#include <gmock/gmock.h>

#include "IServerCache.hpp"

namespace
{
  class MockServerCache : public IServerCache
  {

  public:

    MOCK_CONST_METHOD1(Exists, bool(const std::string&));
    MOCK_CONST_METHOD0(GetCount, int());
    MOCK_METHOD7(Add, void(const std::string&, const std::string&, int, int, int, const std::string&, unsigned int));
    MOCK_CONST_METHOD1(Find, IServerAdvertisement*(int));
    MOCK_METHOD0(Clear, void());
    
  };
};

#endif