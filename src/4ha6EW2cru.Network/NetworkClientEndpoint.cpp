#include "NetworkClientEndpoint.h"

#include <MessageIdentifiers.h>
#include <RakNetTime.h>
#include <GetTime.h>
using namespace RakNet;

#include "NetworkUtils.h"
#include "ServerAdvertisement.hpp"
#include "ServerCache.h"
#include "NetworkStream.h"

#include "Management/Management.h"

#include "Events/Event.h"
#include "Events/EventData.hpp"
#include "Events/ScriptEvent.hpp"
using namespace Events;

#include "Utility/StringUtils.h"
using namespace Utility;

using namespace IO;
using namespace Services;

namespace Network
{
	NetworkClientEndpoint* NetworkClientEndpoint::m_clientEndpoint = 0;

	NetworkClientEndpoint::NetworkClientEndpoint( INetworkInterface* networkInterface, IServerCache* serverCache, Events::EventManager* eventManager, Services::IServiceManager* serviceManager )
		: m_networkInterface( networkInterface )
		, m_serverCache( serverCache )
		, m_eventManager( eventManager )
		, m_serviceManager( serviceManager )
		, m_isPassive( false )
	{
		NetworkClientEndpoint::m_clientEndpoint = this;
	}

	void NetworkClientEndpoint::Initialize( )
	{
		RPC3_REGISTER_FUNCTION( m_networkInterface->GetRPC( ), &NetworkClientEndpoint::Net_LoadLevel );
		RPC3_REGISTER_FUNCTION( m_networkInterface->GetRPC( ), &NetworkClientEndpoint::Net_CreateEntity );
		RPC3_REGISTER_FUNCTION( m_networkInterface->GetRPC( ), &NetworkClientEndpoint::Net_DestroyEntity );
		RPC3_REGISTER_FUNCTION( m_networkInterface->GetRPC( ), &NetworkClientEndpoint::Net_UpdateWorld );
	}

	void NetworkClientEndpoint::Net_LoadLevel( RakString levelName, RakNet::RPC3* rpcFromNetwork )
	{
		IEventData* eventData = new LevelChangedEventData( levelName.C_String( ) );
		IEvent* event = new Event( GAME_LEVEL_CHANGED, eventData );
		Management::Get( )->GetEventManager( )->QueueEvent( event );
	}

	void NetworkClientEndpoint::Net_CreateEntity( RakNet::RakString entityName, RakNet::RakString filePath, RPC3* rpcFromNetwork )
	{
		NetworkClientEndpoint::m_clientEndpoint->CreateEntity( entityName, filePath, rpcFromNetwork );
	}

	void NetworkClientEndpoint::Net_DestroyEntity( RakNet::RakString entityname, RakNet::RPC3* rpcFromNetwork )
	{
		NetworkClientEndpoint::m_clientEndpoint->DestroyEntity( entityname, rpcFromNetwork );
	}

	void NetworkClientEndpoint::Net_UpdateWorld( BitStream& stream, RakNet::RPC3* rpcFromNetwork )
	{
		NetworkClientEndpoint::m_clientEndpoint->UpdateWorld( stream, rpcFromNetwork );
	}

	void NetworkClientEndpoint::UpdateWorld( BitStream& stream, RakNet::RPC3* rpcFromNetwork )
	{
		NetworkStream networkStream( &stream );

		AnyType::AnyTypeMap parameters;
		parameters [ System::Parameters::IO::Stream ] = static_cast< IStream* >( &networkStream );

		m_serviceManager->FindService( System::Types::ENTITY )->ProcessMessage( System::Messages::Entity::DeSerializeWorld, parameters );
	}

	void NetworkClientEndpoint::CreateEntity( RakNet::RakString entityName, RakNet::RakString entityType, RakNet::RPC3* rpcFromNetwork )
	{
		if ( !m_isPassive )
		{
			AnyType::AnyTypeMap parameters;
			parameters[ System::Attributes::Name ] = std::string( entityName );
			parameters[ System::Attributes::EntityType ] = std::string( entityType );

			std::string fileExtension = ( entityName == m_networkInterface->GetAddress( rpcFromNetwork->GetLastSenderAddress( ) ).ToString( ) ) ? "-fps.xml" : ".xml";

			std::stringstream entityFilePath;
			entityFilePath << "/data/entities/" << entityType << fileExtension;
			parameters[ System::Attributes::FilePath ] = entityFilePath.str( );

			m_serviceManager->FindService( System::Types::ENTITY )->ProcessMessage( System::Messages::Entity::CreateEntity, parameters );
		}
	}

	void NetworkClientEndpoint::DestroyEntity( RakNet::RakString entityname, RakNet::RPC3* rpcFromNetwork )
	{
		if ( !m_isPassive )
		{
			AnyType::AnyTypeMap parameters;
			parameters[ System::Attributes::Name ] = std::string( entityname );

			IService* service = m_serviceManager->FindService( System::Types::ENTITY );
			service->ProcessMessage( System::Messages::Entity::DestroyEntity, parameters );
		}
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

			case ID_CONNECTION_REQUEST_ACCEPTED:

				m_networkInterface->GetRPC( )->SetRecipientAddress( packet->systemAddress, false );

				break;

			case ID_PONG:
				{
					BitStream* stream = NetworkUtils::ReceiveNetworkMessage( packet );

					RakNetTime requestTime;
					stream->Read( requestTime );

					RakString serverName;
					stream->Read( serverName );

					int maxPlayers = 0;
					stream->Read( maxPlayers );

					int numPlayers = 0;
					stream->Read( numPlayers );

					RakString mapName;
					stream->Read( mapName );

					RakNetTime ping = RakNet::GetTime( ) - requestTime;

					Info( "Found Server", "Address:", packet->systemAddress.ToString( ), "ServerName:", serverName, "Map:", "Ping:", ping, "MapName", mapName, "Players", numPlayers, "Max Players:", maxPlayers );

					m_serverCache->Add( serverName.C_String( ), mapName.C_String( ), maxPlayers, numPlayers, ping, packet->systemAddress.ToString( false ), packet->systemAddress.port ); 

					ScriptEvent* scriptEvent = new ScriptEvent( "SERVER_ADVERTISED", m_serverCache->GetCount( ) - 1 );
					m_eventManager->QueueEvent( scriptEvent );

					delete stream;

					break;
				}

			case ID_RPC_REMOTE_ERROR:
				{
					NetworkUtils::HandleRPCError( packet );
					
					break;
				}
			}

			m_networkInterface->DeAllocatePacket( packet );
		}
	}
}