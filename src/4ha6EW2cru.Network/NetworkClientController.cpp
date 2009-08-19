#include "NetworkClientController.h"

#include "NetworkServerEndpoint.h"

#include "RakString.h"
using namespace RakNet;

namespace Network
{
	void NetworkClientController::Initialize()
	{
		RPC3_REGISTER_FUNCTION( m_networkInterface->GetRPC( ), &NetworkServerEndpoint::SelectCharacter );
	}

	void NetworkClientController::SelectCharacter( const std::string& characterName )
	{
		m_networkInterface->GetRPC( )->CallC( "&NetworkServerEndpoint::SelectCharacter", RakString( characterName ) );
	}
}