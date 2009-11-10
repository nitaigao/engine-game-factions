#include "UXSystemComponent.h"

#include "Events/Event.h"
#include "Events/EventListener.h"
#include "Events/EventData.hpp"
using namespace Events;

#include "ScriptFunctionHandler.h"
using namespace Script;

using namespace luabind;

#include "Service/IService.hpp"
using namespace Services;

#include "Management/Management.h"

#include "Logging/Logger.h"
using namespace Logging;

namespace UX
{
	UXSystemComponent::~UXSystemComponent()
	{
		delete m_state;
		delete m_facadeManager;
	}

	void UXSystemComponent::Initialize( )
	{
		m_state->Execute( );

		//m_eventManager->RegisterEventType( EventTypes::UI_EVENT );
		//m_eventManager->AddEventListener( EventTypes::ALL_EVENTS, MakeEventListener( this, &UXSystemComponent::OnEvent ) );

		m_facadeManager->Initialize( this );
	}

	void UXSystemComponent::Destroy()
	{
		//m_eventManager->RemoveEventListener( EventTypes::ALL_EVENTS, MakeEventListener( this, &UXSystemComponent::OnEvent ) );

		for ( IScriptFunctionHandler::FunctionList::iterator i = m_updateHandlers.begin( ); i != m_updateHandlers.end( ); )	
		{
			delete ( *i );
			i = m_updateHandlers.erase( i );
		}

		for ( IScriptFunctionHandler::FunctionList::iterator i = m_messageHandlers.begin( ); i != m_messageHandlers.end( ); )
		{
			delete ( *i );
			i = m_messageHandlers.erase( i );
		}

		for ( IScriptFunctionHandler::FunctionMap::iterator i = m_eventHandlers.begin( ); i != m_eventHandlers.end( ); )	
		{
			delete ( *i ).second;
			i = m_eventHandlers.erase( i );
		}

		m_facadeManager->Destroy( );
	}

	void UXSystemComponent::RegisterUpdate( const luabind::object& function )
	{
		//m_updateHandlers.push_back( new ScriptFunctionHandler( function ) );
	}

	void UXSystemComponent::UnRegisterUpdate( const luabind::object& function )
	{
		/*for ( IScriptFunctionHandler::FunctionList::iterator i = m_updateHandlers.begin( ); i != m_updateHandlers.end( ); ++i )
		{
			if ( ( *i )->GetFunction( ) == function )
			{
				( *i )->MarkForDeletion( ); 
			}
		}*/
	}

	void UXSystemComponent::Update( float deltaMilliseconds )
	{
		for ( IScriptFunctionHandler::FunctionList::iterator i = m_updateHandlers.begin( ); i != m_updateHandlers.end( ); )	
		{
			if ( ( *i )->IsMarkedForDeletion( ) )
			{
				delete ( *i );
				i = m_updateHandlers.erase( i );
			}
			else
			{
				++i;
			}
		}

		for ( IScriptFunctionHandler::FunctionList::iterator i = m_updateHandlers.begin( ); i != m_updateHandlers.end( ); ++i )	
		{
			try
			{
				//call_function< void >( ( *i )->GetFunction( ), deltaMilliseconds );
			}
			catch( error& e )
			{
				object error_msg( from_stack( e.state( ) , -1) );
				std::stringstream logMessage;
				logMessage << error_msg;
				Warn( logMessage.str( ) );
			}
		}

		for ( IScriptFunctionHandler::FunctionList::iterator i = m_messageHandlers.begin( ); i != m_messageHandlers.end( ); )
		{
			if ( ( *i )->IsMarkedForDeletion( ) )
			{
				delete ( *i );
				i = m_messageHandlers.erase( i );
			}
			else
			{
				++i;
			}
		}
	}

	void UXSystemComponent::SendEvent( const std::string& eventName, const std::string& parameter1, const std::string& parameter2 )
	{
		UIEventData* eventData = new UIEventData( eventName, parameter1, parameter2 );
		Event* event = new Event( eventName, eventData );
		m_eventManager->QueueEvent( event );
	}

	void UXSystemComponent::ExecuteString( const std::string& input )
	{
		m_state->ExecuteString( input );
	}


	void UXSystemComponent::RegisterEventHandler( const std::string& eventType, const luabind::object& handlerFunction )
	{
		this->RegisterEventHandler( eventType, new ScriptFunctionHandler( handlerFunction ) );
	}

	void UXSystemComponent::RegisterEventHandler( const std::string& eventType, IScriptFunctionHandler* eventHandler )
	{
		if ( m_eventTypes.find( eventType ) == m_eventTypes.end( ) )
		{
			m_eventTypes.insert( std::make_pair( eventType, m_eventTypes.size( ) ) );
		}

		m_eventHandlers.insert( std::make_pair( ( *m_eventTypes.find( eventType ) ).second, eventHandler ) );

		m_eventManager->AddEventListener( eventType, MakeEventListener( this, &UXSystemComponent::EventHandler ) );
	}

	void UXSystemComponent::UnregisterEventHandler( const std::string& eventType, const luabind::object& handlerFunction )
	{
		this->UnregisterEventHandler( eventType, new ScriptFunctionHandler( handlerFunction ) );
	}

	void UXSystemComponent::UnregisterEventHandler( const std::string& eventType, Script::IScriptFunctionHandler* eventHandler )
	{
		EventTypeMap::iterator eventTypeId = m_eventTypes.find( eventType );

		if ( eventTypeId != m_eventTypes.end( ) )
		{
			IScriptFunctionHandler::FunctionMap::iterator eventHandlersUpper = m_eventHandlers.upper_bound( ( *eventTypeId ).second );
			IScriptFunctionHandler::FunctionMap::iterator eventHandlersLower = m_eventHandlers.lower_bound( ( *eventTypeId ).second );

			for ( IScriptFunctionHandler::FunctionMap::iterator i = eventHandlersLower; i != eventHandlersUpper; )
			{
				if ( ( *i ).second->Compare( eventHandler ) )
				{
					delete (*i).second;
					i = m_eventHandlers.erase( i );

					m_eventManager->RemoveEventListener( eventType, MakeEventListener( this, &UXSystemComponent::EventHandler ) );
				}
				else
				{
					++i;
				}
			}
		}

		delete eventHandler;
	}

	void UXSystemComponent::EventHandler( const IEvent* event )
	{
		EventTypeMap::iterator eventTypeId = m_eventTypes.find( event->GetEventType( ) );

		IScriptFunctionHandler::FunctionMap::iterator eventHandlersUpper = m_eventHandlers.upper_bound( ( *eventTypeId ).second );
		IScriptFunctionHandler::FunctionMap::iterator eventHandlersLower = m_eventHandlers.lower_bound( ( *eventTypeId ).second );

		for ( IScriptFunctionHandler::FunctionMap::iterator i = eventHandlersLower; i != eventHandlersUpper; ++i )
		{
			( *i ).second->CallFunction(event->GetEventType( ), event->GetEventData( ) );
		}
	}

}