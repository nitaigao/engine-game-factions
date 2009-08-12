#include "ClientNetworkProvider.h"

#include "NetworkUtils.h"

#include <RakNetworkFactory.h>
#include <RakSleep.h>
#include <BitStream.h>
#include <RakPeer.h>
#include <MessageIdentifiers.h>
#include <GetTime.h>
using namespace RakNet;

#include "Configuration/Configuration.h"
#include "Configuration/ConfigurationTypes.hpp"
using namespace Configuration;

#include "Logging/Logger.h"
using namespace Logging;

#include "ServerCache.h"

namespace Network
{
	ClientNetworkProvider::~ClientNetworkProvider()
	{
		delete m_messageRouter;
		m_messageRouter = 0;
		
		delete m_packetTranslator;
		m_packetTranslator = 0;

		RakNetworkFactory::DestroyRakPeerInterface( m_networkInterface );
	}

	void ClientNetworkProvider::Initialize( Configuration::IConfiguration* configuration )
	{
		m_configuration = configuration;

		ServerCache::Initialize( );

		m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::MaxClientConnections, 1 );
		m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::ClientSleepTime, 0 );
		m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::MaxClientReleaseTime, 10 );
		m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::ClientSnapshotRate, 33 );

		m_networkInterface = new RakPeer( );
		m_messageRouter = new ClientMessageRouter( m_networkInterface );
		m_packetTranslator = new ClientPacketTranslator( m_networkSystem, m_networkInterface );

		m_networkInterface->Startup( 
			m_configuration->Find( ConfigSections::Network, ConfigItems::Network::MaxClientConnections ).As< int >( ), 
			m_configuration->Find( ConfigSections::Network, ConfigItems::Network::ClientSleepTime ).As< int >( ), 
			&SocketDescriptor( ), 1 
			);

		m_networkInterface->SetOccasionalPing( true );
	}

	void ClientNetworkProvider::Release( )
	{
		ServerCache::Destroy( );

		m_networkInterface->Shutdown( m_configuration->Find( ConfigSections::Network, ConfigItems::Network::MaxClientReleaseTime ).As< int >( ) );
	}

	void ClientNetworkProvider::Update( const float& deltaMilliseconds )
	{
		RakSleep( m_configuration->Find( ConfigSections::Network, ConfigItems::Network::ClientSleepTime ).As< int >( ) );

		Packet* packet = m_networkInterface->Receive( );

		if ( packet )
		{
			TranslatePackets( packet );
			m_networkInterface->DeallocatePacket( packet );
		}

		m_messageRouter->UpdateServer( deltaMilliseconds, m_configuration->Find( ConfigSections::Network, ConfigItems::Network::ClientSnapshotRate ).As< int >( ) );
	}

	AnyType::AnyTypeMap ClientNetworkProvider::Message( const System::Message& message, AnyType::AnyTypeMap parameters )
	{
		AnyType::AnyTypeMap results;

		if ( message == System::Messages::Network::Connect )
		{
			m_messageRouter->Connect( parameters );
		}

		if ( message == System::Messages::Network::Disconnect )
		{
			m_messageRouter->Disconnect( );
		}

		if ( message == System::Messages::Network::Client::GetServerAd )
		{
			m_messageRouter->GetServerAdvertisement( parameters, results );
		}

		if( message == System::Messages::Network::Client::FindServers )
		{
			m_messageRouter->FindServers( );
		}

		if( message == System::Messages::Network::Client::CharacterSelected )
		{
			m_messageRouter->SelectCharacter( message, parameters );
		}

		return results;
	}

	void ClientNetworkProvider::PushMessage( const System::Message& message, AnyType::AnyTypeMap parameters )
	{
		m_messageRouter->PushMessage( message, parameters );
	}

	void ClientNetworkProvider::TranslatePackets( Packet* packet )
	{
		Net( "Received packet from", packet->systemAddress.ToString( ) );
		MessageID messageId = NetworkUtils::GetPacketIdentifier( packet );

		switch( messageId )
		{

		case ID_NO_FREE_INCOMING_CONNECTIONS:

			Info( packet->systemAddress.ToString( ), "is full" );

			break;

		case ID_CONNECTION_REQUEST_ACCEPTED:

			Info( packet->systemAddress.ToString( ), "accepted the connection" );

			break;

		case ID_CONNECTION_LOST:

			Info( packet->systemAddress.ToString( ), "disconnected" );

			m_packetTranslator->OnDisconnected( packet );

			break;

		case ID_CONNECTION_ATTEMPT_FAILED:

			Info( "Failed to connect to",  packet->systemAddress.ToString( ) );

			break;

		case ID_ADVERTISE_SYSTEM:

			m_packetTranslator->OnAdvertiseSystem( packet );

			break;

		case ID_USER_PACKET_ENUM:

			m_packetTranslator->OnPacketReceived( packet );

			break;
		}
	}
}