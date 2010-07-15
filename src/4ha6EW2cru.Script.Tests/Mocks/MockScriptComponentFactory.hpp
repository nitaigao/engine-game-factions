/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockScriptComponentFactory.hpp
*  @date   2009/08/27
*/
#pragma once
#ifndef MOCKSCRIPTCOMPONENTFACTORY_HPP
#define MOCKSCRIPTCOMPONENTFACTORY_HPP

#include <gmock/gmock.h>

#include "IScriptComponentFactory.hpp"

namespace
{
  class MockScriptComponentFactory : public IScriptComponentFactory
  {

  public:

  
    MOCK_METHOD2( CreateComponent, IScriptComponent*( const std::string& name, const std::string& type ) );

    
  };
};

#endif