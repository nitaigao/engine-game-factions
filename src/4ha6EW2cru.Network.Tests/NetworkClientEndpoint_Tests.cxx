#include <gtest/gtest.h>
using namespace testing;

#include "NetworkClientEndpoint.h"
using namespace Network;

#include <PluginInterface2.h>
#include <MessageIdentifiers.h>
#include <GetTIme.h>
using namespace RakNet;

#include "Mocks/MockNetworkInterface.hpp"
#include "Mocks/MockServerCache.hpp"

#include "Events/EventManager.h"
using namespace Events;

class NetworkClientEndpoint_Tests : public TestHarness< NetworkClientEndpoint >
{

protected:

	MockNetworkInterface* m_networkInterface;
	MockServerCache* m_serverCache;
	EventManager* m_eventManager;

	void EstablishContext( )
	{
		m_networkInterface = new MockNetworkInterface( );
		m_serverCache = new MockServerCache( );
		m_eventManager = new EventManager( );
	}

	void DestroyContext( )
	{
		delete m_networkInterface;
		delete m_serverCache;
		delete m_eventManager;
	}

	NetworkClientEndpoint* CreateSubject( )
	{
		return new NetworkClientEndpoint( m_networkInterface, m_serverCache, m_eventManager );
	}
};

TEST_F( NetworkClientEndpoint_Tests, should_receive_offline_pong_messages )
{
	std::string serverName = "serverName";
	int players = 10;
	int maxPlayers = 32;
	std::string mapName = "mapName";
	std::string serverAddress = "127.0.0.1";
	unsigned int port = 8989;

	BitStream stream;
	stream.Write( ( MessageID ) ID_PONG );
	stream.Write( GetTime( ) );
	stream.Write( RakString( serverName ) );
	stream.Write( players );
	stream.Write( maxPlayers );
	stream.Write( RakString( mapName ) );

	Packet* p = new Packet( );
	p->systemAddress = SystemAddress( serverAddress.c_str( ), port );
	p->data = stream.GetData( );
	p->length = stream.GetNumberOfBytesUsed( );

	EXPECT_CALL( *m_networkInterface, Receive( ) )
		.WillOnce( Return( p ) );

	EXPECT_CALL( *m_serverCache, Add( serverName, mapName, players, maxPlayers, An< int >( ), serverAddress, port ) );
	EXPECT_CALL( *m_networkInterface, DeAllocatePacket( p ) );

	m_subject->Update( 99 );

	m_serverCache->Clear( );

	delete p;
}

TEST_F( NetworkClientEndpoint_Tests, should_create_an_entity )
{
	
}