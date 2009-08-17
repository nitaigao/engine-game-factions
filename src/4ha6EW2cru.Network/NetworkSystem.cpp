#include "NetworkSystem.h"

#include "NetworkSystemScene.h"
#include "NetworkServerProvider.h"

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

namespace Network
{
	NetworkSystem::NetworkSystem()
		: m_configuration( 0 )
	{
		m_attributes[ System::Attributes::Network::IsServer ] = false;
		m_scene = new NetworkSystemScene( );
	}

	GAMEAPI NetworkSystem::NetworkSystem( INetworkSystemScene* scene )
		: m_scene( scene )
	{

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
		m_configuration = configuration;

		/*if ( m_attributes[ System::Attributes::Network::IsServer ].As< bool >( ) )
		{
			m_networkProvider = new ServerNetworkProvider( this );
		}
		else
		{
			m_networkProvider = new ClientNetworkProvider( this );
		}

		m_networkProvider->Initialize( configuration );*/

		Management::Get( )->GetServiceManager( )->RegisterService( this ); 
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
			NetworkServerProvider* serverProvider = new NetworkServerProvider( );

			serverProvider->Initialize(
				parameters[ System::Parameters::Network::Port ].As< unsigned int >( ),
				parameters[ System::Parameters::Network::Server::MaxPlayers ].As< int >( )
				);

			m_scene->AddNetworkProvider( serverProvider );
		}

		return results;
	}

	void NetworkSystem::MessageComponent( const std::string& componentName, const std::string& message, AnyType::AnyTypeMap parameters )
	{
		m_scene->MessageComponent( componentName, message, parameters );
	}
}