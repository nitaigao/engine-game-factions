#include <gtest/gtest.h>
using namespace testing;

#include "NetworkClientProvider.h"
using namespace Network;

#include "Mocks/MockNetworkInterface.hpp"
#include "Mocks/MockNetworkClientEndpoint.hpp"
#include "Mocks/MockNetworkClientController.hpp"

#include "Configuration/Configuration.h"
using namespace Configuration;

TEST( NetworkClientProvider, should_initialize_network_interface )
{
	unsigned int port = 8989;
	int maxConnections = 10;

	MockNetworkClientController* controller = new MockNetworkClientController( );
	EXPECT_CALL( *controller, Initialize( ) );

	MockNetworkClientEndpoint* endpoint = new MockNetworkClientEndpoint( );
	EXPECT_CALL( *endpoint, Initialize( ) );

	MockNetworkInterface* eth0 = new MockNetworkInterface( );
	EXPECT_CALL( *eth0, Initialize( port, maxConnections ) );

	ClientConfiguration config;

	NetworkClientProvider provider( &config, eth0, controller, endpoint );
	provider.Initialize( port, maxConnections );
}

TEST( NetworkClientProvider, should_connect_to_a_server )
{
	std::string address = "127.0.0.1";
	unsigned int port = 8989;

	MockNetworkInterface* eth0 = new MockNetworkInterface( );
	EXPECT_CALL( *eth0, Connect( address, port ) );

	ClientConfiguration config;

	NetworkClientProvider provider( &config, eth0, 0, 0 );
	provider.Connect( address, port );
}

TEST( NetworkClientProvider, should_disconnect_from_a_server )
{
	MockNetworkInterface* eth0 = new MockNetworkInterface( );
	EXPECT_CALL( *eth0, Disconnect( ) );

	ClientConfiguration config;

	NetworkClientProvider provider( &config, eth0, 0, 0 );
	provider.Disconnect( );
}

TEST( NetworkClientProvider, should_initialize_endpoint )
{
	MockNetworkClientController* controller = new MockNetworkClientController( );
	EXPECT_CALL( *controller, Initialize( ) );

	MockNetworkClientEndpoint* endpoint = new MockNetworkClientEndpoint( );
	EXPECT_CALL( *endpoint, Initialize( ) );

	MockNetworkInterface* eth0 = new MockNetworkInterface( );
	EXPECT_CALL( *eth0, Initialize( An< unsigned int >( ), An< int >( ) ) );

	NetworkClientProvider provider( 0, eth0, controller, endpoint );
	provider.Initialize( 0, 0 );
}

TEST( NetworkClientProvider_Tests, should_update_the_endpoint )
{
	float delta = 99;

	MockNetworkClientEndpoint* endpoint = new MockNetworkClientEndpoint( );
	EXPECT_CALL( *endpoint, Update( delta ) );

	NetworkClientProvider provider( 0, 0, 0, endpoint );
	provider.Update( delta );
}

TEST( NetworkClientProvider_Tests, should_initialize_the_client_controller )
{
	MockNetworkClientController* controller = new MockNetworkClientController( );
	EXPECT_CALL( *controller, Initialize( ) );

	MockNetworkClientEndpoint* endpoint = new MockNetworkClientEndpoint( );
	EXPECT_CALL( *endpoint, Initialize( ) );

	MockNetworkInterface* eth0 = new MockNetworkInterface( );
	EXPECT_CALL( *eth0, Initialize( An< unsigned int >( ), An< int >( ) ) );

	NetworkClientProvider provider( 0, eth0, controller, endpoint );
	provider.Initialize( 0, 0 );
}

TEST( NetworkClientProvider_Tests, should_select_a_character )
{
	std::string characterName = "marine";

	MockNetworkClientController* controller = new MockNetworkClientController( );
	EXPECT_CALL( *controller, SelectCharacter( characterName ) );

	NetworkClientProvider provider( 0, 0, controller, 0 );
	provider.SelectCharacter( characterName );
}