/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockSoundComponentFactory.hpp
*  @date   2009/08/26
*/
#pragma once
#ifndef MOCKSOUNDCOMPONENTFACTORY_HPP
#define MOCKSOUNDCOMPONENTFACTORY_HPP

#include <gmock/gmock.h>

#include "ISoundComponentFactory.hpp"

namespace
{
  class MockSoundComponentFactory : public ISoundComponentFactory
  {

  public:

    MOCK_METHOD2(CreateComponent, ISoundSystemComponent*(const std::string&, const std::string&));
    

    
  };
};

#endif