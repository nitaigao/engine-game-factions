#include "NetworkServerEndpoint.h"

#include "NetworkUtils.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
using namespace RakNet;

#include "Logging/Logger.h"
using namespace Logging;

namespace Network
{
	void NetworkServerEndpoint::Update( float deltaMilliseconds )
	{
		Packet* packet = m_networkInterface->Receive( );

		if ( packet )
		{
			BitStream stream( packet->data, packet->length, false );

			unsigned char packetId;
			stream.Read( packetId );

			switch( packetId )
			{

			case ID_NEW_INCOMING_CONNECTION:

				m_networkController->ClientConnected( packet->systemAddress );

				break;

			}

			m_networkInterface->DeAllocatePacket( packet );
		}
	}
}