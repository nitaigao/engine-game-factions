#include "NetworkClientEndpoint.h"

#include "MessageIdentifiers.h"
using namespace RakNet;

#include "NetworkUtils.h"

namespace Network
{
	void NetworkClientEndpoint::Initialize( )
	{
		m_networkInterface->AttachPlugin( m_rpc );

		RPC3_REGISTER_FUNCTION( m_rpc, &NetworkClientEndpoint::LoadLevel );
	}

	void NetworkClientEndpoint::LoadLevel( RakString levelName, RakNet::RPC3* rpcFromNetwork )
	{
		
	}

	void NetworkClientEndpoint::Update( float deltaMilliseconds )
	{

		Packet* packet = m_networkInterface->Receive( );

		if ( packet )
		{
			MessageID messageId = NetworkUtils::GetPacketIdentifier( packet );
			DefaultMessageIDTypes messageType = ( DefaultMessageIDTypes ) messageId;
		}

	}
}