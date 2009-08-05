#include "ServerNetworkProvider.h"

#include "NetworkUtils.h"

#include "Configuration/Configuration.h"
#include "Configuration/ConfigurationTypes.hpp"
using namespace Configuration;

#include <RakNetworkFactory.h>
#include <RakSleep.h>
#include <BitStream.h>
#include <MessageIdentifiers.h>

using namespace RakNet;

#include <sstream>

#include "Logging/Logger.h"
using namespace Logging;

#include "Management/Management.h"

#include "Maths/MathVector3.hpp"
using namespace Maths;

namespace Network
{
	ServerNetworkProvider::~ServerNetworkProvider()
	{
		if ( m_networkInterface != 0 )
		{
			delete m_networkInterface;
		}
	}

	void ServerNetworkProvider::Release()
	{
		m_networkInterface->Shutdown( m_configuration->Find( ConfigSections::Network, ConfigItems::Network::MaxServerReleaseTime ).As< int >( ) );
	}

	void ServerNetworkProvider::Initialize( Configuration::IConfiguration* configuration )
	{
		m_configuration = configuration;

		configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::MaxServerConnections, 10 );
		configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::ServerSleepTime, 30 );
		m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::MaxServerReleaseTime, 10 );

		m_networkInterface = RakNetworkFactory::GetRakPeerInterface( );

		SocketDescriptor socketDescriptor( NetworkUtils::SERVER_PORT, 0 );

		m_networkInterface->SetMaximumIncomingConnections( 
			configuration->Find( ConfigSections::Network, ConfigItems::Network::MaxServerConnections ).As< int >( ) 
			);

		m_networkInterface->Startup( 
			configuration->Find( ConfigSections::Network, ConfigItems::Network::MaxServerConnections ).As< int >( ), 
			configuration->Find( ConfigSections::Network, ConfigItems::Network::ServerSleepTime ).As< int >( ), 
			&socketDescriptor, 1 );
	}

	void ServerNetworkProvider::Update( const float& deltaMilliseconds )
	{
		RakSleep( m_configuration->Find( ConfigSections::Network, ConfigItems::Network::ServerSleepTime ).As< int >( ) );

		Packet* packet = m_networkInterface->Receive( );

		std::stringstream logMessage;

		if ( packet )
		{
			unsigned char packetId = NetworkUtils::GetPacketIdentifier( packet );
			DefaultMessageIDTypes messageType = static_cast< DefaultMessageIDTypes >( packetId );

			switch( packetId )
			{

			case ID_NEW_INCOMING_CONNECTION:

				this->OnClientConnected( packet );

				break;

			case ID_REMOTE_DISCONNECTION_NOTIFICATION:
			case ID_DISCONNECTION_NOTIFICATION:

				this->OnClientDisconnected( packet );

				break;

			case ID_REMOTE_CONNECTION_LOST:

				logMessage << packet->systemAddress.ToString( false ) << " has lost connection";

				break;

			case ID_PING:
			case ID_PING_OPEN_CONNECTIONS:

				logMessage << "Ping from " << packet->systemAddress.ToString( );;

				break;

			case ID_USER_PACKET_ENUM:

				this->OnPacketReceived( packet );
			}

			if( logMessage.str( ).length( ) > 0 )
			{
				Info( logMessage.str( ) );
			}

			m_networkInterface->DeallocatePacket( packet );
		}
	}

	void ServerNetworkProvider::OnClientConnected( Packet* packet )
	{
		Info( packet->systemAddress.ToString( ), "connected" );

		m_clients.push_back( packet->systemAddress );

		BitStream stream;
		stream.Write( RakString( System::Messages::Game::ChangeLevel.c_str( ) ) );
		stream.Write( RakString( Management::Get( )->GetInstrumentation( )->GetLevelName( ).c_str( ) ) );

		NetworkUtils::SendNetworkMessage( stream, packet->systemAddress, m_networkInterface );
	}

	void ServerNetworkProvider::OnClientDisconnected( Packet* packet )
	{
		Info( packet->systemAddress.ToString( ), "disconnected" );

		AnyType::AnyTypeMap parameters;
		parameters[ System::Attributes::Name ] = packet->systemAddress.ToString( );

		Management::Get( )->GetServiceManager( )->FindService( System::Types::ENTITY )->Message( System::Messages::Entity::DestroyEntity, parameters );
	}

	void ServerNetworkProvider::OnPacketReceived( Packet* packet )
	{
		BitStream* stream = NetworkUtils::ReceiveNetworkMessage( packet );

		RakString message;
		stream->Read( message );

		if ( message == System::Messages::Network::ComponentUpdate.c_str( ) )
		{
			RakString messageForEntity;
			stream->Read( messageForEntity );

			RakString entityName;
			stream->Read( entityName );

			AnyType::AnyTypeMap parameters;

			if ( messageForEntity == System::Messages::Mouse_Moved.c_str( ) )
			{
				float deltaX;
				stream->Read( deltaX );
				parameters[ System::Parameters::DeltaX ] = deltaX;
			}

			m_networkSystem->MessageComponent( entityName.C_String( ), messageForEntity.C_String( ), parameters );
		}

		if ( message == System::Messages::Network::Client::RequestServerInfo.c_str( ) )
		{
			Net( "Request Server Info from: ", packet->systemAddress.ToString( ) );
		}

		if ( message == System::Messages::Network::Client::CharacterSelected.c_str( ) )
		{
			RakString characterName;
			stream->Read( characterName );

			AnyType::AnyTypeMap parameters;
			parameters[ System::Attributes::Name ] = packet->systemAddress.ToString( );

			std::stringstream entityFilePath;
			entityFilePath << "/data/entities/" << characterName.C_String( ) << ".xml";
			parameters[ System::Attributes::FilePath ] = entityFilePath.str( );

			Management::Get( )->GetServiceManager( )->FindService( System::Types::ENTITY )->Message( System::Messages::Entity::CreateEntity, parameters );

			Net( packet->systemAddress.ToString( ), "has selected character:", characterName );
		}

		delete stream;
	}

	void ServerNetworkProvider::PushMessage( const System::Message& message, AnyType::AnyTypeMap parameters )
	{
		if ( message == System::Messages::Entity::CreateEntity )
		{
			std::string filePath = parameters[ System::Attributes::FilePath ].As< std::string >( );
			std::string name = parameters[ System::Attributes::Name ].As< std::string >( );

			BitStream stream;

			stream.Write( message.c_str( ) );
			stream.Write( RakString( filePath.c_str( ) ) );
			stream.Write( RakString( name.c_str( ) ) );

			for ( SystemAddressList::iterator i = m_clients.begin( ); i != m_clients.end( ); ++i )
			{
				NetworkUtils::SendNetworkMessage( stream, ( *i ), m_networkInterface );
			}
		}
	}
}