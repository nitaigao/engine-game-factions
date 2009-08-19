#include "NetworkServerController.h"

#include "NetworkClientEndpoint.h"

using namespace RakNet;

namespace Network
{
	NetworkServerController::~NetworkServerController( )
	{
		//delete m_rpc;
	}

	void NetworkServerController::Initialize( )
	{
		m_networkInterface->AttachPlugin( m_rpc );
	}

	void NetworkServerController::SetOrientation( const std::string& name, const Maths::MathQuaternion& orientation )
	{

	}

	void NetworkServerController::SetPosition( const std::string& name, const Maths::MathVector3& position )
	{

	}

	void NetworkServerController::ClientConnected( const SystemAddress& clientAddress )
	{
		m_rpc->SetRecipientAddress( clientAddress, false );
		RPC3_REGISTER_FUNCTION( m_rpc, &NetworkClientEndpoint::LoadLevel );
		m_rpc->CallC( "&NetworkClientEndpoint::LoadLevel", RakString( "test" ), m_rpc );
	}
}