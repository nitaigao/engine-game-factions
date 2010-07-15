#include <gtest/gtest.h>
using namespace testing;

#include "UXSystemComponentFactory.h"
using namespace UX;

#include "Mocks/MockLuaState.hpp"
#include "Mocks/MockGUI.hpp"
#include "Mocks/MockEventManager.hpp"
#include "Mocks/MockScriptFacadeFactory.hpp"

class UXSystemComponentFactory_Tests : public TestHarness<UXSystemComponentFactory>
{

protected:

  MockLuaState* m_masterState;
  MockGUI* m_gui;
  MockEventManager* m_eventManager;
  MockScriptFacadeFactory* m_facadeFactory;

  void EstablishContext()
  {
    m_masterState = new MockLuaState();
    m_eventManager = new MockEventManager();
    m_gui = new MockGUI();
    m_facadeFactory = new MockScriptFacadeFactory();
  }


  void DestroyContext()
  {
    delete m_eventManager;
  }

  UXSystemComponentFactory* CreateSubject()
  {
    return new UXSystemComponentFactory(m_masterState, m_gui, m_eventManager, m_facadeFactory); 
  }
};