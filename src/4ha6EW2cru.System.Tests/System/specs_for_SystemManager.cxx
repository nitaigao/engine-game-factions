#include <gtest/gtest.h>
using namespace testing;

#include "System/SystemManager.h"
using namespace System;

#include "../Mocks/MockPlatformManager.hpp"
#include "../Mocks/MockConfiguration.hpp"
#include "../Mocks/MockServiceManager.hpp"
#include "../Mocks/MockResourceCache.hpp"
#include "../Mocks/MockEventManager.hpp"
#include "../Mocks/MockInstrumentation.hpp"

namespace base_context
{
  class SystemManager_BaseContext : public TestHarness<SystemManager>
  {

  protected:

    MockConfigurartion* m_configuration;
    MockServiceManager* m_serviceManager;
    MockResourceCache* m_resourceCache;
    MockEventManager* m_eventManager;
    MockInstrumentation* m_instrumentation;
    MockPlatformManager* m_platformManager;

    virtual void EstablishContext()
    {
      m_platformManager = new MockPlatformManager();
      m_configuration = new MockConfigurartion();
      m_serviceManager = new MockServiceManager();
      m_resourceCache = new MockResourceCache();
      m_eventManager = new MockEventManager();
      m_instrumentation = new MockInstrumentation();
    }

    virtual void DestroyContext()
    {
      delete m_platformManager;
      delete m_configuration;
      delete m_serviceManager;
      delete m_resourceCache;
      delete m_eventManager;
      delete m_instrumentation;
    }

    SystemManager* CreateSubject()
    {
      return new SystemManager(m_configuration, m_serviceManager, m_resourceCache, m_eventManager, m_instrumentation, m_platformManager);
    }
  };
};

namespace given_the_game_is_a_dedicated_server
{
  class when_the_systems_are_initialized : public base_context::SystemManager_BaseContext
  {
  
  protected:

    // need to find a better way to test this without actually loading all the systems
  
    void Expecting()
    {
      //EXPECT_CALL(*m_platformManager, CreateConsoleWindow());
    }
  
    void When()
    {
      
      //m_subject->LoadSystems(true);
      //m_subject->InitializeAllSystems();
      //m_subject->Release();
    }
    
  };

  TEST_F(when_the_systems_are_initialized, then_the_console_window_should_spawn) { }
}