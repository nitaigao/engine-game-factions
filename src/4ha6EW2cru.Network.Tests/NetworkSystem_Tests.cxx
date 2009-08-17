#include <gtest/gtest.h>
using namespace testing;

#include "NetworkSystem.h"
#include "ServerNetworkProvider.h"
using namespace Network;

#include "Mocks/MockNetworkSystemScene.hpp"

TEST( NetworkSystem_Tests, should_add_server_network_provider_to_scene )
{
	MockNetworkSystemScene* scene = new MockNetworkSystemScene( );
	EXPECT_CALL( *scene, AddNetworkProvider( An< INetworkProvider* >( ) ) );

	NetworkSystem system( scene );
	
	AnyType::AnyTypeMap parameters;
	parameters[ System::Parameters::Network::Port ] = static_cast< unsigned int >( 8989 );
	parameters[ System::Parameters::Network::Server::MaxPlayers ] = 10;

	system.Message( System::Messages::Network::CreateServer, parameters );

	delete scene;
}

TEST( NetworkSystem_Tests, should_update_the_scene )
{
	float delta = 99;

	MockNetworkSystemScene scene;
	EXPECT_CALL( scene, Update( delta ) );

	NetworkSystem system( &scene );
	system.Update( delta );
}