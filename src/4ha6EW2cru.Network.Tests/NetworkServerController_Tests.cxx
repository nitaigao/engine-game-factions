#include <gtest/gtest.h>
using namespace testing;

#include "NetworkServerController.h"
using namespace Network;

#include "Mocks/MockNetworkInterface.hpp"

TEST( NetworkServerController, should_attach_rpc_plugin_to_interface )
{
	MockNetworkInterface eth0;
	EXPECT_CALL( eth0, AttachPlugin( An< PluginInterface2* >( ) ) );

	NetworkServerController controller( &eth0 );
	controller.Initialize( );
}