/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockEntityFactory.hpp
*  @date   2009/08/13
*/
#pragma once
#ifndef MOCKENTITYFACTORY_HPP
#define MOCKENTITYFACTORY_HPP

#include "State/IWorldEntityFactory.hpp"

namespace
{
  class MockEntityFactory : public IWorldEntityFactory
  {

  public:

    MOCK_CONST_METHOD1(CreateEntity, State::IWorldEntity*(const std::string&));
    
  };
};

#endif