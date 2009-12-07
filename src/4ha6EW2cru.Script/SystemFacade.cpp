#include "precompiled.h"

#include "SystemFacade.h"

#include "ScriptEvent.hpp"

using namespace luabind;

#include "Logging/Logger.h"
using namespace Logging;

#include "Events/Event.h"
#include "Events/EventData.hpp"
using namespace Events;

namespace Script
{
	luabind::scope SystemFacade::RegisterFunctions()
	{
		return (
			def( "print", &SystemFacade::Print ),

			class_< SystemFacade >( "SystemFacade" )
				.def( "quit", &SystemFacade::Quit )
				.def( "loadLevel", &SystemFacade::LoadLevel )
				.def( "endGame", &SystemFacade::EndGame )
				.def( "getTime", &SystemFacade::GetTime )
		);
	}

	void SystemFacade::Print( const System::MessageType& message )
	{
		Info( message );
	}

	void SystemFacade::Quit( )
	{
		m_eventManager->QueueEvent( new Event( EventTypes::GAME_QUIT ) );
	}

	void SystemFacade::LoadLevel( const std::string& levelName )
	{
		IEventData* eventData = new LevelChangedEventData( levelName );
		m_eventManager->QueueEvent( new Event( EventTypes::GAME_LEVEL_CHANGED, eventData ) );
	}

	void SystemFacade::EndGame( )
	{
		m_eventManager->QueueEvent( new ScriptEventT0<>( "GAME_ENDED" ) );
		m_eventManager->QueueEvent( new Event( EventTypes::GAME_ENDED ) );
	}

	float SystemFacade::GetTime( ) const
	{
		return m_platformManager->GetClock( )->GetTime( );
	}
}