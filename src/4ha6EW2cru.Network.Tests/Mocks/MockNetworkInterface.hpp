/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockNetworkInterface.cxx
*  @date   2009/08/17
*/
#pragma once
#ifndef MOCKNETWORKINTERFACE_CXX
#define MOCKNETWORKINTERFACE_CXX

#include <gmock/gmock.h>

#include "INetworkInterface.hpp"

namespace
{
	class MockNetworkInterface : public INetworkInterface
	{

	public:

		MOCK_METHOD2( Connect, void( const std::string&, unsigned int ) );
		MOCK_METHOD0( Disconnect, void( ) );
		MOCK_METHOD2( Initialize, void( unsigned int, int ) );
		MOCK_METHOD1( Destroy, void( unsigned int ) );
		MOCK_METHOD0( Receive, Packet*( ) );
		MOCK_METHOD1( DeAllocatePacket, void( Packet* ) );
		MOCK_METHOD1( SetOfflinePingInformation, void( RakNet::BitStream* ) );
		MOCK_METHOD0( GetConnectionCount, int( ) );
		MOCK_METHOD1( AttachPlugin, void( PluginInterface2* ) );
		MOCK_METHOD0( GetRPC, RakNet::RPC3*( ) );
		MOCK_METHOD0( BroadcastOfflinePing, void( ) );
		MOCK_METHOD1( GetAddress, SystemAddress( const SystemAddress& ) );
		
	};
};

#endif