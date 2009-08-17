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

TEST( NetworkServerEndpoint, should_respond_to_server_advertisement )
{
	SystemAddress clientAddress( "127.0.0.1", 8990 );
	RakNetTime time = RakNet::GetTime( );

	BitStream stream;
	stream.Write( ( MessageID ) ID_ADVERTISE_SYSTEM );
	stream.Write( time );
	stream.ResetReadPointer( );

	Packet p;
	p.data = stream.GetData( );
	p.bitSize = stream.GetNumberOfBitsUsed( );
	p.systemAddress = clientAddress;

	MockNetworkInterface eth0;
	EXPECT_CALL( eth0, Receive( ) )
		.WillOnce( Return( &p ) );

	MockNetworkServerController controller;
	EXPECT_CALL( controller, AdvertiseSystem( clientAddress, time ) );

	NetworkServerEndpoint endpoint( &eth0, &controller );
	endpoint.Update( 99 );
}