#include "NetworkUtils.h"

#include "Logging/Logger.h"
using namespace Logging;

#include "Maths/MathVector3.hpp"
#include "Maths/MathQuaternion.hpp"
using namespace Maths;

#include <RakString.h>
#include <BitStream.h>
#include <MessageIdentifiers.h>
using namespace RakNet;

#include "System/SystemType.hpp"

#include "Exceptions/OutOfRangeException.hpp"

namespace Network
{
	unsigned char NetworkUtils::GetPacketIdentifier( Packet *packet )
	{
		if ( packet == 0 )
		{
			return 255;
		}

		if ( ( unsigned char ) packet->data[ 0 ] == ID_TIMESTAMP )
		{
			assert( packet->length > sizeof( unsigned char ) + sizeof( unsigned long ) );
			return ( unsigned char ) packet->data[ sizeof( unsigned char ) + sizeof( unsigned long ) ];
		}

		return ( unsigned char ) packet->data[ 0 ];
	}

	void NetworkUtils::SendNetworkMessage( BitStream& data, const SystemAddress& destination, RakPeerInterface* networkInterface )
	{
		BitStream stream;
		stream.Write( ( MessageID ) ID_USER_PACKET_ENUM );
		stream.Write( data );
		networkInterface->Send( &stream, MEDIUM_PRIORITY, RELIABLE, 0, destination, false );
	}

	RakNet::BitStream* NetworkUtils::ReceiveNetworkMessage( Packet* packet )
	{
		BitStream* bitStream = new BitStream( packet->data, packet->length, false );

		MessageID messageId;
		bitStream->Read( messageId );

		return bitStream;
	}
}