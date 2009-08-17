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
		BitStream stream( packet->data, packet->length, false );

		unsigned char packetId;
		stream.Read( packetId );

		if ( packet )
		{
			switch( packetId )
			{

			case ID_ADVERTISE_SYSTEM:

				RakNetTime clientTime;
				stream.Read( clientTime );

				m_networkController->AdvertiseSystem( packet->systemAddress, clientTime );

				break;
			}

			m_networkInterface->DeAllocatePacket( packet );
		}
	}
}