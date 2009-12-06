#include <gtest/gtest.h>
using namespace testing;

#include "NetworkServerEndpoint.h"
using namespace Network;

#include "Mocks/MockNetworkInterface.hpp"
#include "Mocks/MockNetworkServerController.hpp"
#include "Mocks/MockNetworkSystemScene.hpp"
#include "Mocks/MockServiceManager.hpp"

#include <RakNetTime.h>
#include <BitStream.h>
#include <MessageIdentifiers.h>
#include <GetTime.h>
using namespace RakNet;


class NetworkServerEndpoint_Tests : public TestHarness< NetworkServerEndpoint >
{

protected:

	MockNetworkInterface* m_networkInterface;
	MockNetworkServerController* m_controller;
	MockNetworkSystemScene* m_scene;
	MockServiceManager* m_serviceManager;

	void EstablishContext( )
	{
		m_networkInterface = new MockNetworkInterface( );
		m_controller = new MockNetworkServerController( );
		m_scene = new MockNetworkSystemScene( );
		m_serviceManager = new MockServiceManager( );
	}


	void DestroyContext( )
	{
		delete m_controller;
		delete m_networkInterface;
		delete m_scene;
		delete m_serviceManager;
	}

	NetworkServerEndpoint* CreateSubject( )
	{
		return new NetworkServerEndpoint( m_networkInterface, m_scene, m_controller, m_serviceManager );
	}
};

TEST_F( NetworkServerEndpoint_Tests, should_intruct_client_on_connect )
{
	SystemAddress clientAddress( "127.0.0.1", 8990 );
	
	BitStream stream;
	stream.Write( ( MessageID ) ID_NEW_INCOMING_CONNECTION );
	stream.ResetReadPointer( );

	Packet p;
	p.data = stream.GetData( );
	p.bitSize = stream.GetNumberOfBitsUsed( );
	p.systemAddress = clientAddress;

	EXPECT_CALL( *m_networkInterface, Receive( ) )
		.WillOnce( Return( &p ) );

	EXPECT_CALL( *m_controller, ClientConnected( clientAddress ) );

	m_subject->Update( 99 );
}

TEST_F( NetworkServerEndpoint_Tests, should_destroy_client_entity_on_disconnect )
{
	SystemAddress clientAddress( "127.0.0.1", 8990 );

	BitStream stream;
	stream.Write( ( MessageID ) ID_DISCONNECTION_NOTIFICATION );
	stream.ResetReadPointer( );

	Packet p;
	p.data = stream.GetData( );
	p.bitSize = stream.GetNumberOfBitsUsed( );
	p.systemAddress = clientAddress;

	EXPECT_CALL( *m_networkInterface, Receive( ) )
		.WillOnce( Return( &p ) );

	EXPECT_CALL( *m_controller, ClientDisconnected( clientAddress ) );

	m_subject->Update( 99 );
}

TEST_F( NetworkServerEndpoint_Tests, should_message_entity_mouse_moved )
{
	std::string entityName = "test";

	AnyType::AnyTypeMap parameters;
	parameters[ System::Parameters::DeltaX ] = 0.1f;

	EXPECT_CALL( *m_scene, MessageComponent( entityName, System::Messages::Mouse_Moved, An< AnyType::AnyTypeMap >( ) ) );

	m_subject->MessageEntity( entityName, System::Messages::Mouse_Moved, parameters, 0 );
}