/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockResourceManager.hpp
*  @date   2009/08/28
*/
#pragma once
#ifndef MOCKRESOURCEMANAGER_HPP
#define MOCKRESOURCEMANAGER_HPP

#include <gmock/gmock.h>

#include "IO/IResourceCache.hpp"

namespace
{
  class MockResourceCache : public Resources::IResourceCache
  {

  public:

    MOCK_METHOD1( GetResource, Resources::IResource*( const std::string& ) );
    MOCK_METHOD1( ResourceExists, bool( const std::string& ) );
    MOCK_METHOD1( Update, void( float ) );
    MOCK_CONST_METHOD3( ResourceSearch, IO::FileSearchResult::FileSearchResultList*( const std::string&, const std::string&, bool ) );
    
  };
};

#endif