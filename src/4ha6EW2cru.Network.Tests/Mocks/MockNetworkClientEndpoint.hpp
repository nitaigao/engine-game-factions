/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockNetworkClientEndpoint.hpp
*  @date   2009/08/19
*/
#pragma once
#ifndef MOCKNETWORKCLIENTENDPOINT_HPP
#define MOCKNETWORKCLIENTENDPOINT_HPP

#include <gmock/gmock.h>

#include "INetworkClientEndpoint.hpp"

namespace
{
  class MockNetworkClientEndpoint : public INetworkClientEndpoint
  {

  public:

    MOCK_METHOD0( Initialize, void( ) );
    MOCK_METHOD1( Update, void( float ) );
    MOCK_METHOD1( SetPassive, void( bool ) );
    
  };
};

#endif