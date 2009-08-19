#include <gtest/gtest.h>
using namespace testing;

#include "NetworkServerProvider.h"
using namespace Network;

#include "Maths/MathVector3.hpp"
using namespace Maths;

#include "System/AnyType.hpp"

#include "Management/Management.h"

#include "Mocks/MockNetworkInterface.hpp"
#include "Mocks/MockNetworkServerController.hpp"
#include "Mocks/MockNetworkServerEndpoint.hpp"

#include "Events/Event.h"
#include "Events/EventData.hpp"
using namespace Events;

#include <BitStream.h>
using namespace RakNet;

#include "Configuration/Configuration.h"
using namespace Configuration;

TEST( NetworkServerProvider, should_initialize_network_interface )
{
	MockNetworkInterface* eth0 = new MockNetworkInterface( );
	EXPECT_CALL( *eth0, Initialize( An< unsigned int >( ), An< int >( ) ) );

	ClientConfiguration config;

	NetworkServerProvider provider( &config, eth0, new MockNetworkServerController( ), 0 );
	provider.Initialize( 0, 0 );
}

TEST( NetworkServerProvider, should_update_endpoint )
{
	float delta = 99;

	MockNetworkServerEndpoint* endpoint = new MockNetworkServerEndpoint( ); 
	EXPECT_CALL( *endpoint, Update( delta ) );

	NetworkServerProvider provider( 0, 0, 0, endpoint );
	provider.Update( delta );
}

TEST( NetworkServerProvider, should_handle_set_position_messages )
{
	std::string entityName = "test";
	MathVector3 position = MathVector3::Forward( );

	MockNetworkServerController* controller = new MockNetworkServerController( );
	EXPECT_CALL( *controller, SetPosition( entityName, position ) );

	AnyType::AnyTypeMap parameters;
	parameters[ System::Attributes::Position ] = position;

	NetworkServerProvider provider( 0, 0, controller, 0 );
	provider.Message( entityName, System::Messages::SetPosition, parameters );
}

TEST( NetworkServerController, should_set_offline_message_on_level_changed )
{
	MockNetworkInterface* eth0 = new MockNetworkInterface( );
	
	EXPECT_CALL( *eth0, GetConnectionCount( ) )
		.WillOnce( Return( 1 ) );

	EXPECT_CALL( *eth0, SetOfflinePingInformation( A< BitStream* >( ) ) );

	ClientConfiguration config;

	NetworkServerProvider provider( &config, eth0, new MockNetworkServerController( ), 0 );
	provider.Initialize( 0, 0 );

	Event event( GAME_LEVEL_CHANGED, new LevelChangedEventData( "test" ) );
	provider.OnGameLevelChanged( &event );
}

TEST( NetworkServerProvider_Tests, should_initialize_controller )
{
	MockNetworkServerController* controller = new MockNetworkServerController( );
	EXPECT_CALL( *controller, Initialize( ) );

	MockNetworkInterface* networkInterface = new MockNetworkInterface( );

	ClientConfiguration config;

	NetworkServerProvider provider( &config, networkInterface, controller, 0 );
	provider.Initialize( 0, 0 );
}