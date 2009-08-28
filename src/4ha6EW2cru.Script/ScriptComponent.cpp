#include "ScriptComponent.h"

#include "Maths/MathMatrix.h"
using namespace Maths;

#include "Logging/Logger.h"
using namespace Logging;

#include "Exceptions/ScriptException.hpp"

#include "IO/IResource.hpp"
using namespace Resources;

#include "Management/Management.h"

#include "Events/Event.h"
#include "Events/ScriptEvent.hpp"
using namespace Events;

#include <luabind/luabind.hpp>
using namespace luabind;

#include "Service/IService.hpp"
using namespace Services;

#include "ScriptFunctionHandler.hpp"
#include "LuaState.h"

#include "Events/EventManager.h"
#include "Events/EventListener.h"
using namespace Events;

namespace Script
{
	void ScriptComponent::Initialize( )
	{
		m_eventManager->AddEventListener( MakeEventListener( ALL_EVENTS, this, &ScriptComponent::OnEvent ) );

		m_state->LoadScript( m_attributes[ System::Parameters::ScriptPath ].As< std::string >( ) );

		m_facadeManager->Initialize( this );
	}

	void ScriptComponent::Destroy( )
	{
		m_eventManager->RemoveEventListener( MakeEventListener( ALL_EVENTS, this, &ScriptComponent::OnEvent ) );

		m_facadeManager->Destroy( );

		for( IScriptFacade::ScriptFacadeList::iterator i = m_facades.begin( ); i != m_facades.end( ); )
		{
			delete ( *i );
			i = m_facades.erase( i );
		}

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

	void ScriptComponent::RunScript( )
	{
		m_state->Execute( );
	}

	void ScriptComponent::IncludeScript( const std::string& scriptPath )
	{
		m_state->LoadScript( scriptPath );
		m_state->ReParse( );
	}

	void ScriptComponent::ExecuteString( const std::string& input )
	{
		m_state->ExecuteString( input );
	}

	void ScriptComponent::RegisterEvent( const luabind::object& function )
	{
		m_eventHandlers.push_back( new ScriptFunctionHandler( function ) );
	}

	void ScriptComponent::UnRegisterEvent( const luabind::object& function )
	{
		for ( IScriptFunctionHandler::FunctionList::iterator i = m_eventHandlers.begin( ); i != m_eventHandlers.end( ); ++i )
		{
			if ( ( *i )->GetFunction( ) == function )
			{
				( *i )->MarkForDeletion( ); 
			}
		}
	}

	void ScriptComponent::RegisterUpdate( const luabind::object& function )
	{
		m_updateHandlers.push_back( new ScriptFunctionHandler( function ) );
	}

	void ScriptComponent::UnRegisterUpdate( const luabind::object& function )
	{
		for ( IScriptFunctionHandler::FunctionList::iterator i = m_updateHandlers.begin( ); i != m_updateHandlers.end( ); ++i )
		{
			if ( ( *i )->GetFunction( ) == function )
			{
				( *i )->MarkForDeletion( ); 
			}
		}
	}

	void ScriptComponent::OnEvent( const IEvent* event )
	{
		for ( IScriptFunctionHandler::FunctionList::iterator i = m_eventHandlers.begin( ); i != m_eventHandlers.end( ); ++i )
		{
			EventType eventType = event->GetEventType( );
			
			if ( event->GetEventType( ) == ALL_EVENTS )
			{
				ScriptEvent* scriptEvent = ( ScriptEvent* ) event;

				try
				{
					switch( scriptEvent->GetParamType( ) )
					{

					case ScriptEvent::PARAMCOMBO_NONE:

						call_function< void >( ( *i )->GetFunction( ), scriptEvent->GetEventName( ) );

						break;

					case ScriptEvent::PARAMCOMBO_INT:

						call_function< void >( ( *i )->GetFunction( ), scriptEvent->GetEventName( ), scriptEvent->GetValue1AsInt( ) );

						break;

					case ScriptEvent::PARAMCOMBO_STRING:

						call_function< void >( ( *i )->GetFunction( ), scriptEvent->GetEventName( ), scriptEvent->GetValue1AsString( ) );

						break;

					case ScriptEvent::PARAMCOMBO_STRING_STRING:

						call_function< void >( ( *i )->GetFunction( ), scriptEvent->GetEventName( ), scriptEvent->GetValue1AsString( ), scriptEvent->GetValue2AsString( ) );

						break;

					case ScriptEvent::PARAMCOMBO_STRING_INT:

						call_function< void >( ( *i )->GetFunction( ), scriptEvent->GetEventName( ), scriptEvent->GetValue1AsString( ), scriptEvent->GetValue2AsInt( ) );

						break;

					case ScriptEvent::PARAMCOMBO_INT_STRING:

						call_function< void >( ( *i )->GetFunction( ), scriptEvent->GetEventName( ), scriptEvent->GetValue1AsInt( ), scriptEvent->GetValue2AsString( ) );

						break;

					case ScriptEvent::PARAMCOMBO_INT_INT:

						call_function< void >( ( *i )->GetFunction( ), scriptEvent->GetEventName( ), scriptEvent->GetValue1AsInt( ), scriptEvent->GetValue2AsInt( ) );

						break;

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
	}

	void ScriptComponent::BroadcastEvent( const std::string& eventName, const std::string& var1 )
	{
		m_eventManager->QueueEvent( new ScriptEvent( eventName, var1 ) ); 
	}

	void ScriptComponent::BroadcastEvent( const std::string& eventName, int var1 )
	{
		m_eventManager->QueueEvent( new ScriptEvent( eventName, var1 ) ); 
	}

	void ScriptComponent::BroadcastEvent( const std::string& eventName, const std::string& var1, const std::string& var2 )
	{
		m_eventManager->QueueEvent( new ScriptEvent( eventName, var1, var2 ) ); 
	}

	void ScriptComponent::BroadcastEvent( const std::string& eventName, const std::string& var1, int var2 )
	{
		m_eventManager->QueueEvent( new ScriptEvent( eventName, var1, var2 ) ); 
	}

	void ScriptComponent::BroadcastEvent( const std::string& eventName, int var1, const std::string& var2 )
	{
		m_eventManager->QueueEvent( new ScriptEvent( eventName, var1, var2 ) ); 
	}

	void ScriptComponent::BroadcastEvent( const std::string& eventName, int var1, int var2 )
	{
		m_eventManager->QueueEvent( new ScriptEvent( eventName, var1, var2 ) ); 
	}

	void ScriptComponent::BroadcastEvent( const std::string& eventName )
	{
		m_eventManager->QueueEvent( new ScriptEvent( eventName ) ); 
	}

	AnyType ScriptComponent::Observe( const ISubject* subject, const System::MessageType& message, AnyType::AnyTypeMap parameters )
	{
		AnyType result;

		if ( message == System::Messages::SetPosition  )
		{
			m_attributes[ System::Attributes::Position ] = parameters[ System::Attributes::Position ].As< MathVector3 >( );
		}

		if ( message ==  System::Messages::SetOrientation )
		{
			m_attributes[ System::Attributes::Orientation ] = parameters[ System::Attributes::Orientation ].As< MathQuaternion >( );
		}

		if ( message == System::Messages::SetLookAt )
		{
			m_lookAt = parameters[ System::Attributes::LookAt ].As< MathVector3 >( );
		}

		if ( message == System::Messages::RunScript )
		{
			this->RunScript( );
		}

		if ( message == System::Messages::PostInitialize )
		{
			this->RunScript( );
		}

		if( message == System::Messages::GetState )
		{
			result = m_state;
		}

		m_eventManager->QueueEvent( new ScriptEvent( message, m_attributes[ System::Attributes::Name ].As< std::string >( ) ) );

		return result;
	}

	void ScriptComponent::Update( float deltaMilliseconds )
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

	ScriptComponent::~ScriptComponent()
	{
		delete m_facadeManager;
		delete m_state;
	}
}