#include "UXSystemComponent.h"

#include "ScriptFunctionHandler.h"
using namespace Script;

using namespace luabind;

#include "Service/IService.hpp"
using namespace Services;

#include "Logging/Logger.h"
using namespace Logging;

namespace UX
{
	UXSystemComponent::~UXSystemComponent()
	{
		delete m_state;
		delete m_updateDispatcher;
		delete m_eventDispatcher;
		delete m_messageDispatcher;
		delete m_facadeManager;
	}

	void UXSystemComponent::Initialize( )
	{
		m_facadeManager->Initialize( this );
		m_state->Execute( );
	}

	void UXSystemComponent::Destroy()
	{
		m_updateDispatcher->Destroy( );
		m_facadeManager->Destroy( );
	}

	void UXSystemComponent::RegisterUpdate( const luabind::object& function )
	{
		m_updateDispatcher->RegisterUpdateHandler( new ScriptFunctionHandler( function ) );
	}

	void UXSystemComponent::UnRegisterUpdate( const luabind::object& function )
	{
		m_updateDispatcher->UnRegisterUpdateHandler( new ScriptFunctionHandler( function ) );
	}

	void UXSystemComponent::Update( float deltaMilliseconds )
	{
		m_updateDispatcher->Update( deltaMilliseconds );
		m_messageDispatcher->Update( deltaMilliseconds );
	}

	void UXSystemComponent::ExecuteString( const std::string& input )
	{
		m_state->ExecuteString( input );
	}

	void UXSystemComponent::RegisterEventHandler( const std::string& eventType, const luabind::object& handlerFunction )
	{
		m_eventDispatcher->RegisterEventHandler( eventType, new ScriptFunctionHandler( handlerFunction ) );
	}

	void UXSystemComponent::UnregisterEventHandler( const std::string& eventType, const luabind::object& handlerFunction )
	{
		m_eventDispatcher->UnregisterEventHandler( eventType, new ScriptFunctionHandler( handlerFunction ) );
	}
}