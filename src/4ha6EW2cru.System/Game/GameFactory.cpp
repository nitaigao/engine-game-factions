#include "GameFactory.h"

#include "../Platform/Win32PlatformManager.h"
#include "../Platform/ProgramOptions.h"
using namespace Platform;

#include "../Configuration/Configuration.h"
using namespace Configuration;

#include "../Events/EventManager.h"
using namespace Events;

#include "../Service/ServiceManager.h"
using namespace Services;

#include "../System/SystemManager.h"

#include "Game.h"

namespace Game
{
	GameFactory::~GameFactory( )
	{
		delete m_programOptions;
		delete m_configuration;
		delete m_platformManager;
		delete m_systemManager;
		delete m_eventManager;
		delete m_serviceManager;
	}

	GameFactory::GameFactory( )
	{
		m_programOptions = new ProgramOptions( );
		m_platformManager = new Win32PlatformManager( );

		m_configuration = new ClientConfiguration( );		
		m_eventManager = new EventManager( );
		m_serviceManager = new ServiceManager( );

		m_systemManager = new SystemManager( m_configuration );
	}

	IGame* GameFactory::CreateGame( ) const
	{
		return new GameRoot( m_programOptions, m_configuration, m_platformManager, m_systemManager, m_eventManager, m_serviceManager );
	}
}