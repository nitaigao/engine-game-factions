#include "precompiled.h"
#include "Game.h"

#include "../System/Memory.cxx"

#include "../Exceptions/AlreadyInitializedException.hpp"
#include "../Exceptions/UnInitializedException.hpp"

#include "../Logging/Logger.h"
using namespace Logging;

#include "../Configuration/Configuration.h"
#include "../Configuration/ConfigurationTypes.hpp"
using namespace Configuration;

#include "../State/World.h"
using namespace State;

#include "../Service/IService.hpp"
using namespace Services;

#include "../Events/Event.h"
#include "../Events/EventData.hpp"
#include "../Events/EventListener.h"
using namespace Events;

namespace Game
{
	void GameRoot::Initialize()
	{
		Logger::Initialize(m_platformManager, m_eventManager);
		Logger::Get()->SetLogLevel(Logging::LEVEL_WARN);
		//Info("Game Startup"); 

		m_programOptions->Initialize();
		m_fileSystem->Initialize();

		m_configuration->Initialize("game.cfg");
		m_configuration->SetDefault(ConfigSections::Developer, ConfigItems::Developer::Console, false);
		m_configuration->SetDefault(ConfigSections::Logging, ConfigItems::Logging::LogLevel, static_cast<int>(LEVEL_WARN));

		LogLevel logLevel = static_cast<LogLevel>(m_configuration->Find(ConfigSections::Logging, ConfigItems::Logging::LogLevel).As<int>());
		Logger::Get()->SetLogLevel(logLevel);

		bool isDedicated = m_programOptions->HasOption(System::Options::DedicatedServer);
		m_systemManager->LoadSystems(isDedicated);
		m_systemManager->InitializeAllSystems();

		m_serviceManager->MessageAll(System::Messages::PostInitialize, AnyType::AnyTypeMap());

		m_world = m_systemManager->CreateWorld();

		m_eventManager->AddEventListener(EventTypes::GAME_QUIT, MakeEventListener(this, &GameRoot::OnGameQuit));
		m_eventManager->AddEventListener(EventTypes::GAME_LEVEL_CHANGED, MakeEventListener(this, &GameRoot::OnGameLevelChanged)); 
		m_eventManager->AddEventListener(EventTypes::GAME_ENDED, MakeEventListener(this, &GameRoot::OnGameEnded));


		if (isDedicated)
		{
			if (m_programOptions->HasOption(System::Options::LevelName))
			{
				AnyType::AnyTypeMap parameters;
				
				std::string levelName = m_programOptions->GetOption(System::Options::LevelName);
				parameters[ System::Parameters::Game::LevelName ] = levelName;
				
				int maxPlayers = m_configuration->Find(Configuration::ConfigSections::Network, Configuration::ConfigItems::Network::ServerMaxPlayers).As<int>();
				parameters[ System::Parameters::Network::Server::MaxPlayers ] = maxPlayers;

				IService* networkService = m_serviceManager->FindService(System::Types::NETWORK);
				networkService->ProcessMessage(System::Messages::Network::CreateServer, parameters);
			}
		}
		
		if (m_programOptions->HasOption(System::Options::LevelName))
		{
			std::string levelName = m_programOptions->GetOption(System::Options::LevelName);
			LevelChangedEventData* eventData = new LevelChangedEventData(levelName);
			m_eventManager->QueueEvent(EventTypes::GAME_LEVEL_CHANGED, eventData);
		}

		m_isInitialized = true;
	}

	void GameRoot::Update()
	{
		float deltaMilliseconds = m_platformManager->GetClock()->GetDeltaMilliseconds();

		m_systemManager->Update(deltaMilliseconds);
		m_eventManager->Update(deltaMilliseconds);
		m_platformManager->Update(deltaMilliseconds);

		m_world->Update(deltaMilliseconds);
	}

	void GameRoot::Release()
	{
		m_eventManager->RemoveEventListener(EventTypes::GAME_QUIT, MakeEventListener(this, &GameRoot::OnGameQuit));
		m_eventManager->RemoveEventListener(EventTypes::GAME_LEVEL_CHANGED, MakeEventListener(this, &GameRoot::OnGameLevelChanged));
		m_eventManager->RemoveEventListener(EventTypes::GAME_ENDED, MakeEventListener(this, &GameRoot::OnGameEnded));

		m_world->Destroy();

		delete m_world;

		m_systemManager->Release();

		Logger::Release();
	}

	void GameRoot::OnGameQuit(const IEvent* event)
	{
		m_isQuitting = true;
	}

	void GameRoot::OnGameLevelChanged(const IEvent* event)
	{
		this->OnGameEnded(event);

		LevelChangedEventData* eventData = static_cast<LevelChangedEventData*>(event->GetEventData());

		std::stringstream levelPath;
		levelPath <<"/data/levels/" <<eventData->GetLevelName() <<".xml";

		m_world->LoadLevel(levelPath.str());

		//Management::Get()->GetInstrumentation()->SetLevelName(eventData->GetLevelName());
	}

	void GameRoot::OnGameEnded(const IEvent* event)
	{
		m_world->Clear();
	}
}

// EOF