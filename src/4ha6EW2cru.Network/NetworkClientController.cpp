#include "NetworkClientController.h"

#include "NetworkServerEndpoint.h"

#include "RakString.h"
using namespace RakNet;

namespace Network
{
	void NetworkClientController::Initialize()
	{
		RPC3_REGISTER_FUNCTION( m_networkInterface->GetRPC( ), &NetworkServerEndpoint::Net_SelectCharacter );
		RPC3_REGISTER_FUNCTION( m_networkInterface->GetRPC( ), &NetworkServerEndpoint::Net_LevelLoaded );
	}

	void NetworkClientController::SelectCharacter( const std::string& characterName )
	{
		m_networkInterface->GetRPC( )->CallC( "&NetworkServerEndpoint::Net_SelectCharacter", RakString( characterName ) );
	}

	void NetworkClientController::FindServers( ) 
	{
		m_networkInterface->BroadcastOfflinePing( );
	}

	void NetworkClientController::LevelLoaded( )
	{
		m_networkInterface->GetRPC( )->CallC( "&NetworkServerEndpoint::Net_LevelLoaded", RakString( "levelName" ) );
	}
}