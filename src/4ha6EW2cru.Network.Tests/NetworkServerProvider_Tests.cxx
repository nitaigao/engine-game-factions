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

class NetworkServerProvider_Tests : public ::testing::Test
{

public:

	virtual void SetUp( )
	{
		m_networkInterface = new MockNetworkInterface( );
		m_controller = new MockNetworkServerController( );
		m_endpoint = new MockNetworkServerEndpoint( ); 
	}

	MockNetworkInterface* m_networkInterface;
	MockNetworkServerController* m_controller;
	MockNetworkServerEndpoint* m_endpoint;
};

TEST_F( NetworkServerProvider_Tests, should_initialize_network_interface )
{
	EXPECT_CALL( *m_networkInterface, Initialize( An< unsigned int >( ), An< int >( ) ) );

	ClientConfiguration config;

	NetworkServerProvider provider( &config, m_networkInterface, m_controller, m_endpoint );
	provider.Initialize( 0, 0 );
}

TEST_F( NetworkServerProvider_Tests, should_update_endpoint )
{
	float delta = 99;
	EXPECT_CALL( *m_endpoint, Update( delta ) );

	NetworkServerProvider provider( 0, m_networkInterface, m_controller, m_endpoint );
	provider.Update( delta );
}

TEST_F( NetworkServerProvider_Tests, should_handle_set_position_messages )
{
	std::string entityName = "test";
	MathVector3 position = MathVector3::Forward( );

	EXPECT_CALL( *m_controller, SetPosition( entityName, position ) );

	AnyType::AnyTypeMap parameters;
	parameters[ System::Attributes::Position ] = position;

	NetworkServerProvider provider( 0, m_networkInterface, m_controller, m_endpoint );
	provider.Message( entityName, System::Messages::SetPosition, parameters );
}

TEST_F( NetworkServerProvider_Tests, should_set_offline_message_on_level_changed )
{
	MockNetworkInterface* eth0 = new MockNetworkInterface( );
	
	EXPECT_CALL( *eth0, GetConnectionCount( ) )
		.WillOnce( Return( 1 ) );

	EXPECT_CALL( *eth0, SetOfflinePingInformation( A< BitStream* >( ) ) );

	ClientConfiguration config;

	NetworkServerProvider provider( &config, eth0, m_controller, m_endpoint);
	provider.Initialize( 0, 0 );

	Event event( GAME_LEVEL_CHANGED, new LevelChangedEventData( "test" ) );
	provider.OnGameLevelChanged( &event );
}

TEST_F( NetworkServerProvider_Tests, should_initialize_controller )
{
	EXPECT_CALL( *m_controller, Initialize( ) );

	ClientConfiguration config;

	NetworkServerProvider provider( &config, m_networkInterface, m_controller, m_endpoint );
	provider.Initialize( 0, 0 );
}