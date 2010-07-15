/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockUXSystemScene.hpp
*  @date   2009/09/02
*/
#pragma once
#ifndef MOCKUXSYSTEMSCENE_HPP
#define MOCKUXSYSTEMSCENE_HPP

#include <gmock/gmock.h>

namespace
{
  class MockUXSystemScene : public IUXSystemScene
  {

  public:

  
    MOCK_METHOD0( Initialize, void( ) );
    MOCK_METHOD1( Update, void( float ) );
    MOCK_METHOD0( Destroy, void( ) );
    MOCK_CONST_METHOD0( GetType, System::Types::Type( ) );
    MOCK_METHOD2( CreateComponent, ISystemComponent*( const std::string&, const std::string& ) );
    MOCK_METHOD1( DestroyComponent, void( ISystemComponent* ) );

    
  };
};

#endif