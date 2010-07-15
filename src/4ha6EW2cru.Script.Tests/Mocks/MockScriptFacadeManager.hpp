/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockScriptFacadeManager.hpp
*  @date   2009/08/27
*/
#pragma once
#ifndef MOCKSCRIPTFACADEMANAGER_HPP
#define MOCKSCRIPTFACADEMANAGER_HPP

#include <gmock/gmock.h>

#include "IScriptFacadeManager.hpp"

namespace
{
  class MockScriptFacadeManager : public Script::IScriptFacadeManager
  {

  public:

    MOCK_METHOD1( Initialize, void ( ISystemComponent* ) );
    MOCK_METHOD0( Destroy, void( ) );

  };
};

#endif