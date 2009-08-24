#include <gtest/gtest.h>
using namespace testing;

#include "Events/EventManager.h"
using namespace Events;

#include "NetworkSystem.h"
#include "ServerAdvertisement.hpp"
using namespace Network;

#include "Configuration/Configuration.h"
using namespace Configuration;

#include "Mocks/MockNetworkSystemScene.hpp"
#include "Mocks/MockServiceManager.hpp"
#include "Mocks/MockNetworkClientProvider.hpp"
#include "Mocks/MockNetworkServerProvider.hpp"
#include "Mocks/MockInstrumentation.hpp"

#include "Service/IService.hpp"
using namespace Services;

class NetworkSystem_Tests : public TestHarness< NetworkSystem >
{

protected:

	MockServiceManager* m_serviceManager;
	MockNetworkSystemScene* m_scene;
	MockNetworkClientProvider* m_clientProvider;
	MockNetworkServerProvider * m_serverProvider;
	MockInstrumentation* m_instrumentation;
	EventManager* m_eventManager;

	void EstablishContext( )
	{
		m_serviceManager = new MockServiceManager( );
		m_scene = new MockNetworkSystemScene( );
		m_clientProvider = new MockNetworkClientProvider( );
		m_serverProvider = new MockNetworkServerProvider( );
		m_instrumentation = new MockInstrumentation( );
		m_eventManager = new EventManager( );
	}


	void DestroyContext( )
	{
		delete m_scene;
		delete m_serviceManager;
		delete m_instrumentation;
		delete m_eventManager;
	}

	NetworkSystem* CreateSubject( )
	{
		return new NetworkSystem( m_serviceManager, m_instrumentation, m_scene, m_clientProvider, m_serverProvider, m_eventManager ); 
	}
};

TEST_F( NetworkSystem_Tests, should_add_server_network_provider_to_scene )
{
	EXPECT_CALL( *m_serviceManager, RegisterService( An< IService* >( ) ) );
	EXPECT_CALL( *m_scene, AddNetworkProvider( An< INetworkProvider* >( ) ) )
		.Times( AtLeast( 1 ) );

	ClientConfiguration config;
	m_subject->Initialize( &config );
	
	AnyType::AnyTypeMap parameters;
	parameters[ System::Parameters::Network::Port ] = static_cast< unsigned int >( 8989 );
	parameters[ System::Parameters::Network::Server::MaxPlayers ] = 10;
	parameters[ System::Parameters::Game::LevelName ] = "test";

	m_subject->ProcessMessage( System::Messages::Network::CreateServer, parameters );
}

TEST_F( NetworkSystem_Tests, should_add_client_network_provider_to_the_scene )
{
	EXPECT_CALL( *m_serviceManager, RegisterService( An< IService* >( ) ) );
	EXPECT_CALL( *m_scene, AddNetworkProvider( An< INetworkProvider* >( ) ) );

	ClientConfiguration config;

	m_subject->SetAttribute( System::Attributes::Network::IsServer, false );
	m_subject->Initialize( &config );
	m_subject->Release( );
}

TEST_F( NetworkSystem_Tests, should_set_client_to_passive_if_server )
{
	EXPECT_CALL( *m_clientProvider, SetPassive( true ) );

	AnyType::AnyTypeMap parameters;
	parameters[ System::Parameters::Network::Port ] = static_cast< unsigned int >( 8989 );
	parameters[ System::Parameters::Network::Server::MaxPlayers ] = 10;
	parameters[ System::Parameters::Game::LevelName ] = "test";

	m_subject->ProcessMessage( System::Messages::Network::CreateServer, parameters );
}

TEST_F( NetworkSystem_Tests, should_connect_to_server )
{
	std::string serverAddress = "127.0.0.1";
	unsigned int port = 8989;

	EXPECT_CALL( *m_clientProvider, Connect( serverAddress, port ) );

	AnyType::AnyTypeMap parameters;
	parameters[ System::Parameters::Network::HostAddress ] = serverAddress;
	parameters[ System::Parameters::Network::Port ] = port;

	m_subject->ProcessMessage( System::Messages::Network::Connect, parameters );
}

TEST_F( NetworkSystem_Tests, should_disconnect_from_server )
{
	EXPECT_CALL( *m_clientProvider, Disconnect( ) );
	m_subject->ProcessMessage( System::Messages::Network::Disconnect, AnyType::AnyTypeMap( ) );
}

TEST_F( NetworkSystem_Tests, should_update_the_scene )
{
	float delta = 99;

	EXPECT_CALL( *m_scene, Update( delta ) );

	m_subject->Update( delta );
}


TEST_F( NetworkSystem_Tests, should_call_select_character_when_client_picks_one )
{
	std::string characterName = "marine";

	EXPECT_CALL( *m_clientProvider, SelectCharacter( characterName ) );

	AnyType::AnyTypeMap parameters;
	parameters[ System::Parameters::Network::Client::CharacterName ] = characterName;

	m_subject->ProcessMessage( System::Messages::Network::Client::CharacterSelected, parameters );
}

TEST_F( NetworkSystem_Tests, should_find_servers )
{
	EXPECT_CALL( *m_clientProvider, FindServers( ) );
	m_subject->ProcessMessage( System::Messages::Network::Client::FindServers, AnyType::AnyTypeMap( ) );
}

TEST_F( NetworkSystem_Tests, should_return_server_ad )
{
	int cacheIndex = 0;

	AnyType::AnyTypeMap parameters;
	parameters[ System::Parameters::Network::Client::ServerCacheIndex ] = cacheIndex;

	ServerAdvertisement* ad = new ServerAdvertisement( "name", "level", 10, 1, 10, "127.0.0.1", 8989 );

	EXPECT_CALL( *m_clientProvider, GetServerAdvertisement( cacheIndex ) )
		.WillOnce( Return( ad ) );

	m_subject->ProcessMessage( System::Messages::Network::Client::GetServerAd, parameters );

	delete ad;
}

TEST_F( NetworkSystem_Tests, should_send_level_loaded )
{
	EXPECT_CALL( *m_clientProvider, LevelLoaded( ) );
	m_subject->ProcessMessage( System::Messages::Network::Client::LevelLoaded, AnyType::AnyTypeMap( ) );
}
	