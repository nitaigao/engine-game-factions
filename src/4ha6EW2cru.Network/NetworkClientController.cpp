#include "precompiled.h"

#include "NetworkClientController.h"

#include "NetworkServerEndpoint.h"

#include "RakString.h"
#include "RakPeerInterface.h"
using namespace RakNet;

namespace Network
{
	void NetworkClientController::Initialize()
	{
		RPC3_REGISTER_FUNCTION( m_networkInterface->GetRPC( ), &NetworkServerEndpoint::Net_SelectCharacter );
		RPC3_REGISTER_FUNCTION( m_networkInterface->GetRPC( ), &NetworkServerEndpoint::Net_LevelLoaded );
		RPC3_REGISTER_FUNCTION( m_networkInterface->GetRPC( ), &NetworkServerEndpoint::Net_MessageEntity );
	}

	void NetworkClientController::SelectCharacter( const std::string& characterName )
	{
		m_networkInterface->GetRPC( )->CallC( "&NetworkServerEndpoint::Net_SelectCharacter", RakString( characterName ) );
	}

	void NetworkClientController::FindServers( unsigned int port ) 
	{
		m_networkInterface->BroadcastOfflinePing( port );
	}

	void NetworkClientController::LevelLoaded( )
	{
		if ( !m_isPassive )
		{
			m_networkInterface->GetRPC( )->CallC( "&NetworkServerEndpoint::Net_LevelLoaded", RakString( "levelName" ) );
		}
	}

	void NetworkClientController::MessageEntity( const std::string& entityName, const System::MessageType& message, AnyType::AnyTypeMap parameters )
	{
		BitStream stream;

		if ( message == System::Messages::Mouse_Moved )
		{
			float deltaX = parameters[ System::Parameters::DeltaX ].As< float >( );
			stream.Write( deltaX );

			float deltaY = parameters[ System::Parameters::DeltaY ].As< float >( );
			stream.Write( deltaY );
		}

		SystemAddress clientAddress = m_networkInterface->GetAddress( m_networkInterface->GetRPC( )->GetRakPeer( )->GetSystemAddressFromIndex( 0 ) );

		if ( !m_isPassive && entityName == clientAddress.ToString( ) )
		{
			SystemAddress serverAddress = m_networkInterface->GetRPC( )->GetRakPeer( )->GetSystemAddressFromIndex( 0 );
			m_networkInterface->GetRPC( )->SetRecipientAddress( serverAddress, false );
			m_networkInterface->GetRPC( )->CallC( "&NetworkServerEndpoint::Net_MessageEntity", RakString( entityName ), RakString( message ), stream );
		}
	}
}