/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockScriptFacadeFactory.hpp
*  @date   2009/08/27
*/
#pragma once
#ifndef MOCKSCRIPTFACADEFACTORY_HPP
#define MOCKSCRIPTFACADEFACTORY_HPP

#include <gmock/gmock.h>

#include "IScriptFacadeFactory.hpp"

namespace
{
  class MockScriptFacadeFactory : public Script::IScriptFacadeFactory
  {

  public:

    MOCK_METHOD3(CreateScriptFacade, Script::IScriptFacade*(Script::IScriptFacade::FacadeType, ISystemComponent*, Script::ILuaState*));
    
  };
};

#endif