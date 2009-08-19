#include "NetworkInterface.h"

#include <RakPeer.h>
#include <RakNetworkFactory.h>
using namespace RakNet;

namespace Network
{
	NetworkInterface::~NetworkInterface( )
	{
		RakNetworkFactory::DestroyRakPeerInterface( m_networkAdapter );
	}

	NetworkInterface::NetworkInterface( )
		: m_networkAdapter( RakNetworkFactory::GetRakPeerInterface( ) )
	{

	}

	void NetworkInterface::Initialize( unsigned int port, int maxConnections )
	{
		m_networkAdapter->SetMaximumIncomingConnections( maxConnections );

		SocketDescriptor descriptor( port, 0 );
		m_networkAdapter->Startup( maxConnections, 0, &descriptor, 1 );
		m_networkAdapter->SetOccasionalPing( true );
	}

	void NetworkInterface::Destroy( unsigned int timeToBlock )
	{
		m_networkAdapter->Shutdown( timeToBlock );
	}

	Packet* NetworkInterface::Receive()
	{
		return m_networkAdapter->Receive( );
	}

	void NetworkInterface::DeAllocatePacket( Packet* packet )
	{
		m_networkAdapter->DeallocatePacket( packet );
	}

	void NetworkInterface::SetOfflinePingInformation( BitStream* information )
	{
		m_networkAdapter->SetOfflinePingResponse( ( const char* ) information->GetData( ), information->GetNumberOfBytesUsed( ) );
	}

	void NetworkInterface::Connect( const std::string& address, unsigned int port )
	{
		m_networkAdapter->Connect( address.c_str( ), port, 0, 0 );
	}

	void NetworkInterface::Disconnect()
	{
	}

	void NetworkInterface::AttachPlugin( PluginInterface2* plugin )
	{
		m_networkAdapter->AttachPlugin( plugin );
	}
}