/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IEvent.hpp
*  @date   2009/04/25
*/
#pragma once
#ifndef IEVENT_H
#define IEVENT_H

#include "EventType.hpp"
#include "IEventData.hpp"
#include <queue>

#include "../Export.hpp"

namespace Events
{
	/*! 
	 *  Interface for all Events
	 */
	class GAMEAPI IEvent
	{

	public:

		typedef std::queue<const IEvent*> EventQueue;

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~IEvent() { };

		
		/*! Gets the type of the Event
		 *
		 *  @return (std::string)
		 */
		virtual std::string GetEventType() const = 0;

		
		/*! Returns Event Data attached to the event
		 *
		 *  @return (IEventData*)
		 */
		virtual IEventData* GetEventData() const = 0;

	};
};

#endif

