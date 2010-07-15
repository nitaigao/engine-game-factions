/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockScriptSystemScene.hpp
*  @date   2009/08/27
*/
#pragma once
#ifndef MOCKSCRIPTSYSTEMSCENE_HPP
#define MOCKSCRIPTSYSTEMSCENE_HPP

#include <gmock/gmock.h>

#include "IScriptSystemScene.hpp"

namespace
{
  class MockScriptSystemScene : public IScriptSystemScene
  {

  public:

    MOCK_METHOD0(Initialize, void());
    MOCK_METHOD1(Update, void(float));
    MOCK_METHOD0(Destroy, void());
    MOCK_CONST_METHOD0(GetType, System::Types::Type());
    MOCK_METHOD2(CreateComponent, ISystemComponent*(const std::string&, const std::string&));
    MOCK_METHOD1(DestroyComponent, void(ISystemComponent*));
    MOCK_METHOD1(UnloadComponent, void(const std::string&));
    
  };
};

#endif