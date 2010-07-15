#include <gtest/gtest.h>
using namespace testing;

#include "SoundComponentFactory.h"
using namespace Sound;

#include "Mocks/MockSoundEventSystem.hpp"

class SoundComponentFactory_Tests : public TestHarness<SoundComponentFactory>
{

protected:

  MockSoundEventSystem* m_eventSystem;

  void EstablishContext()
  {
    m_eventSystem = new MockSoundEventSystem();
  }

  void DestroyContext()
  {
    delete m_eventSystem;
  }

  SoundComponentFactory* CreateSubject()
  {
    return new SoundComponentFactory(m_eventSystem); 
  }
};


TEST_F(SoundComponentFactory_Tests, should_create_a_component)
{
  ISystemComponent* notExpected = 0;
  ISystemComponent* result = m_subject->CreateComponent("test", "type");

  EXPECT_NE(notExpected, result);

  delete result;
}