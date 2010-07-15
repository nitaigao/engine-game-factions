#include "precompiled.h"

#include "ScriptEventDispatcher.h"

#include "Events/EventListener.h"
#include "Events/EventType.hpp"

using namespace Events;

namespace Script
{
  ScriptEventDispatcher::~ScriptEventDispatcher()
  {
    for (Events::EventTypeMap::iterator i = m_eventTypes.begin(); i != m_eventTypes.end(); ++i)
    {
      m_eventManager->RemoveEventListener((*i).first, MakeEventListener(this, &ScriptEventDispatcher::EventHandler));
    }

    for (IScriptFunctionHandler::FunctionMap::iterator i = m_eventHandlers.begin(); i != m_eventHandlers.end();)  
    {
      delete (*i).second;
      i = m_eventHandlers.erase(i);
    }
  }

  void ScriptEventDispatcher::RegisterEventHandler(const std::string& eventType, Script::IScriptFunctionHandler* eventHandler)
  {
    if (m_eventTypes.find(eventType) == m_eventTypes.end())
    {
      m_eventTypes.insert(std::make_pair(eventType, m_eventTypes.size()));
    }

    m_eventHandlers.insert(std::make_pair((*m_eventTypes.find(eventType)).second, eventHandler));

    m_eventManager->AddEventListener(eventType, MakeEventListener(this, &ScriptEventDispatcher::EventHandler));
  }

  void ScriptEventDispatcher::UnregisterEventHandler(const std::string& eventType, Script::IScriptFunctionHandler* eventHandler)
  {
    EventTypeMap::iterator eventTypeId = m_eventTypes.find(eventType);

    IScriptFunctionHandler::FunctionMap::iterator eventHandlersUpper = m_eventHandlers.upper_bound((*eventTypeId).second);
    IScriptFunctionHandler::FunctionMap::iterator eventHandlersLower = m_eventHandlers.lower_bound((*eventTypeId).second);

    for (IScriptFunctionHandler::FunctionMap::iterator i = eventHandlersLower; i != eventHandlersUpper; ++i)
    {
      if ((*i).second->Compare(eventHandler))
      {
        (*i).second->MarkForDeletion();
      }
    }

    delete eventHandler;
  }

  void ScriptEventDispatcher::EventHandler(const Events::IEvent* event)
  {
    EventTypeMap::iterator eventTypeId = m_eventTypes.find(event->GetEventType());

    IScriptFunctionHandler::FunctionMap::iterator eventHandlersUpper = m_eventHandlers.upper_bound((*eventTypeId).second);
    IScriptFunctionHandler::FunctionMap::iterator eventHandlersLower = m_eventHandlers.lower_bound((*eventTypeId).second);

    for (IScriptFunctionHandler::FunctionMap::iterator i = eventHandlersLower; i != eventHandlersUpper;)
    {
      if ((*i).second->IsMarkedForDeletion())
      {
        delete (*i).second;
        i = m_eventHandlers.erase(i);
      }
      else
      {
        (*i).second->CallFunction(event->GetEventType(), event->GetEventData());
        ++i;
      }
    }
  }
}