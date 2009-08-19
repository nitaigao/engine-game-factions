#include "NetworkClientEndpoint.h"

#include "MessageIdentifiers.h"
using namespace RakNet;

#include "NetworkUtils.h"

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
		}
	}
}