/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockScriptEventDispatcher.hpp
*  @date   2009/11/08
*/
#pragma once
#ifndef MOCKSCRIPTEVENTDISPATCHER_HPP
#define MOCKSCRIPTEVENTDISPATCHER_HPP

#include <gmock/gmock.h>


#include "IScriptEventDispatcher.hpp"

namespace
{
  class MockScriptEventDispatcher : public Script::IScriptEventDispatcher
  {

  public:

    MOCK_METHOD2( RegisterEventHandler, void( const std::string&, Script::IScriptFunctionHandler* ) );
    MOCK_METHOD2( UnregisterEventHandler, void( const std::string&, Script::IScriptFunctionHandler* ) );
    MOCK_METHOD1( EventHandler, void( const Events::IEvent* ) );


    static void ConsumeFunctionHandler( const std::string& eventType, Script::IScriptFunctionHandler* handler )
    {
      delete handler;
    }
    
  };
};

#endif