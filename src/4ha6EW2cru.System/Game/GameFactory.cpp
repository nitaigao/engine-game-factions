#include "precompiled.h"
#include "GameFactory.h"

#ifdef WIN32

#include "../Platform/Win32PlatformManager.h"
#include "../Platform/Win32Clock.h"
#include "../IO/Win32PathInformation.h"

#endif

#include "../Platform/OSXPlatformManager.h"
#include "../Platform/OSXClock.h"
#include "../IO/OSXPathInformation.h"

#include "../Platform/ProgramOptions.h"
using namespace Platform;

#include "../Configuration/Configuration.h"
#include "../Configuration/ConfigurationFile.h"
using namespace Configuration;

#include "../Events/EventManager.h"
using namespace Events;

#include "../Service/ServiceManager.h"
using namespace Services;

#include "../io/ResourceCache.h"
using namespace Resources;

#include "../IO/FileSystem.h"
using namespace IO;

#include "../System/Instrumentation.hpp"
using namespace System;

#include "../System/SystemManager.h"

#include "Game.h"

namespace Game
{
	GameFactory::~GameFactory()
	{
		delete m_programOptions;
		delete m_configuration;
		delete m_platformManager;
		delete m_systemManager;
		delete m_eventManager;
		delete m_serviceManager;
		delete m_resourceCache;
		delete m_fileSystem;
		delete m_instrumentation;
		delete m_clock;
	}

	GameFactory::GameFactory()
	{
		m_programOptions = new ProgramOptions();
		m_eventManager = new EventManager();
		m_serviceManager = new ServiceManager();
		m_instrumentation = new Instrumentation();
		
		#ifdef WIN32

		m_clock = new Win32Clock();
		m_pathInformation = new Win32PathInformation();
		m_platformManager = new Win32PlatformManager(m_eventManager, m_pathInformation, m_clock);

    #endif
    
    m_clock = new OSXClock();
    m_pathInformation = new OSXPathInformation();
    m_platformManager = new OSXPlatformManager(m_eventManager, m_pathInformation, m_clock);

		m_fileSystem = new FileSystem(m_platformManager);
		m_resourceCache = new ResourceCache(m_fileSystem);

		IConfigurationFile* configFile = new ConfigurationFile(m_platformManager, m_fileSystem);
		m_configuration = new ClientConfiguration(configFile);

		m_systemManager = new SystemManager(m_configuration, m_serviceManager, m_resourceCache, m_eventManager, m_instrumentation, m_platformManager);
	}

	IGame* GameFactory::CreateGame() const
	{
		return new GameRoot(m_programOptions, m_configuration, m_platformManager, m_systemManager, m_eventManager, m_serviceManager, m_fileSystem);
	}
}