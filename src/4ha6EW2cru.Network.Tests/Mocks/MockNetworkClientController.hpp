/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockNetworkClientController.hpp
*  @date   2009/08/19
*/
#pragma once
#ifndef MOCKNETWORKCLIENTCONTROLLER_HPP
#define MOCKNETWORKCLIENTCONTROLLER_HPP

#include <gmock/gmock.h>

#include "INetworkClientController.hpp"

namespace
{
  class MockNetworkClientController : public INetworkClientController
  {

  public:

    MOCK_METHOD0( Initialize, void( ) );
    MOCK_METHOD1( SelectCharacter, void( const std::string& ) );
    MOCK_METHOD1( FindServers, void( unsigned int port ) );
    MOCK_METHOD0( LevelLoaded, void ( ) );
    MOCK_METHOD3( MessageEntity, void( const std::string&, const System::MessageType&, AnyType::AnyTypeMap ) );
    MOCK_METHOD1( SetPassive, void( bool ) );
    MOCK_METHOD1( Update, void( float ) );
    
  };
};

#endif