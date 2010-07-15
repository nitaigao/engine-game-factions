#include <gtest/gtest.h>
using namespace testing;

#include "ScriptSystemScene.h"
using namespace Script;

using namespace luabind;

#include "Mocks/MockScriptComponentFactory.hpp"

#include "Mocks/MockScriptComponent.hpp"
#include "Mocks/MockLuaState.hpp"

#include "Mocks/MockServiceManager.hpp"
#include "Mocks/MockConfiguration.hpp"

class ScriptSystemScene_Tests : public TestHarness<ScriptSystemScene>
{

protected:

  MockScriptComponentFactory* m_factory;
  MockLuaState* m_masterState;
  MockServiceManager* m_serviceManager;

  MockConfigurartion* m_configuration;

  void EstablishContext()
  {
    m_factory = new MockScriptComponentFactory();
    m_masterState = new MockLuaState();
    m_serviceManager = new MockServiceManager();
    m_configuration = new MockConfigurartion();
  }


  void DestroyContext()
  {
    delete m_serviceManager;
    delete m_configuration;
  }

  ScriptSystemScene* CreateSubject()
  {
    return new ScriptSystemScene(m_configuration, m_factory, m_masterState, m_serviceManager); 
  }
};

TEST_F(ScriptSystemScene_Tests, should_create_a_component)
{
  std::string name = "test";
  std::string type = "default";

  MockScriptComponent component;

  EXPECT_CALL(*m_factory, CreateComponent(name, type)).WillOnce(Return(&component));

  m_subject->CreateComponent(name, type);
}

TEST_F(ScriptSystemScene_Tests, should_initialize)
{
  // init master state
  EXPECT_CALL(*m_masterState, Initialize());

  scope classScope = class_<std::string>("string");
  AnyType::AnyTypeMap results;
  results[ System::Attributes::SystemType ] = classScope;

  // poll systems for script functions
  EXPECT_CALL(*m_serviceManager, MessageAll(System::Messages::RegisterScriptFunctions, An<AnyType::AnyTypeMap>()))
    .WillOnce(Return(results));

  EXPECT_CALL(*m_masterState, RegisterTypes(A<const scope&>()))
    .Times(AtLeast(1)); // allows for extra scope registrations

  m_subject->Initialize();
}

TEST_F(ScriptSystemScene_Tests, should_destroy)
{
  EXPECT_CALL(*m_masterState, Destroy());
  m_subject->Destroy();
}

TEST_F(ScriptSystemScene_Tests, should_unload_component)
{
  std::string name = "name";
  std::string type = "type";

  AnyType::AnyTypeMap attributes;
  attributes[ System::Attributes::Name ] = name;

  MockScriptComponent* component = new MockScriptComponent();

  EXPECT_CALL(*m_factory, CreateComponent(name, type)).WillOnce(Return(component));
  m_subject->CreateComponent(name, type);

  EXPECT_CALL(*component, GetAttributes()).WillOnce(Return(attributes));

  EXPECT_CALL(*component, Destroy());
  m_subject->UnloadComponent(name);
}