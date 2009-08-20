#include "NetworkClientEndpoint.h"

#include <MessageIdentifiers.h>
#include <RakNetTime.h>
#include <GetTime.h>
using namespace RakNet;

#include "NetworkUtils.h"
#include "ServerAdvertisement.hpp"
#include "ServerCache.h"

#include "Management/Management.h"

#include "Events/Event.h"
#include "Events/EventData.hpp"
#include "Events/ScriptEvent.hpp"
using namespace Events;

namespace Network
{
	void NetworkClientEndpoint::Initialize( )
	{
		RPC3_REGISTER_FUNCTION( m_networkInterface->GetRPC( ), &NetworkClientEndpoint::LoadLevel );
	}

	void NetworkClientEndpoint::LoadLevel( RakString levelName, RakNet::RPC3* rpcFromNetwork )
	{
		IEventData* eventData = new LevelChangedEventData( levelName.C_String( ) );
		IEvent* event = new Event( GAME_LEVEL_CHANGED, eventData );
		Management::Get( )->GetEventManager( )->QueueEvent( event );
	}

	void NetworkClientEndpoint::Update( float deltaMilliseconds )
	{
		Packet* packet = m_networkInterface->Receive( );

		if ( packet )
		{
			MessageID messageId = NetworkUtils::GetPacketIdentifier( packet );
			DefaultMessageIDTypes messageType = ( DefaultMessageIDTypes ) messageId;

			switch( messageId )
			{

			case ID_PONG:

				BitStream* stream = NetworkUtils::ReceiveNetworkMessage( packet );

				RakNetTime requestTime;
				stream->Read( requestTime );

				RakString serverName;
				stream->Read( serverName );

				int numPlayers = 0;
				stream->Read( numPlayers );

				int maxPlayers = 0;
				stream->Read( maxPlayers );

				RakString mapName;
				stream->Read( mapName );

				RakNetTime ping = RakNet::GetTime( ) - requestTime;

				//ServerAdvertisement* advertisment = new ServerAdvertisement( serverName.C_String( ), mapName.C_String( ), maxPlayers, numPlayers, ping, packet->systemAddress.ToString( false ), packet->systemAddress.port );

				//Info( "Server Advertised", "Name:", serverName, "LevelName:", mapName, "MaxPlayers:", maxPlayers, "NumPlayers:", numPlayers, "Ping:", ping, "Address:", packet->systemAddress.ToString( false ), "Port:" ,packet->systemAddress.port );

				m_serverCache->Add( packet->systemAddress.ToString( ), 0 ); 

				//ScriptEvent* scriptEvent = new ScriptEvent( "SERVER_ADVERTISED", m_serverCache->GetCount( ) - 1 );
				//Management::Get( )->GetEventManager( )->QueueEvent( scriptEvent );

				delete stream;

				break;
			}

			m_networkInterface->DeAllocatePacket( packet );
		}
	}
}