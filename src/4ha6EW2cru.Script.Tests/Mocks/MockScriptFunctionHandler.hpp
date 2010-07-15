/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockScriptFunctionHandler.hpp
*  @date   2009/09/04
*/
#pragma once
#ifndef MOCKSCRIPTFUNCTIONHANDLER_HPP
#define MOCKSCRIPTFUNCTIONHANDLER_HPP

#include <gmock/gmock.h>

#include "IScriptFunctionHandler.hpp"

namespace
{
  class MockScriptFunctionHandler : public Script::IScriptFunctionHandler
  {

  public:

    MOCK_METHOD0(MarkForDeletion, void());
    MOCK_CONST_METHOD0(IsMarkedForDeletion, bool());
    MOCK_METHOD1(CallFunction, void(float));
    MOCK_METHOD1(CallFunction, void(AnyType::AnyTypeMap));
    MOCK_METHOD2(CallFunction, void(const System::MessageType&, AnyType::AnyTypeMap&));
    MOCK_METHOD1(Compare, bool(IScriptFunctionHandler*));
    MOCK_METHOD2(CallFunction, void(const std::string&, Events::IEventData*));
    MOCK_CONST_METHOD0(GetFunction, luabind::object());
    
  };
};

#endif