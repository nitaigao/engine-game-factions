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
#include "Configuration/ConfigurationTypes.hpp"
using namespace Configuration;

class NetworkServerProvider_Tests : public TestHarness< NetworkServerProvider >
{
	
protected:

	MockNetworkInterface* m_networkInterface;
	MockNetworkServerController* m_controller;
	MockNetworkServerEndpoint* m_endpoint;
	ClientConfiguration* m_configuration;

	void EstablishContext( )
	{
		m_networkInterface = new MockNetworkInterface( );
		m_controller = new MockNetworkServerController( );
		m_endpoint = new MockNetworkServerEndpoint( ); 
		m_configuration = new ClientConfiguration( );

		m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::ServerPort, 0 );
	}

	NetworkServerProvider* CreateSubject( )
	{
		return new NetworkServerProvider( m_configuration, m_networkInterface, m_controller, m_endpoint );
	}

};

TEST_F( NetworkServerProvider_Tests, should_initialize_network_interface )
{
	EXPECT_CALL( *m_networkInterface, Initialize( An< unsigned int >( ), An< int >( ) ) );
	m_subject->Initialize( 0 );
}

TEST_F( NetworkServerProvider_Tests, should_update_endpoint )
{
	float delta = 99;
	EXPECT_CALL( *m_endpoint, Update( delta ) );
	m_subject->Update( delta );
}

TEST_F( NetworkServerProvider_Tests, should_set_offline_message_on_level_changed )
{	
	EXPECT_CALL( *m_networkInterface, GetConnectionCount( ) )
		.WillOnce( Return( 1 ) );

	EXPECT_CALL( *m_networkInterface, SetOfflinePingInformation( A< BitStream* >( ) ) );

	m_subject->Initialize( 0 );

	Event event( EventTypes::GAME_LEVEL_CHANGED, new LevelChangedEventData( "test" ) );
	m_subject->OnGameLevelChanged( &event );
}

TEST_F( NetworkServerProvider_Tests, should_initialize_controller )
{
	EXPECT_CALL( *m_controller, Initialize( ) );

	m_subject->Initialize( 0 );
}

TEST_F( NetworkServerProvider_Tests, should_create_entity_using_controller )
{
	std::string entityName = "testname";
	std::string entityType = "type";;

	AnyType::AnyTypeMap parameters;
	parameters[ System::Attributes::FilePath ] = "filePath";
	parameters[ System::Attributes::EntityType ] = "type";

	EXPECT_CALL( *m_controller, CreateEntity( entityName, entityType ) );
	m_subject->Message( entityName, System::Messages::Entity::CreateEntity, parameters );
}

TEST_F( NetworkServerProvider_Tests, should_destroy_entity_using_the_controller )
{
	std::string entityName = "hello";

	AnyType::AnyTypeMap parameters;
	parameters[ System::Attributes::Name ] = entityName;

	EXPECT_CALL( *m_controller, DestroyEntity( entityName ) );
	m_subject->Message( entityName, System::Messages::Entity::DestroyEntity, parameters );
}

TEST_F( NetworkServerProvider_Tests, should_forward_mouse_moved_events_to_the_network )
{
	std::string entityName = "test";

	AnyType::AnyTypeMap parameters;
	parameters[ System::Parameters::DeltaX ] = "1.0f";

	EXPECT_CALL( *m_controller, MessageEntity( entityName, System::Messages::Mouse_Moved, An< AnyType::AnyTypeMap >( ) ) );

	m_subject->Message( entityName, System::Messages::Mouse_Moved, parameters );
}

/*TEST_F( NetworkServerProvider_Tests, should_update_the_controller )
{
	float delta = 10.0f;

	EXPECT_CALL( *m_controller, Update( delta ) );

	m_subject->Update( delta );
}

/*TEST_F( NetworkServerProvider_Tests, should_forward_position_events_to_clients )
{
	MathVector3 position = MathVector3::Forward( );
	std::string entityName = "test";

	EXPECT_CALL( *m_controller, SetEntityPosition( entityName, position ) );

	AnyType::AnyTypeMap parameters;
	parameters[ System::Attributes::Position ] = position;

	m_subject->Message( entityName, System::Messages::SetPosition, parameters );
}*/