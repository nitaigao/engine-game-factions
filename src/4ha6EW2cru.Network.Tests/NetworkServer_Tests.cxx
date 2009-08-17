#include <gtest/gtest.h>
using namespace testing;

#include <gmock/gmock.h>

#include "NetworkServerProvider.h"
#include "NetworkSystem.h"
using namespace Network;

#include "Mocks/MockNetworkInterface.hpp"

TEST( NetworkServerProvider_Tests, should_start_network_on_initialize )
{
	/*unsigned int serverPort = 8989;
	int maxPlayers = 10;

	MockNetworkInterface* eth0 = new MockNetworkInterface( ); 

	EXPECT_CALL( *eth0, Initialize( serverPort, maxPlayers ) );

	NetworkServerProvider network( eth0 );
	network.Initialize( serverPort, maxPlayers );*/
}