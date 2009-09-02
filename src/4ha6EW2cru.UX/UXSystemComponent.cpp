#include "UXSystemComponent.h"

#include "Events/Event.h"
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
	}

	void UXSystemComponent::Initialize( )
	{
		m_state->Execute( );
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
		EventType eventType = event->GetEventType( );

		if ( event->GetEventType( ) == ALL_EVENTS )
		{
			const IScriptEvent* scriptEvent = static_cast< const IScriptEvent* >( event );

			for ( IScriptFunctionHandler::FunctionList::iterator i = m_eventHandlers.begin( ); i != m_eventHandlers.end( ); ++i )
			{
				( *i )->HandleEvent( scriptEvent );
			}
		}
	}

	void UXSystemComponent::Update( float deltaMilliseconds )
	{
		for ( IScriptFunctionHandler::FunctionList::iterator i = m_updateHandlers.begin( ); i != m_updateHandlers.end( ); ++i )	
		{
			try
			{
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

	void UXSystemComponent::Destroy()
	{
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
	}
}