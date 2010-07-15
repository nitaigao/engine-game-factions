#include <gtest/gtest.h>
using namespace testing;

#include "ScriptComponentFactory.h"
using namespace Script;

#include "Mocks/MockLuaState.hpp"
#include "Mocks/MockEventManager.hpp"
#include "Mocks/MockScriptFacadeFactory.hpp"

using namespace luabind::adl;

class ScriptComponentFactory_Tests : public TestHarness<ScriptComponentFactory>
{

protected:

  MockLuaState* m_masterState;
  MockEventManager* m_eventManager;
  MockScriptFacadeFactory* m_facadeFactory;

  void EstablishContext()
  {
    m_masterState = new MockLuaState();
    m_eventManager = new MockEventManager();
    m_facadeFactory = new MockScriptFacadeFactory();
  }

  void DestroyContext()
  {
    delete m_masterState;
    delete m_eventManager;
  }

  ScriptComponentFactory* CreateSubject()
  {
    return new ScriptComponentFactory(m_masterState, m_eventManager, m_facadeFactory); 
  }
};

TEST_F(ScriptComponentFactory_Tests, should_create_component)
{
  MockLuaState* childState = new MockLuaState();
  EXPECT_CALL(*m_masterState, CreateChild()).WillOnce(Return(childState));

  IScriptComponent* actual = m_subject->CreateComponent("name", "type");
  IScriptComponent* expected = 0;

  EXPECT_NE(expected, actual);

  delete actual;
}