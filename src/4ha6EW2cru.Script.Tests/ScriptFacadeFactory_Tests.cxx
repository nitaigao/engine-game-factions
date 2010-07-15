#include <gtest/gtest.h>
using namespace testing;

#include "ScriptFacadeFactory.h"
using namespace Script;

#include "Mocks/MockLuaState.hpp"
#include "Mocks/MockScriptComponent.hpp"
#include "Mocks/MockServiceManager.hpp"
#include "Mocks/MockEventManager.hpp"
#include "Mocks/MockPlatformManager.hpp"
#include "Mocks/MockInstrumentation.hpp"
#include "Mocks/MockResourceCache.hpp"

class ScriptFacadeFactory_Tests : public TestHarness<ScriptFacadeFactory>
{

protected:

  MockLuaState* m_state;

  MockServiceManager* m_serviceManager;
  MockEventManager* m_eventManager;
  MockPlatformManager* m_platformManager;
  MockInstrumentation* m_instrumentation;
  MockResourceCache* m_resourceCache;

  void EstablishContext()
  {
    m_state = new MockLuaState();
    m_serviceManager = new MockServiceManager();
    m_eventManager = new MockEventManager();
    m_platformManager = new MockPlatformManager();
    m_instrumentation = new MockInstrumentation();
    m_resourceCache = new MockResourceCache();
  }

  void DestroyContext()
  {
    delete m_state;
    delete m_serviceManager;
    delete m_eventManager;
    delete m_platformManager;
    delete m_instrumentation;
    delete m_resourceCache;
  }

  ScriptFacadeFactory* CreateSubject()
  {
    return new ScriptFacadeFactory(m_serviceManager, m_eventManager, m_platformManager, m_instrumentation, m_resourceCache);
  }
};

TEST_F(ScriptFacadeFactory_Tests, should_create_component)
{
  MockScriptComponent component;

  IScriptFacade* facade = m_subject->CreateScriptFacade(IScriptFacade::ANIMATION, &component, m_state);
  delete facade;
}