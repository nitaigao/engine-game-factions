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

class NetworkClientEndpoint_Tests : public TestHarness< NetworkClientEndpoint >
{

protected:

	MockNetworkInterface* m_networkInterface;
	MockServerCache* m_serverCache;

	void EstablishContext( )
	{
		m_networkInterface = new MockNetworkInterface( );
		m_serverCache = new MockServerCache( );
	}

	void DestroyContext( )
	{
		delete m_networkInterface;
		delete m_serverCache;
	}

	NetworkClientEndpoint* CreateSubject( )
	{
		return new NetworkClientEndpoint( m_networkInterface, m_serverCache );
	}
};

TEST_F( NetworkClientEndpoint_Tests, should_receive_offline_pong_messages )
{
	BitStream stream;
	stream.Write( ( MessageID ) ID_PONG );
	stream.Write( GetTime( ) );
	stream.Write( RakString( "ServerName" ) );
	stream.Write( 10 );
	stream.Write( 32 );
	stream.Write( "Map Name" );

	Packet* p = new Packet( );
	p->systemAddress = SystemAddress( "127.0.0.1", 8989 );
	p->data = stream.GetData( );
	p->length = stream.GetNumberOfBytesUsed( );

	EXPECT_CALL( *m_networkInterface, Receive( ) )
		.WillOnce( Return( p ) );

	EXPECT_CALL( *m_serverCache, Add( A< const std::string& >( ), An< IServerAdvertisement* >( ) ) );

	EXPECT_CALL( *m_networkInterface, DeAllocatePacket( p ) );

	m_subject->Update( 99 );

	delete p;
}