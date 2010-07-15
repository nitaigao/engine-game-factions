#include <gtest/gtest.h>
using namespace testing;

#include "ScriptComponent.h"
using namespace Script;

#include "Mocks/MockEventManager.hpp"
#include "Mocks/MockLuaState.hpp"
#include "Mocks/MockScriptFacadeManager.hpp"
#include "Mocks/MockScriptMessageDispatcher.hpp"
#include "Mocks/MockScriptEventDispatcher.hpp"
#include "Mocks/MockScriptUpdateDispatcher.hpp"

#include "Maths/MathVector3.hpp"
using namespace Maths;

#include "Events/IEventListener.hpp"

using namespace Events;

class ScriptComponent_Tests : public TestHarness< ScriptComponent >
{

protected:

  MockLuaState* m_state;
  MockScriptFacadeManager* m_facadeManager;
  MockScriptMessageDispatcher* m_messageDispatcher;
  MockScriptEventDispatcher* m_eventDispatcher;
  MockScriptUpdateDispatcher* m_updateDispatcher;

  void EstablishContext()
  {
    m_state = new MockLuaState();
    m_facadeManager = new MockScriptFacadeManager();
    m_messageDispatcher = new MockScriptMessageDispatcher();
    m_eventDispatcher = new MockScriptEventDispatcher();
    m_updateDispatcher = new MockScriptUpdateDispatcher();
  }

  void DestroyContext()
  {
    
  }

  ScriptComponent* CreateSubject()
  {
    return new ScriptComponent(m_state, m_facadeManager, m_messageDispatcher, m_eventDispatcher, m_updateDispatcher);
  }
};

TEST_F(ScriptComponent_Tests, should_initialize)
{
  std::string scriptpath = "script/path";

  m_subject->SetAttribute(System::Parameters::ScriptPath, scriptpath);

  EXPECT_CALL(*m_state, LoadScript(scriptpath));

  EXPECT_CALL(*m_facadeManager, Initialize(m_subject));

  m_subject->Initialize();
}

TEST_F(ScriptComponent_Tests, should_destroy)
{
  EXPECT_CALL(*m_facadeManager, Destroy());

  m_subject->Destroy();
}

TEST_F(ScriptComponent_Tests, should_run_script)
{
  EXPECT_CALL(*m_state, Execute());
  m_subject->RunScript();
}

TEST_F(ScriptComponent_Tests, should_include_script)
{
  std::string scriptPath = "/path/to/script";

  EXPECT_CALL(*m_state, LoadScript(scriptPath));
  EXPECT_CALL(*m_state, ReParse());

  m_subject->IncludeScript(scriptPath);
}

TEST_F(ScriptComponent_Tests, should_execute_a_string)
{
  std::string scriptString = "print('hello world!')";

  EXPECT_CALL(*m_state, ExecuteString(scriptString));

  m_subject->ExecuteString(scriptString);
}

TEST_F(ScriptComponent_Tests, should_register_function_for_messages)
{
  luabind::object delegateFunction;
  System::MessageType message = System::Messages::SetPosition;

  EXPECT_CALL(*m_messageDispatcher, AddMessageHandler(message, delegateFunction));

  m_subject->SubscribeMessage(message, delegateFunction);
}

TEST_F(ScriptComponent_Tests, should_un_register_function_for_messages)
{
  luabind::object delegateFunction;
  System::MessageType message = System::Messages::SetPosition;

  EXPECT_CALL(*m_messageDispatcher, RemoveHandler(message, delegateFunction));

  m_subject->SubscribeMessage(message, delegateFunction);
  m_subject->UnSubscribeMessage(message, delegateFunction);
}

TEST_F(ScriptComponent_Tests, should_dispatch_subscribed_messages)
{
  System::MessageType message = System::Messages::SetPosition;
  AnyType::AnyTypeMap parameters;
  parameters[ System::Attributes::Position ] = MathVector3::Forward();

  EXPECT_CALL(*m_messageDispatcher, Dispatch_Message(message, An< AnyType::AnyTypeMap& >()));

  m_subject->Observe(0, message, parameters);
}

TEST_F(ScriptComponent_Tests, should_update_dispatchers)
{
  float delta = 10.0f; 

  EXPECT_CALL(*m_messageDispatcher, Update(delta));

  m_subject->Update(delta);
}