/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockConfiguration.hpp
*  @date   2009/11/25
*/
#pragma once
#ifndef MOCKCONFIGURATION_HPP
#define MOCKCONFIGURATION_HPP

#include <gmock/gmock.h>

#include "Configuration/Configuration.h"

namespace
{
  class MockConfigurartion : public Configuration::IConfiguration
  {

  public:

    MOCK_METHOD1(Initialize, void(const std::string&));
    MOCK_METHOD2(Find, AnyType(const std::string&, const std::string&));
    MOCK_METHOD1(FindSection, AnyType::AnyTypeMap(const std::string&));
    MOCK_METHOD3(SetDefault, void(const std::string&, const std::string&, const AnyType&));
    MOCK_METHOD3(Set, void(const std::string&, const std::string&, const AnyType&));
    
  };
};

#endif