#include "precompiled.h"

#include "ScriptFunctionHandler.h"

#include "Logging/Logger.h"

using namespace luabind;

#include "Events/InputEventData.hpp"
#include "Events/EventData.hpp"
using namespace Events;

namespace Script
{
  void ScriptFunctionHandler::CallFunction(AnyType::AnyTypeMap parameters)
  {
    luabind::call_function<void>(m_functionHandler, parameters);
  }

  void ScriptFunctionHandler::CallFunction(const std::string& eventType, Events::IEventData* eventData)
  {
    try
    {
      if(eventData != 0)
      {
        if(typeid(MouseEventData) == typeid(*eventData))
        {
          luabind::call_function<void>(m_functionHandler, eventType, (MouseEventData*) eventData);
        }
        else if(typeid(KeyEventData) == typeid(*eventData))
        {
          luabind::call_function<void>(m_functionHandler, eventType, (KeyEventData*) eventData);
        }
        else if (typeid(UIEventData) == typeid(*eventData))
        {
          luabind::call_function<void>(m_functionHandler, eventType, (UIEventData*) eventData);
        }
        else if (typeid(ServerEventData) == typeid(*eventData))
        {
          luabind::call_function<void>(m_functionHandler, eventType, (ServerEventData*) eventData);
        }
      }
      else
      {
        luabind::call_function<void>(m_functionHandler, eventType);
      }
    }
    catch(error& e)
    {
      object error_msg(from_stack(e.state() , -1));
      std::stringstream logMessage;
      logMessage <<error_msg;
      Warn(logMessage.str());
    }
  }

  void ScriptFunctionHandler::CallFunction(const System::MessageType& message, AnyType::AnyTypeMap& parameters)
  {
    luabind::call_function<void>(m_functionHandler, message, parameters);
  }

  void ScriptFunctionHandler::CallFunction(float deltaMilliseconds)
  {
    try
    {
      luabind::call_function<void>(m_functionHandler, deltaMilliseconds);
    }
    catch(error& e)
    {
      object error_msg(from_stack(e.state() , -1));
      std::stringstream logMessage;
      logMessage <<error_msg;
      Warn(logMessage.str());
    }
  }
}