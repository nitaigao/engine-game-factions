/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ScriptEventDispatcher.hpp
*  @date   2009/11/08
*/
#pragma once
#ifndef SCRIPTEVENTDISPATCHER_HPP
#define SCRIPTEVENTDISPATCHER_HPP

#include "IScriptEventDispatcher.hpp"
#include "Events/IEventManager.hpp"

#include "Export.hpp"

namespace Script
{
	/*! 
	 *  Dispatches Events to Script
	 */
	class GAMEAPI ScriptEventDispatcher : public IScriptEventDispatcher
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~ScriptEventDispatcher( );


		/*! Default Constructor
		*
		* @return (  )
		*/
		ScriptEventDispatcher( Events::IEventManager* eventManager )
			: m_eventManager( eventManager )
		{

		}


		/*! Registers a Script Function to receive Events
		*
		* @param[in] const std::string & eventType
		* @param[in] IScriptFunctionHandler * eventHandler
		* @return ( void )
		*/
		void RegisterEventHandler( const std::string& eventType, Script::IScriptFunctionHandler* eventHandler );


		/*! Unregisters a Script Function from receiving Events
		*
		* @param[in] const std::string & eventType
		* @param[in] IScriptFunctionHandler * eventHandler
		* @return ( void )
		*/
		void UnregisterEventHandler( const std::string& eventType, Script::IScriptFunctionHandler* eventHandler );


		/*! Handles incoming Events
		*
		* @param[in] const Events::IEvent * event
		* @return ( void )
		*/
		void EventHandler( const Events::IEvent* event );

	private:

		ScriptEventDispatcher( const ScriptEventDispatcher & copy ) { };
		ScriptEventDispatcher & operator = ( const ScriptEventDispatcher & copy ) { return *this; };

		Events::IEventManager* m_eventManager;
		Events::EventTypeMap m_eventTypes;
		Script::IScriptFunctionHandler::FunctionMap m_eventHandlers;
		
	};
};

#endif