/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   Event.h
*  @date   2009/04/25
*/
#pragma once
#ifndef EVENT_H
#define EVENT_H

#include "IEvent.hpp"
#include "IEventData.hpp"
#include "EventType.hpp"

namespace Events
{
	/*! 
	 *  A Game Event
	 */
	class GAMEAPI Event : public IEvent
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~Event()
		{
			if (m_eventData != 0)
			{
				delete m_eventData;
				m_eventData = 0;
			}
		}


		/*! Default Constructor
		 *
		 *  @param[in] const EventType & eventType
		 *  @return ()
		 */
		Event(const std::string& eventType)
			: m_eventType(eventType)
			, m_eventData(0)
		{

		};


		/*! Constructor that accepts an object containing Event Data
		*
		*  @param[in] const EventType & eventType
		*  @param[in] IEventData * eventData
		*  @return ()
		*/
		Event(const std::string& eventType, IEventData* eventData)
			: m_eventType(eventType)
			, m_eventData(eventData)
		{

		};


		/*! Gets the type of the Event
		*
		*  @return (std::string)
		*/
		inline std::string GetEventType() const { return m_eventType; };

		
		/*! Returns Event Data attached to the Event
		 *
		 *  @return (IEventData*)
		 */
		inline IEventData* GetEventData() const { return m_eventData; };

	private:

		std::string m_eventType;
		IEventData* m_eventData;

		Event() { };
		Event(const Event & copy) { };
		Event & operator = (const Event & copy) { return *this; };

	};
};

#endif

