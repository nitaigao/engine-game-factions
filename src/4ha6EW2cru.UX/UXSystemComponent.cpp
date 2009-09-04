#include "UXSystemComponent.h"

#include "Events/Event.h"
#include "Events/EventListener.h"
#include "Events/EventData.hpp"
using namespace Events;

#include "ScriptFunctionHandler.hpp"
using namespace Script;

#include <luabind/luabind.hpp>
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

		m_eventManager->AddEventListener( MakeEventListener( EventTypes::ALL_EVENTS, this, &UXSystemComponent::OnEvent ) );

		m_facadeManager->Initialize( this );
	}

	void UXSystemComponent::Destroy()
	{
		m_eventManager->RemoveEventListener( MakeEventListener( EventTypes::ALL_EVENTS, this, &UXSystemComponent::OnEvent ) );

		for ( IScriptFunctionHandler::FunctionList::iterator i = m_updateHandlers.begin( ); i != m_updateHandlers.end( ); )	
		{
			delete ( *i );
			i = m_updateHandlers.erase( i );
		}

		for ( IScriptFunctionHandler::FunctionList::iterator i = m_eventHandlers.begin( ); i != m_eventHandlers.end( ); )
		{
			delete ( *i );
			i = m_eventHandlers.erase( i );
		}

		m_facadeManager->Destroy( );
	}

	void UXSystemComponent::RegisterUpdate( const luabind::object& function )
	{
		m_updateHandlers.push_back( new ScriptFunctionHandler( function ) );
	}

	void UXSystemComponent::UnRegisterUpdate( const luabind::object& function )
	{
		for ( IScriptFunctionHandler::FunctionList::iterator i = m_updateHandlers.begin( ); i != m_updateHandlers.end( ); ++i )
		{
			if ( ( *i )->GetFunction( ) == function )
			{
				( *i )->MarkForDeletion( ); 
			}
		}
	}

	void UXSystemComponent::RegisterEvent( const luabind::object& function )
	{
		m_eventHandlers.push_back( new ScriptFunctionHandler( function ) );
	}

	void UXSystemComponent::UnRegisterEvent( const luabind::object& function )
	{
		for ( IScriptFunctionHandler::FunctionList::iterator i = m_eventHandlers.begin( ); i != m_eventHandlers.end( ); ++i )
		{
			if ( ( *i )->GetFunction( ) == function )
			{
				( *i )->MarkForDeletion( ); 
			}
		}
	}

	void UXSystemComponent::OnEvent( const IEvent* event )
	{
		for ( IScriptFunctionHandler::FunctionList::iterator i = m_eventHandlers.begin( ); i != m_eventHandlers.end( ); ++i )
		{
			try
			{
				if ( !( *i )->GetFunction( ).is_valid( ) )
				{
					int a = 1;
				}

				if ( event->GetEventType( ) == EventTypes::UI_EVENT )
				{
					UIEventData* eventData = static_cast< UIEventData* >( event->GetEventData( ) );
					luabind::call_function< void >( ( *i )->GetFunction( ), eventData->GetEventName( ), eventData->GetParameter1( ), eventData->GetParameter2( ) );
					
				}
				else
				{
					luabind::call_function< void >( ( *i )->GetFunction( ), event->GetEventType( ) );
				}
			}
			catch( error& e )
			{
				object error_msg( from_stack( e.state( ) , -1) );
				std::stringstream logMessage;
				logMessage << error_msg;
				Warn( logMessage.str( ) );
			}
		
		}
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
				if ( !( *i )->GetFunction( ).is_valid( ) )
				{
					int a = 1;
				}

				call_function< void >( ( *i )->GetFunction( ), deltaMilliseconds );
			}
			catch( error& e )
			{
				object error_msg( from_stack( e.state( ) , -1) );
				std::stringstream logMessage;
				logMessage << error_msg;
				Warn( logMessage.str( ) );
			}
		}

		for ( IScriptFunctionHandler::FunctionList::iterator i = m_eventHandlers.begin( ); i != m_eventHandlers.end( ); )
		{
			if ( ( *i )->IsMarkedForDeletion( ) )
			{
				delete ( *i );
				i = m_eventHandlers.erase( i );
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
		Event* event = new Event( Events::EventTypes::UI_EVENT, eventData );
		m_eventManager->QueueEvent( event );
	}

	void UXSystemComponent::ExecuteString( const std::string& input )
	{
		m_state->ExecuteString( input );
	}
}