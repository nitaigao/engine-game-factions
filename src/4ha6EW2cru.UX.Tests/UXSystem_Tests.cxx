#include <gtest/gtest.h>
using namespace testing;

#include "UXSystem.h"
using namespace UX;

#include "Configuration/Configuration.h"
using namespace Configuration;

#include "Mocks/MockGUI.hpp"

#include "Mocks/MockUXSystemScene.hpp"
#include "Mocks/MockEventManager.hpp"
#include "Mocks/MockServiceManager.hpp"
#include "Mocks/MockService.hpp"
#include "Mocks/MockConfiguration.hpp"

#include "Events/InputEventData.hpp"
#include "Events/Event.h"
#include "Events/EventType.hpp"
using namespace Events;

class UXSystem_Tests : public TestHarness<UXSystem>
{

protected:

  MockGUI* m_gui;
  MockUXSystemScene* m_scene;
  MockEventManager* m_eventManager;
  MockServiceManager* m_serviceManager;
  MockConfigurartion* m_configuration;

  void EstablishContext()
  {
    m_gui = new MockGUI();
    m_scene = new MockUXSystemScene();
    m_eventManager = new MockEventManager();
    m_serviceManager = new MockServiceManager();
    m_configuration = new MockConfigurartion();
  }


  void DestroyContext()
  {
    delete m_scene;
    delete m_eventManager;
    delete m_serviceManager;
    delete m_configuration;
  }

  UXSystem* CreateSubject()
  {
    return new UXSystem(m_gui, m_scene, m_eventManager, m_serviceManager); 
  }
};

TEST_F(UXSystem_Tests, should_initialize)
{
  MockService service;

  EXPECT_CALL(*m_eventManager, AddEventListener(A<const std::string&>(), An<IEventListener*>()))
    .WillRepeatedly(Invoke(MockEventManager::ConsumeEventListener));

  m_subject->Initialize(m_configuration);
}

TEST_F(UXSystem_Tests, should_destroy_the_gui)
{
  EXPECT_CALL(*m_eventManager, RemoveEventListener(A<const std::string&>(), An<IEventListener*>()))
    .WillRepeatedly(Invoke(MockEventManager::ConsumeEventListener));

  EXPECT_CALL(*m_gui, Destroy());

  m_subject->Release();
}

TEST_F(UXSystem_Tests, should_inject_mouse_moved)
{
  int x = 12;
  int y = 10;
  int z = 99;

  EXPECT_CALL(*m_gui, MouseMoved(x, y, z));

  MouseEventData* eventData = new MouseEventData(x, y, z, 0);
  Event event(EventTypes::INPUT_MOUSE_MOVED, eventData);

  m_subject->OnMouseMoved(&event);
}

TEST_F(UXSystem_Tests, should_inject_mouse_pressed)
{
  int id = 12;
  int x = 10;
  int y = 99;

  EXPECT_CALL(*m_gui, MousePressed(x, y, id));

  MouseEventData* eventData = new MouseEventData(x, y, 0, id);
  Event event(EventTypes::INPUT_MOUSE_PRESSED, eventData);

  m_subject->OnMousePressed(&event);
}

TEST_F(UXSystem_Tests, should_inject_mouse_release)
{
  int id = 12;
  int x = 10;
  int y = 99;

  EXPECT_CALL(*m_gui, MouseReleased(x, y, id));

  MouseEventData* eventData = new MouseEventData(x, y, 0, id);
  Event event(EventTypes::INPUT_MOUSE_RELEASED, eventData);

  m_subject->OnMouseReleased(&event);
}

TEST_F(UXSystem_Tests, should_inject_key_release)
{
  int keyCode = 10;

  EXPECT_CALL(*m_gui, KeyReleased(keyCode));

  KeyEventData* eventData = new KeyEventData(keyCode, "something");
  Event event(EventTypes::INPUT_KEY_UP, eventData);

  m_subject->OnKeyUp(&event);
}

TEST_F(UXSystem_Tests, should_inject_key_press)
{
  int keyCode = 10;

  EXPECT_CALL(*m_gui, KeyPressed(keyCode));

  KeyEventData* eventData = new KeyEventData(keyCode, "something");
  Event event(EventTypes::INPUT_KEY_DOWN, eventData);

  m_subject->OnKeyDown(&event);
}


TEST_F(UXSystem_Tests, should_update)
{
  float delta = 10.0f;

  EXPECT_CALL(*m_gui, Update(delta));

  m_subject->Update(delta);
}