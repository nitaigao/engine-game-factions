#include "precompiled.h"

#include "NetworkUtils.h"

#include "Logging/Logger.h"
using namespace Logging;

#include "Maths/MathVector3.hpp"
#include "Maths/MathQuaternion.hpp"
using namespace Maths;

#include <RakString.h>
#include <BitStream.h>
#include <MessageIdentifiers.h>
#include <RPC3.h>
using namespace RakNet;

#include "System/SystemType.hpp"

#include "Exceptions/OutOfRangeException.hpp"

namespace Network
{
  const unsigned int NetworkUtils::SERVER_PORT = 8989;
  const SystemAddress NetworkUtils::BROADCAST_ADDRESS = SystemAddress( "255.255.255.255", NetworkUtils::SERVER_PORT );

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

  void NetworkUtils::HandleRPCError( Packet* packet )
  {
    switch ( packet->data[1] )
    {
    case RakNet::RPC_ERROR_NETWORK_ID_MANAGER_UNAVAILABLE:
      Fatal( "RPC Error:", packet->data + 2, "RPC_ERROR_NETWORK_ID_MANAGER_UNAVAILABLE" );
      break;

    case RakNet::RPC_ERROR_OBJECT_DOES_NOT_EXIST:
      Fatal( "RPC Error:", packet->data + 2, "RPC_ERROR_OBJECT_DOES_NOT_EXIST" );
      break;

    case RakNet::RPC_ERROR_FUNCTION_INDEX_OUT_OF_RANGE:
      Fatal( "RPC Error:", packet->data + 2, "RPC_ERROR_FUNCTION_INDEX_OUT_OF_RANGE" );
      break;

    case RakNet::RPC_ERROR_FUNCTION_NOT_REGISTERED:
      Fatal( "RPC Error:", packet->data + 2, "RPC_ERROR_FUNCTION_NOT_REGISTERED" );
      break;

    case RakNet::RPC_ERROR_FUNCTION_NO_LONGER_REGISTERED:
      Fatal( "RPC Error:", packet->data + 2, "RPC_ERROR_FUNCTION_NO_LONGER_REGISTERED" );
      break;

    case RakNet::RPC_ERROR_CALLING_CPP_AS_C:
      Fatal( "RPC Error:", packet->data + 2, "RPC_ERROR_CALLING_CPP_AS_C" );
      break;

    case RakNet::RPC_ERROR_CALLING_C_AS_CPP:
      Fatal( "RPC Error:", packet->data + 2, "RPC_ERROR_CALLING_C_AS_CPP" );
      break;
    }
  }
}