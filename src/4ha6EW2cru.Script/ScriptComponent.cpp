#include "ScriptComponent.h"

#include "Maths/MathMatrix.h"
using namespace Maths;

#include "Logging/Logger.h"
using namespace Logging;

#include "Exceptions/ScriptException.hpp"

#include "IO/IResource.hpp"
using namespace Resources;

#include "Events/Event.h"
using namespace Events;

#include <luabind/luabind.hpp>
using namespace luabind;

#include "Service/IService.hpp"
using namespace Services;

#include "ScriptFunctionHandler.h"
#include "LuaState.h"
#include "ScriptEvent.hpp"

#include "Events/EventManager.h"
#include "Events/EventListener.h"
#include "Events/EventData.hpp"
using namespace Events;

using namespace System;

namespace Script
{
	ScriptComponent::~ScriptComponent()
	{
		delete m_messageDispatcher;
		delete m_eventDispatcher;

		delete m_updateDispatcher;
		delete m_facadeManager;
		delete m_state;
	}

	void ScriptComponent::Initialize( )
	{
		m_state->LoadScript( m_attributes[ System::Parameters::ScriptPath ].As< std::string >( ) );

		m_facadeManager->Initialize( this );
	}

	void ScriptComponent::Destroy( )
	{
		m_facadeManager->Destroy( );
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

	void ScriptComponent::RegisterUpdateHandler( const luabind::object& function )
	{
		m_updateDispatcher->RegisterUpdateHandler( new ScriptFunctionHandler( function ) );
	}

	void ScriptComponent::UnRegisterUpdateHandler( const luabind::object& function )
	{
		m_updateDispatcher->UnRegisterUpdateHandler( new ScriptFunctionHandler( function ) );
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

		if ( message == System::Messages::RunScript || message == System::Messages::PostInitialize )
		{
			this->RunScript( );
		}

		m_messageDispatcher->Dispatch_Message( message, parameters );

		return result;
	}

	void ScriptComponent::Update( float deltaMilliseconds )
	{
		m_messageDispatcher->Update( deltaMilliseconds );
		m_updateDispatcher->Update( deltaMilliseconds );
	}

	void ScriptComponent::SetPosition( const Maths::MathVector3& position )
	{
		m_attributes[ System::Attributes::Position ] = position;
		this->PushMessage( System::Messages::SetPosition, m_attributes );
	}

	void ScriptComponent::SubscribeMessage( const System::MessageType& message, const luabind::object& delegateFunction )
	{
		m_messageDispatcher->AddMessageHandler( message, delegateFunction );
	}

	void ScriptComponent::UnSubscribeMessage( const System::MessageType& message, const luabind::object& delegateFunction )
	{
		m_messageDispatcher->RemoveHandler( message, delegateFunction );
	}

	void ScriptComponent::RegisterEventHandler( const std::string& eventType, const luabind::object& handlerFunction )
	{
		m_eventDispatcher->RegisterEventHandler( eventType, new ScriptFunctionHandler( handlerFunction ) );
	}
}