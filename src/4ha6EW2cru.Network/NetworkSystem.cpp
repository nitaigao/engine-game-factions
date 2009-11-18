#include "NetworkSystem.h"

#include "NetworkUtils.h"
#include "NetworkSystemScene.h"
#include "NetworkServerProvider.h"
#include "NetworkClientProvider.h"
#include "ServerAdvertisement.hpp"

#include <RakNetworkFactory.h>
#include <RakSleep.h>
#include <BitStream.h>
#include <MessageIdentifiers.h>
using namespace RakNet;

#include "Utility/StringUtils.h"
using namespace Utility;

#include "Logging/Logger.h"
using namespace Logging;

#include "Events/Event.h"
#include "Events/EventData.hpp"
#include "Events/EventListener.h"
using namespace Events;

#include "System/SystemType.hpp"
#include "System/Instrumentation.hpp"
using namespace Configuration;

using namespace Services;

#include <luabind/luabind.hpp>
using namespace luabind;

#include "Management/Management.h"

#include "Configuration/ConfigurationTypes.hpp"

namespace Network
{
	NetworkSystem::~NetworkSystem( )
	{
		delete m_clientProvider;
		delete m_serverProvider;
	}	

	void NetworkSystem::Release( )
	{

	}

	ISystemScene* NetworkSystem::CreateScene()
	{
		return m_scene;
	}

	void NetworkSystem::Initialize( Configuration::IConfiguration* configuration )
	{
		m_serviceManager->RegisterService( this );

		if ( !m_attributes[ System::Attributes::Network::IsServer ].As< bool >( ) )
		{
			m_clientProvider->Initialize( 0, 1 );
			m_scene->AddNetworkProvider( m_clientProvider );
		}

		configuration->SetDefault( Configuration::ConfigSections::Network, Configuration::ConfigItems::Network::ServerPort, 8989 );
		configuration->SetDefault( Configuration::ConfigSections::Network, Configuration::ConfigItems::Network::ServerBotCount, 0 );
		configuration->SetDefault( Configuration::ConfigSections::Network, Configuration::ConfigItems::Network::ServerName, "Factions Server" );
		configuration->SetDefault( Configuration::ConfigSections::Network, Configuration::ConfigItems::Network::ServerTimeLimit, 60 );
		configuration->SetDefault( Configuration::ConfigSections::Network, Configuration::ConfigItems::Network::ServerFragLimit, 50 ); 
		configuration->SetDefault( Configuration::ConfigSections::Network, Configuration::ConfigItems::Network::ServerMaxPlayers, 10 ); 
	}

	void NetworkSystem::Update( float deltaMilliseconds )
	{
		m_scene->Update( deltaMilliseconds );
	}

	AnyType::AnyTypeMap NetworkSystem::ProcessMessage( const System::MessageType& message, AnyType::AnyTypeMap parameters )
	{
		AnyType::AnyTypeMap results;

		if ( message == System::Messages::RegisterScriptFunctions )
		{
			scope luaScope = 
				(
				class_< ServerEventData >( "ServerEventData" )
					.def( constructor< const std::string&, const std::string&, int, int, int, const std::string&, int >( ) )
					.def( "getServerName", &ServerEventData::GetServerName )
					.def( "getMaxPlayers", &ServerEventData::GetMaxPlayers )
					.def( "getMapName", &ServerEventData::GetMapName )
					.def( "getNumPlayers", &ServerEventData::GetNumPlayers )
					.def( "getPing", &ServerEventData::GetPing )
					.def( "getAddress", &ServerEventData::GetAddress )
					.def( "getPort", &ServerEventData::GetPort )
				);

			results[ System::TypeStrings::NETWORK ] = luaScope;
		}

		if ( message == System::Messages::Network::CreateServer )
		{
			m_instrumentation->SetLevelName( parameters[ System::Parameters::Game::LevelName ].As< std::string >( ) );

			m_clientProvider->SetPassive( true );

			m_serverProvider->Initialize(
				parameters[ System::Parameters::Network::Port ].As< unsigned int >( ),
				parameters[ System::Parameters::Network::Server::MaxPlayers ].As< int >( )
				);

			m_scene->AddNetworkProvider( m_serverProvider );
			m_eventManager->AddEventListener( EventTypes::GAME_LEVEL_CHANGED, MakeEventListener( static_cast< NetworkServerProvider* >( m_serverProvider ), &NetworkServerProvider::OnGameLevelChanged ) );
		}

		if ( message == System::Messages::Network::Connect )
		{
			m_clientProvider->Connect( 
				parameters[ System::Parameters::Network::HostAddress ].As< std::string >( ).c_str( ),
				parameters[ System::Parameters::Network::Port ].As< unsigned int >( )
				);
		}

		if ( message == System::Messages::Network::Disconnect )
		{
			m_clientProvider->Disconnect( );
		}

		if ( message == System::Messages::Network::Client::CharacterSelected )
		{
			m_clientProvider->SelectCharacter( parameters[ System::Parameters::Network::Client::CharacterName ].As< std::string >( ) );
		}

		if( message == System::Messages::Network::Client::FindServers )
		{
			m_clientProvider->FindServers( );
		}

		if ( message == System::Messages::Network::Client::LevelLoaded )
		{
			m_clientProvider->LevelLoaded( );
		}

		return results;
	}
}