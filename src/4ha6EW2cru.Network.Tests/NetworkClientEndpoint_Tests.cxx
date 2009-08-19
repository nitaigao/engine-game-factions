#include <gtest/gtest.h>
using namespace testing;

#include "NetworkClientEndpoint.h"
using namespace Network;

#include <PluginInterface2.h>
using namespace RakNet;

#include "Mocks/MockNetworkInterface.hpp"

TEST( NetworkClientEndpoint_Tests, should_attach_rpc_plugin_to_interface )
{
	MockNetworkInterface eth0;
	EXPECT_CALL( eth0, AttachPlugin( An< PluginInterface2* >( ) ) );

	NetworkClientEndpoint endpoint( &eth0 );
	endpoint.Initialize( );
}