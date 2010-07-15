#include "precompiled.h"
#include "EventManager.h"

#include "Event.h"

#include "../Logging/Logger.h"
using namespace Logging;

#include "../Exceptions/NullReferenceException.hpp"
#include "../Exceptions/UnInitializedException.hpp"
#include "../Exceptions/AlreadyInitializedException.hpp"
using namespace Exceptions;

namespace Events
{
	EventManager::~EventManager()
	{
		while(m_eventQueue.size()> 0)
		{
			delete m_eventQueue.front();
			m_eventQueue.pop();
		}

		for (IEventListener::EventListenerMultiMap::iterator i = m_eventListeners.begin(); i != m_eventListeners.end(); ++i)
		{
			delete (*i).second;
		}
	}

	void EventManager::QueueEvent(const IEvent* event)
	{
		if (0 == event)
		{
			//NullReferenceException e("EventManager::QueueEvent - Attempted to add a NULL Event to the Queue");
			//Fatal(e.what ());
			//throw e;
		}

		m_eventQueue.push(event);
	}

	void EventManager::QueueEvent(const std::string& eventType, IEventData* eventData)
	{
		IEvent* event = new Event(eventType, eventData);
		this->QueueEvent(event);
	}

	void EventManager::TriggerEvent(const IEvent* event)
	{
		if (0 == event)
		{
			//NullReferenceException e("EventManager::TriggerEvent - Attempted to trigger a NULL Event");
			//Fatal(e.what ());
			//throw e;
		}

		//Debug(event->GetEventType().c_str());
		unsigned int eventTypeId = this->GetEventTypeId(event->GetEventType());

		IEventListener::EventListenerMultiMap::iterator listenersUpper = m_eventListeners.upper_bound(eventTypeId);
		IEventListener::EventListenerMultiMap::iterator listenersLower = m_eventListeners.lower_bound(eventTypeId);

		for (IEventListener::EventListenerMultiMap::iterator i = listenersLower; i != listenersUpper;)
		{
			if (!(*i).second->IsMarkedForDeletion())
			{
				(*i).second->HandleEvent(event);
				++i;
			}
			else
			{
				delete (*i).second;
				//i = m_eventListeners.erase(i);
        m_eventListeners.erase(i++);
				
			}
		}

		delete event;
	}

	void EventManager::Update(float deltaMilliseconds)
	{
		while(m_eventQueue.size()> 0)
		{
			this->TriggerEvent(m_eventQueue.front());
			m_eventQueue.pop();
		}
	}

	void EventManager::RemoveEventListener(const std::string& eventType, IEventListener* eventListener)
	{
		unsigned int eventTypeId = (*m_eventTypes.find(eventType)).second;

		IEventListener::EventListenerMultiMap::iterator listenersUpper = m_eventListeners.upper_bound(eventTypeId);
		IEventListener::EventListenerMultiMap::iterator listenersLower = m_eventListeners.lower_bound(eventTypeId);

		for (IEventListener::EventListenerMultiMap::iterator i = listenersLower; i != listenersUpper; ++i)
		{
			if (eventListener->GetHandlerFunctionName() == (*i).second->GetHandlerFunctionName() &&
				eventListener->GetHandlerAddress() == (*i).second->GetHandlerAddress())
			{
				(*i).second->MarkForDeletion();
			}
		}

		delete eventListener;
	}

	void EventManager::AddEventListener(const std::string& eventType, IEventListener* eventListener)
	{
		m_eventListeners.insert(std::make_pair(this->GetEventTypeId(eventType), eventListener));
	}

	unsigned int EventManager::GetEventTypeId(const std::string& eventType)
	{
		EventTypeMap::iterator i = m_eventTypes.find(eventType);

		if (i != m_eventTypes.end())
		{
			return (*i).second;
		}

		unsigned int eventTypeId = m_eventTypes.size();

		m_eventTypes.insert(std::make_pair(eventType, eventTypeId));

		return eventTypeId;
	}
}