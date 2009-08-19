#include <gtest/gtest.h>
using namespace testing;

#include "NetworkClientController.h"
using namespace Network;


TEST( NetworkClientController_Tests, should_attach_rpc_to_network_interface )
{
	MockNetworkInterface eth0;
	EXPECT_CALL( eth0, AttachPlugin( A< PluginInterface2* >( ) ) );

	NetworkClientController controller( &eth0 );
	controller.Initialize( );
}
