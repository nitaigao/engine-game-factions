#include <gtest/gtest.h>
using namespace testing;

#include "NetworkClientProvider.h"
#include "ServerAdvertisement.hpp"
using namespace Network;

#include "Mocks/MockNetworkInterface.hpp"
#include "Mocks/MockNetworkClientEndpoint.hpp"
#include "Mocks/MockNetworkClientController.hpp"
#include "Mocks/MockServerCache.hpp"

#include "Configuration/Configuration.h"
using namespace Configuration;

class NetworkClientProvider_Tests : public TestHarness< NetworkClientProvider >
{

protected:
	 
	MockNetworkInterface* m_networkInterface;
	MockNetworkClientController* m_controller;
	MockNetworkClientEndpoint* m_endpoint;
	MockServerCache* m_serverCache;

	void EstablishContext( )
	{
		m_networkInterface = new MockNetworkInterface( );
		m_controller = new MockNetworkClientController( );
		m_endpoint = new MockNetworkClientEndpoint( );
		m_serverCache = new MockServerCache( );
	}

	void DestroyContext( )
	{

	}

	NetworkClientProvider* CreateSubject( )
	{
		return new NetworkClientProvider( m_networkInterface, m_controller, m_endpoint, m_serverCache );
	}
};

TEST_F( NetworkClientProvider_Tests, should_initialize_network_interface )
{
	unsigned int port = 8989;
	int maxConnections = 10;

	EXPECT_CALL( *m_controller, Initialize( ) );
	EXPECT_CALL( *m_endpoint, Initialize( ) );
	EXPECT_CALL( *m_networkInterface, Initialize( port, maxConnections ) );

	m_subject->Initialize( port, maxConnections );
}

TEST_F( NetworkClientProvider_Tests, should_connect_to_a_server )
{
	std::string address = "127.0.0.1";
	unsigned int port = 8989;

	EXPECT_CALL( *m_networkInterface, Connect( address, port ) );

	m_subject->Connect( address, port );
}

TEST_F( NetworkClientProvider_Tests, should_disconnect_from_a_server )
{
	EXPECT_CALL( *m_networkInterface, Disconnect( ) );

	m_subject->Disconnect( );
}

TEST_F( NetworkClientProvider_Tests, should_initialize_endpoint )
{
	EXPECT_CALL( *m_controller, Initialize( ) );
	EXPECT_CALL( *m_endpoint, Initialize( ) );
	EXPECT_CALL( *m_networkInterface, Initialize( An< unsigned int >( ), An< int >( ) ) );

	m_subject->Initialize( 0, 0 );
}

TEST_F( NetworkClientProvider_Tests, should_update_the_endpoint )
{
	float delta = 99;

	EXPECT_CALL( *m_endpoint, Update( delta ) );

	m_subject->Update( delta );
}

TEST_F( NetworkClientProvider_Tests, should_initialize_the_client_controller )
{
	EXPECT_CALL( *m_controller, Initialize( ) );
	EXPECT_CALL( *m_endpoint, Initialize( ) );
	EXPECT_CALL( *m_networkInterface, Initialize( An< unsigned int >( ), An< int >( ) ) );

	m_subject->Initialize( 0, 0 );
}

TEST_F( NetworkClientProvider_Tests, should_select_a_character )
{
	std::string characterName = "marine";

	EXPECT_CALL( *m_controller, SelectCharacter( characterName ) );

	m_subject->SelectCharacter( characterName );
}

TEST_F( NetworkClientProvider_Tests, should_find_servers )
{
	EXPECT_CALL( *m_controller, FindServers( ) );
	EXPECT_CALL( *m_serverCache, Clear( ) );
	m_subject->FindServers( );
}

TEST_F( NetworkClientProvider_Tests, should_get_server_ad )
{
	int cacheIndex = 0;

	IServerAdvertisement* ad = new ServerAdvertisement( "name", "level", 10, 1, 10, "127.0.0.1", 8989 );

	EXPECT_CALL( *m_serverCache, Find( cacheIndex ) )
		.WillOnce( Return( ad ) );

	IServerAdvertisement* result = m_subject->GetServerAdvertisement( cacheIndex );

	EXPECT_EQ( ad, result );

	delete ad;
}

TEST_F( NetworkClientProvider_Tests, should_set_passive_mode )
{
	bool isPassive = true;

	EXPECT_CALL( *m_endpoint, SetPassive( isPassive ) );
	EXPECT_CALL( *m_controller, SetPassive( isPassive ) );

	m_subject->SetPassive( isPassive );
}

TEST_F( NetworkClientProvider_Tests, should_send_level_loaded_to_controller )
{
	EXPECT_CALL( *m_controller, LevelLoaded( ) );
	m_subject->LevelLoaded( );
}

TEST_F( NetworkClientProvider_Tests, should_forward_input_events_to_the_network )
{
	std::string entityName = "test";

	AnyType::AnyTypeMap parameters;
	parameters[ System::Parameters::DeltaX ] = "1.0f";

	EXPECT_CALL( *m_controller, MessageEntity( entityName, System::Messages::Mouse_Moved, An< AnyType::AnyTypeMap >( ) ) );

	m_subject->Message( entityName, System::Messages::Mouse_Moved, parameters );
}