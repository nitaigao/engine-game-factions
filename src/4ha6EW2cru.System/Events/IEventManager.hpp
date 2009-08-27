/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IEventManager.hpp
*  @date   2009/08/26
*/
#pragma once
#ifndef IEVENTMANAGER_HPP
#define IEVENTMANAGER_HPP

#include "../Export.hpp"

#include "IEventListener.hpp"

namespace Events
{
	/*! 
	 *  Manages the distribution of Events throughout the Game
	 */
	class GAMEAPI IEventManager
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~IEventManager( ) { };


		/*! Queues an Event for processing on the next call to Update
		*
		*  @param[in] const IEvent * event
		*  @return (void)
		*/
		virtual void QueueEvent( const Events::IEvent* event ) = 0;


		/*! Processes an Event immediately
		*
		*  @param[in] const IEvent * event
		*  @return (void)
		*/
		virtual void TriggerEvent( const Events::IEvent* event ) = 0;


		/*! Dispatched all events in the Event Queue to their Listening Event Handlers
		*
		*  @param[in] float deltaMilliseconds
		*  @return (void)
		*/
		virtual void Update( float deltaMilliseconds ) = 0;


		/*! Adds an EventListener for Event processing
		*
		* @param[in] IEventListener * eventListener
		* @return ( void )
		*/
		virtual void AddEventListener( IEventListener* eventListener ) = 0;


		/*! Marks an Event Listener for removal on the next call to Update
		*
		* @param[in] IEventListener * eventListener
		* @return ( void )
		*/
		virtual void RemoveEventListener( IEventListener* eventListener ) = 0;
		
	};
};

#endif