/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockNetworkServerProvider.hpp
*  @date   2009/08/20
*/
#pragma once
#ifndef MOCKNETWORKSERVERPROVIDER_HPP
#define MOCKNETWORKSERVERPROVIDER_HPP

#include <gmock/gmock.h>

#include "INetworkServerProvider.hpp"

namespace
{
  class MockNetworkServerProvider : public INetworkServerProvider
  {

  public:

    MOCK_METHOD1( Connect, void( const std::string& ) );
    MOCK_METHOD0( Disconnect, void( ) );
    MOCK_METHOD1( Initialize, void ( int ) );
    MOCK_METHOD1( Update, void( float ) );
    MOCK_METHOD3( Message, void( ISystemComponent*, const System::MessageType&, AnyType::AnyTypeMap ) );
    MOCK_METHOD0( Destroy, void( ) );
    MOCK_METHOD1( OnGameLevelChanged, void( const Events::IEvent* ) );
    
  };
};

#endif