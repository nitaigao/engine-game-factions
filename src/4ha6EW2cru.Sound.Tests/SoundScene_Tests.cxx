#include <gtest/gtest.h>
using namespace testing;

#include "SoundScene.h"
using namespace Sound;

#include "Mocks/MockSoundEventSystem.hpp"
#include "Mocks/MockSoundComponentFactory.hpp"
#include "Mocks/MockSoundSystemComponent.hpp"

class SoundScene_Tests : public TestHarness< SoundScene >
{

protected:

  MockSoundComponentFactory* m_factory;

  void EstablishContext()
  {
    m_factory = new MockSoundComponentFactory();
  }

  void DestroyContext()
  {

  }

  SoundScene* CreateSubject()
  {
    return new SoundScene(m_factory); 
  }
};

TEST_F(SoundScene_Tests, should_create_components)
{
  std::string name = "test";
  std::string type = "default";

  MockSoundSystemComponent component;

  EXPECT_CALL(*m_factory, CreateComponent(name, type)).WillOnce(Return(&component));
  m_subject->CreateComponent(name, type);
}

TEST_F(SoundScene_Tests, should_destroy_components)
{
  MockSoundSystemComponent* component = new MockSoundSystemComponent();
  EXPECT_CALL(*component, Destroy());

  m_subject->DestroyComponent(component);
}