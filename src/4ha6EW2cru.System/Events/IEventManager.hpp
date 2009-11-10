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

#include <map>

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


		/*! Registers a string event type for use
		 *
		 * @param[in] const std::string & eventType
		 * @return ( void )
		 */
		virtual void RegisterEventType( const std::string& eventType ) = 0;


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
		 * @param[in] const std::string & eventType
		 * @param[in] IEventListener * eventListener
		 * @return ( void )
		 */
		virtual void AddEventListener( const std::string& eventType, IEventListener* eventListener ) = 0;


		/*! Marks an Event Listener for removal on the next call to Update
		*
		* @param[in] const std::string & eventType
		* @param[in] IEventListener * eventListener
		* @return ( void )
		*/
		virtual void RemoveEventListener( const std::string& eventType, IEventListener* eventListener ) = 0;
		
	};
};

#endif