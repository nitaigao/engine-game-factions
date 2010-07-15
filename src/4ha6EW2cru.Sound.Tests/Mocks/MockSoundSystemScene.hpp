/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockSoundSystemScene.hpp
*  @date   2009/08/26
*/
#pragma once
#ifndef MOCKSOUNDSYSTEMSCENE_HPP
#define MOCKSOUNDSYSTEMSCENE_HPP

#include <gmock/gmock.h>

#include "ISoundScene.hpp"

namespace
{
  class MockSoundSystemScene : public ISoundScene
  {

  public:

    MOCK_METHOD0( GetSoundSystem, ISoundSystem*( ) );
    MOCK_METHOD0( Initialize, void( ) );
    MOCK_METHOD1( Update, void( float ) );
    MOCK_METHOD0( Destroy, void( ) );
    MOCK_CONST_METHOD0( GetType, System::Types::Type( ) );
    MOCK_METHOD2( CreateComponent, ISystemComponent*( const std::string&, const std::string& ) );
    MOCK_METHOD1( DestroyComponent, void( ISystemComponent* ) );

    
  };
};

#endif