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

	NetworkServerEndpoint::NetworkServerEndpoint( INetworkInterface* networkInterface, INetworkServerController* controller )
		: m_networkInterface( networkInterface )
		, m_networkController( controller )
	{
		NetworkServerEndpoint::m_networkServerEndpoint = this;
	}

	void NetworkServerEndpoint::Initialize( )
	{
		RPC3_REGISTER_FUNCTION( m_networkInterface->GetRPC( ), &NetworkServerEndpoint::Net_SelectCharacter );
		RPC3_REGISTER_FUNCTION( m_networkInterface->GetRPC( ), &NetworkServerEndpoint::Net_LevelLoaded );
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
			->Message( System::Messages::Entity::CreateEntity, parameters );
	}

	void NetworkServerEndpoint::Net_LevelLoaded( RakString levelName, RakNet::RPC3* rpcFromNetwork )
	{ 
		 NetworkServerEndpoint::m_networkServerEndpoint->LevelLoaded( rpcFromNetwork ); 
	};

	void NetworkServerEndpoint::LevelLoaded( RakNet::RPC3* rpcFromNetwork )
	{
		m_networkController->SendWorldUpdate( rpcFromNetwork->GetLastSenderAddress( ) );
	}
}