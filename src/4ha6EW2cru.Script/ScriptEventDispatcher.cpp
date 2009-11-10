#include "ScriptEventDispatcher.h"

#include "Events/EventListener.h"

namespace Script
{
	ScriptEventDispatcher::~ScriptEventDispatcher()
	{
		for ( IScriptFunctionHandler::FunctionMap::iterator i = m_eventHandlers.begin( ); i != m_eventHandlers.end( ); )	
		{
			delete ( *i ).second;
			i = m_eventHandlers.erase( i );
		}
	}

	/*void ScriptComponent::RegisterEventHandler( const std::string& eventType, IScriptFunctionHandler* eventHandler )
	{
	if ( m_eventTypes.find( eventType ) == m_eventTypes.end( ) )
	{
	m_eventTypes.insert( std::make_pair( eventType, m_eventTypes.size( ) ) );
	}

	m_eventHandlers.insert( std::make_pair( ( *m_eventTypes.find( eventType ) ).second, eventHandler ) );

	m_eventManager->AddEventListener( eventType, MakeEventListener( this, &ScriptComponent::EventHandler ) );
	}*/

	void ScriptEventDispatcher::RegisterEventHandler( const std::string& eventType, Script::IScriptFunctionHandler* eventHandler )
	{
		if ( m_eventTypes.find( eventType ) == m_eventTypes.end( ) )
		{
			m_eventTypes.insert( std::make_pair( eventType, m_eventTypes.size( ) ) );
		}

		m_eventHandlers.insert( std::make_pair( ( *m_eventTypes.find( eventType ) ).second, eventHandler ) );

		m_eventManager->AddEventListener( eventType, MakeEventListener( this, &ScriptEventDispatcher::EventHandler ) );
	}

	void ScriptEventDispatcher::UnregisterEventHandler( const std::string& eventType, Script::IScriptFunctionHandler* eventHandler )
	{

	}

	void ScriptEventDispatcher::EventHandler( const Events::IEvent* event )
	{

	}
}