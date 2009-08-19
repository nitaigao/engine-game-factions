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
	void NetworkServerEndpoint::Initialize( )
	{
		RPC3_REGISTER_FUNCTION( m_networkInterface->GetRPC( ), &NetworkServerEndpoint::SelectCharacter );
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

	void NetworkServerEndpoint::SelectCharacter( RakString characterName, RakNet::RPC3* rpcFromnetwork )
	{
		std::string clientName( rpcFromnetwork->GetLastSenderAddress( ).ToString( ) );

		AnyType::AnyTypeMap parameters;
		parameters[ System::Attributes::Name ] = clientName;

		std::stringstream entityFilePath;
		entityFilePath << "/data/entities/" << characterName << ".xml";
		parameters[ System::Attributes::FilePath ] = entityFilePath.str( );

		Management::Get( )->GetServiceManager( )->FindService( System::Types::ENTITY )
			->Message( System::Messages::Entity::CreateEntity, parameters );
	}
}