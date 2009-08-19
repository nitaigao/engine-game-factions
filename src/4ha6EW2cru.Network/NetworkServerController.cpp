#include "NetworkServerController.h"

#include "NetworkClientEndpoint.h"

using namespace RakNet;

#include "Management/Management.h"

namespace Network
{
	NetworkServerController::~NetworkServerController( )
	{

	}

	void NetworkServerController::Initialize( )
	{
		RPC3_REGISTER_FUNCTION( m_networkInterface->GetRPC( ), &NetworkClientEndpoint::LoadLevel );
	}

	void NetworkServerController::SetOrientation( const std::string& name, const Maths::MathQuaternion& orientation )
	{

	}

	void NetworkServerController::SetPosition( const std::string& name, const Maths::MathVector3& position )
	{

	}

	void NetworkServerController::ClientConnected( const SystemAddress& clientAddress )
	{
		m_networkInterface->GetRPC( )->SetRecipientAddress( clientAddress, false );
		m_networkInterface->GetRPC( )->CallC( "&NetworkClientEndpoint::LoadLevel", RakString( Management::Get( )->GetInstrumentation( )->GetLevelName( ) ) );
	}
}