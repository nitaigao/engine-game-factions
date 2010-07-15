#include <gtest/gtest.h>
using namespace testing;

#include "ScriptFacadeManager.h"
using namespace Script;

#include "Mocks/MockScriptFacade.hpp"
#include "Mocks/MockScriptFacadeFactory.hpp"
#include "Mocks/MockScriptComponent.hpp"
#include "Mocks/MockLuaState.hpp"

class ScriptFacadeManager_Tests : public TestHarness<ScriptFacadeManager>
{

protected:

  MockScriptFacadeFactory* m_facadeFactory;
  MockLuaState* m_state;

  void EstablishContext()
  {
    m_facadeFactory = new MockScriptFacadeFactory();
    m_state = new MockLuaState();
  }

  void DestroyContext()
  {
    delete m_state;
    delete m_facadeFactory;
  }

  ScriptFacadeManager* CreateSubject()
  {
    return new ScriptFacadeManager(m_facadeFactory, m_state); 
  }
};

TEST_F(ScriptFacadeManager_Tests, should_initialize)
{
  MockScriptFacade facade;
  MockScriptComponent component;

  EXPECT_CALL(*m_facadeFactory, CreateScriptFacade(IScriptFacade::ANIMATION, &component, m_state)).WillOnce(Return(&facade));
  EXPECT_CALL(*m_facadeFactory, CreateScriptFacade(IScriptFacade::INPUT, &component, m_state)).WillOnce(Return(&facade));
  EXPECT_CALL(*m_facadeFactory, CreateScriptFacade(IScriptFacade::INSTRUMENTATION, &component, m_state)).WillOnce(Return(&facade));
  EXPECT_CALL(*m_facadeFactory, CreateScriptFacade(IScriptFacade::NETWORK, &component, m_state)).WillOnce(Return(&facade));
  EXPECT_CALL(*m_facadeFactory, CreateScriptFacade(IScriptFacade::PHYSICS, &component, m_state)).WillOnce(Return(&facade));
  EXPECT_CALL(*m_facadeFactory, CreateScriptFacade(IScriptFacade::SOUND, &component, m_state)).WillOnce(Return(&facade));
  EXPECT_CALL(*m_facadeFactory, CreateScriptFacade(IScriptFacade::SYSTEM, &component, m_state)).WillOnce(Return(&facade));
  EXPECT_CALL(facade, Initialize()).Times((int) IScriptFacade::FACADETYPE_MAX);

  m_subject->Initialize(&component);
}


TEST_F(ScriptFacadeManager_Tests, should_destroy)
{
  m_subject->Destroy();
}