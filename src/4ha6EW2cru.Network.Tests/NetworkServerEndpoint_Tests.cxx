#include <gtest/gtest.h>
using namespace testing;

#include "NetworkServerEndpoint.h"
using namespace Network;

#include "Mocks/MockNetworkInterface.hpp"
#include "Mocks/MockNetworkServerController.hpp"

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

	void EstablishContext( )
	{
		m_networkInterface = new MockNetworkInterface( );
		m_controller = new MockNetworkServerController( );
	}


	void DestroyContext( )
	{
		delete m_controller;
		delete m_networkInterface;
	}

	NetworkServerEndpoint* CreateSubject( )
	{
		return new NetworkServerEndpoint( m_networkInterface, m_controller );
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