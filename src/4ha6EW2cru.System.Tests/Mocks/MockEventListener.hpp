/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockEventListener.hpp
*  @date   2009/10/31
*/
#pragma once
#ifndef MOCKEVENTLISTENER_HPP
#define MOCKEVENTLISTENER_HPP

#include <gmock/gmock.h>

#include "Events/IEventListener.hpp"

namespace
{
  class MockEventListener : public IEventListener
  {

  public:

    MOCK_CONST_METHOD1( HandleEvent, void( const IEvent* ) );
    MOCK_CONST_METHOD0( GetEventType, EventType( ) );
    MOCK_METHOD0( MarkForDeletion, void( ) );
    MOCK_CONST_METHOD0( IsMarkedForDeletion, bool( ) );
    MOCK_CONST_METHOD0( GetHandlerAddress, unsigned int( ) );
    MOCK_CONST_METHOD0( GetHandlerFunctionName, std::string( ) );

  };
};

#endif