/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockNetworkSystemComponentFactory.hpp
*  @date   2009/08/17
*/
#pragma once
#ifndef MOCKNETWORKSYSTEMCOMPONENTFACTORY_HPP
#define MOCKNETWORKSYSTEMCOMPONENTFACTORY_HPP

#include "INetworkSystemComponentFactory.hpp"

namespace
{
  class MockNetworkSystemComponentFactory : public INetworkSystemComponentFactory
  {

  public:

    MOCK_METHOD1(Create, INetworkSystemComponent*(const std::string&));

  };
};

#endif