#include "NetworkSystem.h"

#include "NetworkSystemScene.h"
#include "NetworkServerProvider.h"
#include "NetworkClientProvider.h"

#include <RakNetworkFactory.h>
#include <RakSleep.h>
#include <BitStream.h>
#include <MessageIdentifiers.h>

using namespace RakNet;

#include "Logging/Logger.h"
using namespace Logging;

#include "Events/Event.h"
#include "Events/EventData.hpp"
using namespace Events;

#include "System/SystemType.hpp"
using namespace Configuration;

#include "Management/Management.h"

#include "NetworkUtils.h"

#include "Configuration/ConfigurationTypes.hpp"

#include "ServerNetworkProvider.h"
#include "ClientNetworkProvider.h"

#include "ServerAdvertisement.hpp"

#include <luabind/luabind.hpp>
using namespace luabind;

using namespace Services;

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

	void NetworkSystem::PushMessage( const System::Message& message, AnyType::AnyTypeMap parameters )
	{
		//m_networkProvider->PushMessage( message, parameters );
	}

	void NetworkSystem::PushMessage( const SystemAddress& address, const System::Message& message, AnyType::AnyTypeMap parameters )
	{
		//m_networkProvider->PushMessage( address, message, parameters );
	}

	void NetworkSystem::Update( float deltaMilliseconds )
	{
		m_scene->Update( deltaMilliseconds );
	}

	AnyType::AnyTypeMap NetworkSystem::Message( const System::Message& message, AnyType::AnyTypeMap parameters )
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

			m_serverProvider->Initialize(
				parameters[ System::Parameters::Network::Port ].As< unsigned int >( ),
				parameters[ System::Parameters::Network::Server::MaxPlayers ].As< int >( )
				);

			m_scene->AddNetworkProvider( m_serverProvider );
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

		return results;
	}

	void NetworkSystem::MessageComponent( const std::string& componentName, const std::string& message, AnyType::AnyTypeMap parameters )
	{
		m_scene->MessageComponent( componentName, message, parameters );
	}
}