#include "ServerPacketTranslator.h"

#include <BitStream.h>
using namespace RakNet;

#include "Management/Management.h"

#include "NetworkUtils.h"
#include "NetworkStream.h"
using namespace IO;

namespace Network
{
	void ServerPacketTranslator::OnClientConnected( Packet* packet )
	{
		Info( packet->systemAddress.ToString( ), "connected" );

		BitStream stream;
		stream.Write( RakString( System::Messages::Game::ChangeLevel ) );
		stream.Write( RakString( Management::Get( )->GetInstrumentation( )->GetLevelName( ) ) );

		NetworkUtils::SendNetworkMessage( stream, packet->systemAddress, m_networkInterface );
	}

	void ServerPacketTranslator::OnClientDisconnected( Packet* packet )
	{
		Info( packet->systemAddress.ToString( ), "disconnected" );

		std::string clientId = packet->systemAddress.ToString( );

		AnyType::AnyTypeMap parameters;
		parameters[ System::Attributes::Name ] = clientId;

		Management::Get( )->GetServiceManager( )->FindService( System::Types::ENTITY )->Message( System::Messages::Entity::DestroyEntity, parameters );
		m_networkInterface->CloseConnection( packet->systemAddress, true );
	}

	void ServerPacketTranslator::OnPacketReceived( Packet* packet )
	{
		BitStream* stream = NetworkUtils::ReceiveNetworkMessage( packet );

		RakString message;
		stream->Read( message );

		if ( message == System::Messages::Network::ComponentUpdate.c_str( ) )
		{
			OnComponentUpdate( message.C_String( ), stream );
		}

		if ( message == System::Messages::Network::Client::CharacterSelected.c_str( ) )
		{
			OnCharacterSelected( packet->systemAddress.ToString( ), stream );
		}

		if ( message == System::Messages::Network::Client::LevelLoaded.c_str( ) )
		{
			Info( packet->systemAddress.ToString( ), "is ready for a world state update" );

			OnLevelLoaded( packet->systemAddress.ToString( ) );
		}

		delete stream;
	}

	void ServerPacketTranslator::OnAdvertiseSystem( Packet* packet, const std::string& serverName, int maxPlayers, int playerCount )
	{
		BitStream* incomingStream = NetworkUtils::ReceiveNetworkMessage( packet );

		RakNetTime clientTime;
		incomingStream->ReadCompressed( clientTime );
		delete incomingStream;

		BitStream stream;
		stream.WriteCompressed( clientTime );
		stream.WriteCompressed( RakString( serverName ) );
		stream.WriteCompressed( playerCount );
		stream.WriteCompressed( maxPlayers );
		stream.WriteCompressed( RakString( Management::Get( )->GetInstrumentation( )->GetLevelName( ) ) );

		m_networkInterface->AdvertiseSystem( 
			packet->systemAddress.ToString( false ), packet->systemAddress.port,
			( const char* ) stream.GetData( ), stream.GetNumberOfBitsUsed( )
			);
	}

	void ServerPacketTranslator::OnComponentUpdate( const std::string& message, BitStream* stream )
	{
		while( stream->GetReadOffset( ) != stream->GetNumberOfBitsUsed( ) )
		{
			RakString messageForEntity;
			stream->Read( messageForEntity );

			if ( messageForEntity == System::Messages::Network::ComponentUpdate.c_str( ) )
			{
				stream->Read( messageForEntity );
			}

			RakString entityName;
			stream->Read( entityName );

			Net( messageForEntity.C_String( ), "for", entityName.C_String( ) );

			AnyType::AnyTypeMap parameters;

			if ( messageForEntity == System::Messages::Mouse_Moved.c_str( ) )
			{
				float deltaX;
				stream->Read( deltaX );
				parameters[ System::Parameters::DeltaX ] = deltaX;
			}

			m_networkSystem->MessageComponent( entityName.C_String( ), messageForEntity.C_String( ), parameters );
		}
	}

	void ServerPacketTranslator::OnCharacterSelected( const std::string& clientName, BitStream* stream )
	{
		RakString characterName;
		stream->Read( characterName );

		AnyType::AnyTypeMap parameters;
		parameters[ System::Attributes::Name ] = clientName;

		std::stringstream entityFilePath;
		entityFilePath << "/data/entities/" << characterName << ".xml";
		parameters[ System::Attributes::FilePath ] = entityFilePath.str( );

		Management::Get( )->GetServiceManager( )->FindService( System::Types::ENTITY )->Message( System::Messages::Entity::CreateEntity, parameters );

		Info( clientName, "has selected character:", characterName );
	}

	void ServerPacketTranslator::OnLevelLoaded( const std::string& clientName )
	{
		BitStream stream;
		NetworkStream networkStream( &stream );

		AnyType::AnyTypeMap parameters;
		parameters[ System::Parameters::IO::Stream ] = static_cast< IStream* >( &networkStream );

		Management::Get( )->GetServiceManager( )->FindService( System::Types::ENTITY )->Message( System::Messages::Entity::SerializeWorld, parameters );


		AnyType::AnyTypeMap params;
		params[ System::Parameters::IO::Stream ] = &stream;

		m_networkSystem->PushMessage( System::Messages::Network::Server::WorldUpdate, params );
	}
}