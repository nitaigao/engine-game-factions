#include "NetworkServerEndpoint.h"

#include "NetworkUtils.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
using namespace RakNet;

#include "Logging/Logger.h"
using namespace Logging;

#include "Management/Management.h"

namespace Network
{
	NetworkServerEndpoint* NetworkServerEndpoint::m_networkServerEndpoint = 0;

	NetworkServerEndpoint::NetworkServerEndpoint( INetworkInterface* networkInterface, INetworkSystemScene* networkScene, INetworkServerController* controller )
		: m_networkInterface( networkInterface )
		, m_networkController( controller )
		, m_networkScene( networkScene )
	{
		NetworkServerEndpoint::m_networkServerEndpoint = this;
	}

	void NetworkServerEndpoint::Initialize( )
	{
		RPC3_REGISTER_FUNCTION( m_networkInterface->GetRPC( ), &NetworkServerEndpoint::Net_SelectCharacter );
		RPC3_REGISTER_FUNCTION( m_networkInterface->GetRPC( ), &NetworkServerEndpoint::Net_LevelLoaded );
		RPC3_REGISTER_FUNCTION( m_networkInterface->GetRPC( ), &NetworkServerEndpoint::Net_MessageEntity );
	}

	void NetworkServerEndpoint::Update( float deltaMilliseconds )
	{
		Packet* packet = m_networkInterface->Receive( );

		if ( packet )
		{
			MessageID messageId = NetworkUtils::GetPacketIdentifier( packet );
			DefaultMessageIDTypes messageType = ( DefaultMessageIDTypes ) messageId;

			switch( messageId )
			{

			case ID_NEW_INCOMING_CONNECTION:

				m_networkController->ClientConnected( packet->systemAddress );

				break;

			case ID_DISCONNECTION_NOTIFICATION:

				m_networkController->ClientDisconnected( packet->systemAddress );

				break;

			case ID_RPC_REMOTE_ERROR:

				NetworkUtils::HandleRPCError( packet );

				break;

			}

			m_networkInterface->DeAllocatePacket( packet );
		}
	}

	void NetworkServerEndpoint::Net_SelectCharacter( RakString characterName, RakNet::RPC3* rpcFromnetwork )
	{
		SystemAddress serverAddress = rpcFromnetwork->GetRakPeer( )->GetSystemAddressFromIndex( 0 );
		SystemAddress clientAddress = rpcFromnetwork->GetLastSenderAddress( );

		std::string clientName( rpcFromnetwork->GetLastSenderAddress( ).ToString( ) );

		AnyType::AnyTypeMap parameters;
		parameters[ System::Attributes::Name ] = clientName; 
		parameters[ System::Attributes::EntityType ] = std::string( characterName );

		std::string fileExtension = ( clientAddress == serverAddress ) ? "-fps.xml" : ".xml";

		std::stringstream entityFilePath;
		entityFilePath << "/data/entities/" << characterName << fileExtension;
		parameters[ System::Attributes::FilePath ] = entityFilePath.str( );

		Management::Get( )->GetServiceManager( )->FindService( System::Types::ENTITY )
			->ProcessMessage( System::Messages::Entity::CreateEntity, parameters );
	}

	void NetworkServerEndpoint::Net_LevelLoaded( RakString levelName, RakNet::RPC3* rpcFromNetwork )
	{ 
		 NetworkServerEndpoint::m_networkServerEndpoint->LevelLoaded( rpcFromNetwork ); 
	};

	void NetworkServerEndpoint::Net_MessageEntity( RakNet::RakString entityName, RakNet::RakString message, RakNet::BitStream& parameters, RakNet::RPC3* rpcFromNetwork )
	{
		AnyType::AnyTypeMap parametersMap;

		Debug( message, "for", entityName );

		if ( message == System::Messages::Mouse_Moved )
		{
			float deltaX = 0.0f;
			parameters.Read( deltaX );
			parametersMap[ System::Parameters::DeltaX ] = deltaX;

			float deltaY = 0.0f;
			parameters.Read( deltaY );
			parametersMap[ System::Parameters::DeltaY ] = deltaY;
		}

		NetworkServerEndpoint::m_networkServerEndpoint->MessageEntity( entityName.C_String( ), message.C_String( ), parametersMap, rpcFromNetwork );
	}

	void NetworkServerEndpoint::LevelLoaded( RakNet::RPC3* rpcFromNetwork )
	{
		m_networkController->SendWorldUpdate( rpcFromNetwork->GetLastSenderAddress( ) );
	}

	void NetworkServerEndpoint::MessageEntity( const std::string& entityName, const System::MessageType& message, AnyType::AnyTypeMap parameters, RakNet::RPC3* rpcFromNetwork )
	{
		m_networkScene->MessageComponent( entityName, message, parameters );
	}
}