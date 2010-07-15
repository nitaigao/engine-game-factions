#include "precompiled.h"

#include "ScriptMessageDispatcher.h"

#include "ScriptFunctionHandler.h"

namespace Script
{
  ScriptMessageDispatcher::~ScriptMessageDispatcher()
  {
    for(DelegateFunctionMap::iterator i = m_handlers.begin(); i != m_handlers.end();)
    {
      delete (*i).second;
      i = m_handlers.erase(i);
    }
  }

  void ScriptMessageDispatcher::Dispatch_Message(const System::MessageType& message, AnyType::AnyTypeMap& parameters)
  {
    DelegateFunctionMap::iterator it1 = m_handlers.lower_bound(message);
    DelegateFunctionMap::iterator it2 = m_handlers.upper_bound(message);

    for(DelegateFunctionMap::iterator i = it1; i != it2; ++i)
    {
      (*i).second->CallFunction(message, parameters);
    }
  }

  void ScriptMessageDispatcher::AddMessageHandler(const System::MessageType& message, luabind::object delegateFunction)
  {
    std::pair<System::MessageType, IScriptFunctionHandler*> messagePair = std::make_pair(message, new ScriptFunctionHandler(delegateFunction));
    m_handlers.insert(messagePair);
  }

  bool ScriptMessageDispatcher::HasHandler(const System::MessageType& message, luabind::object delegateFunction)
  {
    DelegateFunctionMap::iterator it1 = m_handlers.lower_bound(message);
    DelegateFunctionMap::iterator it2 = m_handlers.upper_bound(message);

    ScriptFunctionHandler handler(delegateFunction);

    for(DelegateFunctionMap::iterator i = it1; i != it2; ++i)
    {
      if (handler.Compare((*i).second))
      {
        return true;
      }
    }

    return false;
  }

  void ScriptMessageDispatcher::RemoveHandler(const System::MessageType& message, luabind::object delegateFunction)
  {
    DelegateFunctionMap::iterator it1 = m_handlers.lower_bound(message);
    DelegateFunctionMap::iterator it2 = m_handlers.upper_bound(message);

    ScriptFunctionHandler handler(delegateFunction);

    for(DelegateFunctionMap::iterator i = it1; i != it2; ++i)
    {
      if (static_cast<ScriptFunctionHandler*>((*i).second)->Compare(&handler))
      {
        (*i).second->MarkForDeletion();
      }
    }
  }

  void ScriptMessageDispatcher::Update(float deltaMilliseconds)
  {
    for(DelegateFunctionMap::iterator i = m_handlers.begin(); i != m_handlers.end();)
    {
      if((*i).second->IsMarkedForDeletion())
      {
        delete (*i).second;
        i = m_handlers.erase(i);
      }
      else
      {
        ++i;
      }
    }
  }
}