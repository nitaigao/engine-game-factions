#include "precompiled.h"

#include "ScriptSystemScene.h"

#include <luabind/table_policy.hpp>
#include <luabind/operator.hpp>
#include <luabind/error.hpp>
using namespace luabind;

#include "Events/Event.h"
#include "Events/EventData.hpp"
using namespace Events;

#include "Logging/Logger.h"
using namespace Logging;

using namespace Maths;

#include "Exceptions/ScriptException.hpp"
#include "Exceptions/OutOfRangeException.hpp"

#include "ScriptComponent.h"
#include "ScriptConfiguration.h"
#include "LuaState.h"

#include "SystemFacade.h"
#include "SoundFacade.h"
#include "InstrumentationFacade.h"
#include "AnimationFacade.h"
#include "NetworkFacade.h"
#include "InputFacade.h"
#include "PhysicsFacade.h"

namespace Script
{
  ScriptSystemScene::~ScriptSystemScene()
  {
    delete m_masterState;
    m_masterState = 0;

    delete m_eventHandlers;
    m_eventHandlers = 0;

    delete m_componentFactory;
    m_componentFactory = 0;

    if (m_scriptConfiguration != 0)
    {
      delete m_scriptConfiguration;
      m_scriptConfiguration = 0;
    }
  }

  ISystemComponent* ScriptSystemScene::CreateComponent(const std::string& name, const std::string& type)
  {
    IScriptComponent* component = m_componentFactory->CreateComponent(name, type);
    m_components.insert(std::make_pair(name, component));
    return component;
  }

  void ScriptSystemScene::DestroyComponent(ISystemComponent* component)
  {
    m_components.erase(component->GetAttributes()[ System::Attributes::Name ].As< std::string >());
    component->Destroy();
    delete component;
    component = 0;
  }

  void ScriptSystemScene::Initialize()
  {
    m_masterState->Initialize();
    
    AnyType::AnyTypeMap results = m_serviceManager->MessageAll(System::Messages::RegisterScriptFunctions, AnyType::AnyTypeMap());

    for(AnyType::AnyTypeMap::iterator i = results.begin(); i != results.end(); ++i)
    {
      m_masterState->RegisterTypes((*i).second.As< scope >());
    }

    m_masterState->RegisterTypes(SystemFacade::RegisterFunctions());
    m_masterState->RegisterTypes(SoundFacade::RegisterFunctions());
    m_masterState->RegisterTypes(InstrumentationFacade::RegisterFunctions());
    m_masterState->RegisterTypes(AnimationFacade::RegisterFunctions());
    m_masterState->RegisterTypes(NetworkFacade::RegisterFunctions());
    m_masterState->RegisterTypes(InputFacade::RegisterFunctions());
    m_masterState->RegisterTypes(PhysicsFacade::RegisterFunctions());

    m_scriptConfiguration = new ScriptConfiguration(m_configuration);

    if (typeid(*m_masterState) == typeid(LuaState))
    {
      static_cast< LuaState* >(m_masterState)->SetGlobal("Configuration", m_scriptConfiguration);
    }
  }

  void ScriptSystemScene::Destroy()
  {
    m_masterState->Destroy();
  }

  void ScriptSystemScene::Update(float deltaMilliseconds)
  {
    for(ScriptComponentList::iterator i = m_components.begin(); i != m_components.end(); ++i)
    {
      (*i).second->Update(deltaMilliseconds);
    }
  }

  void ScriptSystemScene::UnloadComponent(const std::string& name)
  {
    ScriptComponentList::iterator i = m_components.find(name);

    if (i != m_components.end())
    {
      this->DestroyComponent((*i).second);
    }
  }
}