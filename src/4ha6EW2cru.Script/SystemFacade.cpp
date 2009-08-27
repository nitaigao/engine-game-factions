#include "SystemFacade.h"

#include "Management/Management.h"

using namespace luabind;

#include "Logging/Logger.h"
using namespace Logging;

#include "Events/Event.h"
#include "Events/EventData.hpp"
#include "Events/ScriptEvent.hpp"
using namespace Events;

namespace Script
{
	luabind::scope SystemFacade::RegisterFunctions()
	{
		return (
			class_< SystemFacade >( "SystemFacade" )
				.def( "print", &SystemFacade::Print )
				.def( "quit", &SystemFacade::Quit )
				.def( "loadLevel", &SystemFacade::LoadLevel )
				.def( "endGame", &SystemFacade::EndGame )
		);
	}

	void SystemFacade::Print( const System::MessageType& message )
	{
		Info( message );
	}

	void SystemFacade::Quit( )
	{
		Management::Get( )->GetEventManager( )->QueueEvent( new Event( GAME_QUIT ) );
	}

	void SystemFacade::LoadLevel( const std::string& levelName )
	{
		IEventData* eventData = new LevelChangedEventData( levelName );
		Management::Get( )->GetEventManager( )->QueueEvent( new Event( GAME_LEVEL_CHANGED, eventData ) );
	}

	void SystemFacade::EndGame( )
	{
		Management::Get( )->GetEventManager( )->QueueEvent( new ScriptEvent( "GAME_ENDED" ) );
		Management::Get( )->GetEventManager( )->QueueEvent( new Event( GAME_ENDED ) );
	}
}