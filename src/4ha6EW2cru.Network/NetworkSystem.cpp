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

#include <luabind/luabind.hpp>
using namespace luabind;

using namespace Services;

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
				class_< ServerAdvertisement >( "ServerAdvertisement" )
					.def( constructor< const std::string&, const std::string&, int, int, int, const std::string&, int >( ) )
					.def( "getServerName", &ServerAdvertisement::GetServerName )
					.def( "getMaxPlayers", &ServerAdvertisement::GetMaxPlayers )
					.def( "getPlayerCount", &ServerAdvertisement::GetPlayerCount )
					.def( "getLevelName", &ServerAdvertisement::GetLevelName )
					.def( "getPing", &ServerAdvertisement::GetPing )
					.def( "getServerAddress", &ServerAdvertisement::GetServerAddress )
					.def( "getServerPort", &ServerAdvertisement::GetServerPort )
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
			m_eventManager->AddEventListener( MakeEventListener( GAME_LEVEL_CHANGED, static_cast< NetworkServerProvider* >( m_serverProvider ), &NetworkServerProvider::OnGameLevelChanged ) );
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

		if ( message == System::Messages::Network::Client::GetServerAd )
		{
			IServerAdvertisement* serverAd = m_clientProvider->GetServerAdvertisement( parameters[ System::Parameters::Network::Client::ServerCacheIndex ].As< int >( ) );
		
			if ( serverAd )
			{
				results[ System::Parameters::Network::Server::ServerName ] = serverAd->GetServerName( );
				results[ System::Parameters::Network::Server::LevelName ] = serverAd->GetLevelName( );
				results[ System::Parameters::Network::Server::MaxPlayers ] = StringUtils::ToString( serverAd->GetMaxPlayers( ) );
				results[ System::Parameters::Network::Server::PlayerCount ] = StringUtils::ToString( serverAd->GetPlayerCount( ) );
				results[ System::Parameters::Network::Server::Ping ] = StringUtils::ToString( serverAd->GetPing( ) );
				results[ System::Parameters::Network::HostAddress ] = serverAd->GetServerAddress( );
				results[ System::Parameters::Network::Port ] = StringUtils::ToString( serverAd->GetServerPort( ) );
			}
		}

		if ( message == System::Messages::Network::Client::LevelLoaded )
		{
			m_clientProvider->LevelLoaded( );
		}

		return results;
	}
}