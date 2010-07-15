/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockUXSystemComponentFactory.hpp
*  @date   2009/09/02
*/
#pragma once
#ifndef MOCKUXSYSTEMCOMPONENTFACTORY_HPP
#define MOCKUXSYSTEMCOMPONENTFACTORY_HPP

#include <gmock/gmock.h>

namespace
{
  class MockUXSystemComponentFactory : public IUXSystemComponentFactory
  {

  public:

    MOCK_METHOD1(CreateComponent, IUXSystemComponent*(const std::string&));
    
  };
};

#endif