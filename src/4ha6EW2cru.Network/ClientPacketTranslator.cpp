#include "ClientPacketTranslator.h"

#include <BitStream.h>
#include <GetTime.h>
using namespace RakNet;

#include "NetworkUtils.h"
#include "NetworkStream.h"
#include "ServerAdvertisement.hpp"
#include "ServerCache.h"

#include "Management/Management.h"

#include "Events/Event.h"
#include "Events/EventData.hpp"
#include "Events/ScriptEvent.hpp"
using namespace Events;

#include "Maths/MathVector3.hpp"
using namespace Maths;

#include "Utility/StringUtils.h"
using namespace Utility;

namespace Network
{
	void ClientPacketTranslator::OnPacketReceived( Packet* packet )
	{
		BitStream* stream = NetworkUtils::ReceiveNetworkMessage( packet );

		RakString message;
		stream->Read( message );

		Net( message.C_String( ), "from", packet->systemAddress.ToString( ) );

		if ( message == System::Messages::Game::ChangeLevel.c_str( ) )
		{
			RakString levelName;
			stream->Read( levelName );

			//OnChangeLevel( levelName.C_String( ) );

			BitStream stream;
			stream.Write( RakString( System::Messages::Network::Client::LevelLoaded ) );

			NetworkUtils::SendNetworkMessage( stream, packet->systemAddress, m_networkInterface );
		}

		if ( message == System::Messages::Entity::CreateEntity.c_str( ) )
		{
			RakString filePath;
			stream->Read( filePath );

			RakString name;
			stream->Read( name );

			OnCreateEntity( name.C_String( ), filePath.C_String( ), packet->systemAddress );
		}

		if( message == System::Messages::Entity::DestroyEntity.c_str( ) )
		{
			RakString name;
			stream->Read( name );

			OnDestroyEntity( name.C_String( ) );
		}

		if ( message == System::Messages::Network::ComponentUpdate.c_str( ) )
		{
			OnComponentUpdate( stream );
		}
		
		if ( message == System::Messages::Network::Server::WorldUpdate.c_str( ) )
		{
			NetworkStream networkStream( stream );

			AnyType::AnyTypeMap parameters;
			parameters[ System::Parameters::IO::Stream ] = &networkStream;

			Management::Get( )->GetServiceManager( )->FindService( System::Types::ENTITY )->Message( System::Messages::Entity::DeserializeWorld, parameters );
		}

		delete stream;
	}

	void ClientPacketTranslator::OnAdvertiseSystem( Packet* packet )
	{
		if ( !ServerCache::Get( )->Exists( packet->systemAddress.ToString( ) ) ) 
		{
			BitStream* stream = NetworkUtils::ReceiveNetworkMessage( packet );

			RakNetTime requestTime;
			stream->ReadCompressed( requestTime );

			RakString serverName;
			stream->ReadCompressed( serverName );

			int numPlayers = 0;
			stream->ReadCompressed( numPlayers );

			int maxPlayers = 0;
			stream->ReadCompressed( maxPlayers );

			RakString mapName;
			stream->ReadCompressed( mapName );

			RakNetTime ping = RakNet::GetTime( ) - requestTime;

			ServerAdvertisement* advertisment = new ServerAdvertisement( serverName.C_String( ), mapName.C_String( ), maxPlayers, numPlayers, ping, packet->systemAddress.ToString( false ), packet->systemAddress.port );

			Info( "Server Advertised", "Name:", serverName, "LevelName:", mapName, "MaxPlayers:", maxPlayers, "NumPlayers:", numPlayers, "Ping:", ping, "Address:", packet->systemAddress.ToString( false ), "Port:" ,packet->systemAddress.port );

			ServerCache::Get( )->Add( packet->systemAddress.ToString( ), advertisment ); 

			ScriptEvent* scriptEvent = new ScriptEvent( "SERVER_ADVERTISED", ServerCache::Get( )->GetCount( ) - 1 );
			Management::Get( )->GetEventManager( )->QueueEvent( scriptEvent );

			delete stream;
		}
	}

	void ClientPacketTranslator::OnDisconnected( Packet* packet )
	{
		Management::Get( )->GetEventManager( )->QueueEvent( new Event( GAME_ENDED ) );
		Management::Get( )->GetEventManager( )->QueueEvent( new ScriptEvent( "GAME_ENDED" ) ); 
		Management::Get( )->GetEventManager( )->QueueEvent( new ScriptEvent( "SERVER_DISCONNECTED" ) );
	}

	void ClientPacketTranslator::OnCreateEntity( const std::string& name, const std::string& filePath, const SystemAddress& packetAddress )
	{
		AnyType::AnyTypeMap parameters;
		parameters[ System::Attributes::Name ] = name;

		if ( name == m_networkInterface->GetExternalID( packetAddress ).ToString( ) )
		{
			parameters[ System::Attributes::FilePath ] = StringUtils::Replace( filePath, ".xml", "-fps.xml" );
		}
		else
		{
			parameters[ System::Attributes::FilePath ] = filePath;
		}

		Management::Get( )->GetServiceManager( )->FindService( System::Types::ENTITY )->Message( System::Messages::Entity::CreateEntity, parameters );
	}

	void ClientPacketTranslator::OnChangeLevel( const std::string& levelName )
	{
		/*IEventData* eventData = new LevelChangedEventData( levelName );
		IEvent* event = new Event( GAME_LEVEL_CHANGED, eventData );
		Management::Get( )->GetEventManager( )->QueueEvent( event );*/
	}

	void ClientPacketTranslator::OnDestroyEntity( const std::string& name )
	{
		AnyType::AnyTypeMap parameters;
		parameters[ System::Attributes::Name ] = name;

		Management::Get( )->GetServiceManager( )->FindService( System::Types::ENTITY )->Message( System::Messages::Entity::DestroyEntity, parameters );
	}

	void ClientPacketTranslator::OnComponentUpdate( BitStream* stream )
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

			Net( messageForEntity, "for", entityName );

			AnyType::AnyTypeMap parameters;

			if ( messageForEntity == System::Messages::SetPosition.c_str( ) )
			{
				MathVector3 position;
				stream->ReadVector( position.X, position.Y, position.Z );

				parameters[ System::Attributes::Position ] = position;
			} 
			else if ( messageForEntity == System::Messages::SetOrientation.c_str( ) )
			{
				MathQuaternion orientation;
				stream->ReadNormQuat( orientation.W, orientation.X, orientation.Y, orientation.Z );

				parameters[ System::Attributes::Orientation ] = orientation;
			}
			else
			{
				Net( "Dropping Unknown Packet" );
				break;
			}

			m_networkSystem->MessageComponent( entityName.C_String( ), messageForEntity.C_String( ), parameters );
		}
	}
}