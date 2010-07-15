/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockSystemComponent.hpp
*  @date   2009/08/25
*/
#pragma once
#ifndef MOCKSYSTEMCOMPONENT_HPP
#define MOCKSYSTEMCOMPONENT_HPP

#include <gmock/gmock.h>

#include "System/ISystemComponent.hpp"

namespace
{
  class MockSystemComponent : public ISystemComponent
  {

  public:

    MOCK_METHOD1( Serialize, void( IO::IStream* ) );
    MOCK_METHOD1( DeSerialize, void( IO::IStream* ) );
    MOCK_METHOD0( Initialize, void( ) );
    MOCK_METHOD1( Update, void( float ) );
    MOCK_METHOD0( Destroy, void( ) );
    MOCK_CONST_METHOD0( GetAttributes, AnyType::AnyTypeMap( ) );
    MOCK_METHOD2( SetAttribute, void( const System::Attribute&, const AnyType& ) );
    MOCK_METHOD3( Observe, AnyType( const ISubject*, const System::MessageType&, AnyType::AnyTypeMap ) );
    MOCK_METHOD1( AddObserver, void( IObserver* ) );
    MOCK_METHOD2( PushMessage, AnyType( const System::MessageType&, AnyType::AnyTypeMap ) );
    MOCK_CONST_METHOD0( GetName, std::string( ) );
  };
};

#endif