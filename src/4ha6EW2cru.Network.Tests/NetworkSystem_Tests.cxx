#include <gtest/gtest.h>
using namespace testing;

#include "NetworkSystem.h"
#include "ServerNetworkProvider.h"
using namespace Network;

#include "Configuration/Configuration.h"
using namespace Configuration;

#include "Mocks/MockNetworkSystemScene.hpp"
#include "Mocks/MockServiceManager.hpp"
#include "Mocks/MockNetworkClientProvider.hpp"

#include "Service/IService.hpp"
using namespace Services;

TEST( NetworkSystem_Tests, should_add_server_network_provider_to_scene )
{
	MockServiceManager serviceManager;
	EXPECT_CALL( serviceManager, RegisterService( An< IService* >( ) ) );

	MockNetworkSystemScene* scene = new MockNetworkSystemScene( );
	EXPECT_CALL( *scene, AddNetworkProvider( An< INetworkProvider* >( ) ) )
		.Times( AtLeast( 1 ) );

	ClientConfiguration config;

	NetworkSystem system( &serviceManager, scene, 0 );
	system.Initialize( &config );
	
	AnyType::AnyTypeMap parameters;
	parameters[ System::Parameters::Network::Port ] = static_cast< unsigned int >( 8989 );
	parameters[ System::Parameters::Network::Server::MaxPlayers ] = 10;

	system.Message( System::Messages::Network::CreateServer, parameters );

	delete scene;
}

TEST( NetworkSystem, should_add_client_network_provider_to_the_scene )
{
	MockServiceManager serviceManager;
	EXPECT_CALL( serviceManager, RegisterService( An< IService* >( ) ) );

	MockNetworkSystemScene* scene = new MockNetworkSystemScene( );
	EXPECT_CALL( *scene, AddNetworkProvider( An< INetworkProvider* >( ) ) );

	ClientConfiguration config;

	NetworkSystem system( &serviceManager, scene, 0 );
	system.SetAttribute( System::Attributes::Network::IsServer, false );
	system.Initialize( &config );

	delete scene;
}

TEST( NetworkSystem, should_connect_to_server )
{
	std::string serverAddress = "127.0.0.1";
	unsigned int port = 8989;

	MockNetworkClientProvider* clientProvider = new MockNetworkClientProvider( );
	EXPECT_CALL( *clientProvider, Connect( serverAddress, port ) );

	NetworkSystem system( 0, 0, clientProvider );

	AnyType::AnyTypeMap parameters;
	parameters[ System::Parameters::Network::HostAddress ] = serverAddress;
	parameters[ System::Parameters::Network::Port ] = port;

	system.Message( System::Messages::Network::Connect, parameters );
}

TEST( NetworkSystem, should_disconnect_from_server )
{
	MockNetworkClientProvider* clientProvider = new MockNetworkClientProvider( );
	EXPECT_CALL( *clientProvider, Disconnect( ) );

	NetworkSystem system( 0, 0, clientProvider );

	system.Message( System::Messages::Network::Disconnect, AnyType::AnyTypeMap( ) );
}

TEST( NetworkSystem_Tests, should_update_the_scene )
{
	float delta = 99;

	MockServiceManager serviceManager;

	MockNetworkSystemScene scene;
	EXPECT_CALL( scene, Update( delta ) );

	NetworkSystem system( &serviceManager , &scene, 0 );
	system.Update( delta );
}


TEST( NetworkSystem_Tests, should_call_select_character_when_client_picks_one )
{
	std::string characterName = "marine";

	MockNetworkClientProvider* clientProvider = new MockNetworkClientProvider( );
	EXPECT_CALL( *clientProvider, SelectCharacter( characterName ) );

	NetworkSystem system( 0, 0, clientProvider );

	AnyType::AnyTypeMap parameters;
	parameters[ System::Parameters::Network::Client::CharacterName ] = characterName;

	system.Message( System::Messages::Network::Client::CharacterSelected, parameters );
}

