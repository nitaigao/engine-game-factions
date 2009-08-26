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

#include "../Export.hpp"

namespace Events
{
	/*! 
	 *  Interface for all Events
	 */
	class GAMEAPI IEvent
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~IEvent( ) { };

		
		/*! Gets the type of the Event
		 *
		 *  @return (EventType)
		 */
		virtual EventType GetEventType( ) const = 0;

		
		/*! Returns Event Data attached to the event
		 *
		 *  @return (IEventData*)
		 */
		virtual IEventData* GetEventData( ) const = 0;

	};
};

#endif

