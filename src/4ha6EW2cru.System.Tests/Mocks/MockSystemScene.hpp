#ifndef MOCKSYSTEMSCENE_HPP
#define MOCKSYSTEMSCENE_HPP

#include <gmock/gmock.h>

#include "System/ISystemScene.hpp"

class MockSystemScene : public ISystemScene
{

public:

  MOCK_METHOD0(Initialize, void());
  MOCK_METHOD1(Update, void(float));
  MOCK_METHOD0(Destroy, void());
  MOCK_CONST_METHOD0(GetType, System::Types::Type());
  MOCK_METHOD2(CreateComponent, ISystemComponent*(const std::string&, const std::string&));
  MOCK_METHOD1(DestroyComponent, void(ISystemComponent*));
};

#endif