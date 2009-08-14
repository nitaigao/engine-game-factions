#include "ServerNetworkProvider.h"

#include "NetworkUtils.h"

#include "Configuration/Configuration.h"
#include "Configuration/ConfigurationTypes.hpp"
using namespace Configuration;

#include <RakNetworkFactory.h>
#include <RakSleep.h>
#include <BitStream.h>
#include <MessageIdentifiers.h>
#include <GetTime.h>

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
		delete m_networkSystem;
		RakNetworkFactory::DestroyRakPeerInterface( m_networkInterface );
	}

	void ServerNetworkProvider::Release( )
	{
		m_networkInterface->Shutdown( m_configuration->Find( ConfigSections::Network, ConfigItems::Network::MaxServerReleaseTime ).As< int >( ) );
	}

	void ServerNetworkProvider::Initialize( Configuration::IConfiguration* configuration )
	{
		m_configuration = configuration;

		m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::MaxServerConnections, 10 );
		m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::ServerSleepTime, 30 );
		m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::MaxServerReleaseTime, 10 );
		m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::ServerName, "Factions Server" );
		m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::MaxPlayers, 10 );
		m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::ServerSnapshotRate, 33 );

		m_networkInterface = RakNetworkFactory::GetRakPeerInterface( );
		m_packetTranslator = new ServerPacketTranslator( m_networkSystem, m_networkInterface );

		SocketDescriptor socketDescriptor( NetworkUtils::SERVER_PORT, 0 );

		m_networkInterface->SetMaximumIncomingConnections( 
			configuration->Find( ConfigSections::Network, ConfigItems::Network::MaxServerConnections ).As< int >( ) 
			);

		m_networkInterface->Startup( 
			configuration->Find( ConfigSections::Network, ConfigItems::Network::MaxServerConnections ).As< int >( ), 
			configuration->Find( ConfigSections::Network, ConfigItems::Network::ServerSleepTime ).As< int >( ), 
			&socketDescriptor, 1 );

		m_networkInterface->SetOccasionalPing( true );
	}

	void ServerNetworkProvider::Update( float deltaMilliseconds )
	{
		RakSleep( m_configuration->Find( ConfigSections::Network, ConfigItems::Network::ServerSleepTime ).As< int >( ) );

		Packet* packet = m_networkInterface->Receive( );

		if ( packet )
		{
			TranslatePackets( packet );
			m_networkInterface->DeallocatePacket( packet );
		}

		if ( m_clients.size( ) > 0 )
		{
			UpdateClients( deltaMilliseconds );
		}
	}

	void ServerNetworkProvider::PushMessage( const System::Message& message, AnyType::AnyTypeMap parameters )
	{
		if ( message == System::Messages::Entity::CreateEntity )
		{
			std::string filePath = parameters[ System::Attributes::FilePath ].As< std::string >( );
			std::string name = parameters[ System::Attributes::Name ].As< std::string >( );

			BitStream stream;
			stream.Write( message.c_str( ) );
			stream.Write( RakString( filePath ) );
			stream.Write( RakString( name ) );

			m_sendBuffer.Write( stream );
		}
		else if ( message == System::Messages::Entity::DestroyEntity )
		{
			std::string name = parameters[ System::Attributes::Name ].As< std::string >( );

			BitStream stream;
			stream.Write( message.c_str( ) );
			stream.Write( RakString( name ) );

			m_sendBuffer.Write( stream );
		}
		else if ( message == System::Messages::SetPosition || message == System::Messages::SetOrientation )
		{
			std::string entityName = parameters[ System::Attributes::Name ].As< std::string >( );

			BitStream stream;
			stream.Write( System::Messages::Network::ComponentUpdate.c_str( ) );
			stream.Write( message.c_str( ) );
			stream.Write( entityName.c_str( ) );

			if ( message == System::Messages::SetPosition )
			{
				MathVector3 position = parameters[ System::Attributes::Position ].As< MathVector3 >( );
				stream.WriteVector( position.X, position.Y, position.Z );
			}

			if ( message == System::Messages::SetOrientation )
			{
				MathQuaternion orientation = parameters[ System::Attributes::Orientation ].As< MathQuaternion >( );
				stream.WriteNormQuat( orientation.W, orientation.X, orientation.Y, orientation.Z );
			}

			m_sendBuffer.Write( stream );
		} 
	}

	void ServerNetworkProvider::PushMessage( const SystemAddress& address, const System::Message& message, AnyType::AnyTypeMap parameters )
	{
		if ( message == System::Messages::Network::Server::WorldUpdate )
		{
			BitStream* stream = parameters[ System::Parameters::IO::Stream ].As< BitStream* >( );

			BitStream streamToSend;
			streamToSend.Write( message.c_str( ) );
			streamToSend.Write( *stream );
			NetworkUtils::SendNetworkMessage( streamToSend, address, m_networkInterface );
		}
	}

	void ServerNetworkProvider::UpdateClients( float deltaMilliseconds )
	{
		m_tickRate = 1.0f / m_configuration->Find( ConfigSections::Network, ConfigItems::Network::ServerSnapshotRate ).As< int >( );

		if ( m_tickTotal >= m_tickRate && m_sendBuffer.GetNumberOfBitsUsed( ) > 0 )
		{
			for ( SystemAddressList::iterator i = m_clients.begin( ); i != m_clients.end( ); ++i )
			{
				m_sendBuffer.ResetReadPointer( );
				NetworkUtils::SendNetworkMessage( m_sendBuffer, ( *i ), m_networkInterface );
			}

			m_sendBuffer.Reset( );
			m_tickTotal = 0.0f;
		}

		m_tickTotal += deltaMilliseconds;
	}

	void ServerNetworkProvider::TranslatePackets( Packet* packet )
	{
		unsigned char packetId = NetworkUtils::GetPacketIdentifier( packet );

		switch( packetId )
		{

		case ID_NEW_INCOMING_CONNECTION:

			m_clients.push_back( packet->systemAddress );

			m_packetTranslator->OnClientConnected( packet );

			break;

		case ID_DISCONNECTION_NOTIFICATION:

			for( SystemAddressList::iterator i = m_clients.begin( ); i != m_clients.end( ); )
			{
				if ( ( *i ) == packet->systemAddress )
				{
					i = m_clients.erase( i );
				}
				else
				{
					++i;
				}
			}

			m_packetTranslator->OnClientDisconnected( packet );

			break;

		case ID_REMOTE_CONNECTION_LOST:

			Info( packet->systemAddress.ToString( false ), " has lost connection" );

			break;

		case ID_PING_OPEN_CONNECTIONS:

			Info( "Ping from ", packet->systemAddress.ToString( ) );

			break;

		case ID_ADVERTISE_SYSTEM:

			Info( "Advertise from ", packet->systemAddress.ToString( ) );

			m_packetTranslator->OnAdvertiseSystem( 
				packet, 
				m_configuration->Find( ConfigSections::Network, ConfigItems::Network::ServerName ).As< std::string >( ), 
				m_configuration->Find( ConfigSections::Network, ConfigItems::Network::MaxPlayers ).As< int >( ),
				m_clients.size( )
				);

			break;

		case ID_USER_PACKET_ENUM:

			m_packetTranslator->OnPacketReceived( packet );

			break;
		}
	}
}