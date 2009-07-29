#include "ClientNetworkProvider.h"

#include "NetworkUtils.h"

#include "Configuration/Configuration.h"
#include "Configuration/ConfigurationTypes.hpp"
using namespace Configuration;

#include <RakNetworkFactory.h>
#include <RakSleep.h>
#include <BitStream.h>
#include <RakPeer.h>
#include <MessageIdentifiers.h>
using namespace RakNet;

#include "Logging/Logger.h"
using namespace Logging;

#include "Events/Event.h"
#include "Events/EventData.hpp"
using namespace Events;

#include "Management/Management.h"

#include "Maths/MathVector3.hpp"
using namespace Maths;

#include "NetworkStream.h"

namespace Network
{
	ClientNetworkProvider::~ClientNetworkProvider()
	{
		if ( m_networkInterface != 0 )
		{
			delete m_networkInterface;
		}
	}

	void ClientNetworkProvider::Release()
	{
		m_networkInterface->Shutdown( m_configuration->Find( ConfigSections::Network, ConfigItems::Network::MaxClientReleaseTime ).As< int >( ) );
	}

	void ClientNetworkProvider::Initialize( Configuration::IConfiguration* configuration )
	{
		m_configuration = configuration;

		m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::MaxClientConnections, 1 );
		m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::ClientSleepTime, 0 );
		m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::MaxClientReleaseTime, 10 );

		m_networkInterface = new RakPeer( );

		m_networkInterface->Startup( 
			m_configuration->Find( ConfigSections::Network, ConfigItems::Network::MaxClientConnections ).As< int >( ), 
			m_configuration->Find( ConfigSections::Network, ConfigItems::Network::ClientSleepTime ).As< int >( ), 
			&SocketDescriptor( ), 1 
			);
	}

	void ClientNetworkProvider::Update( const float& deltaMilliseconds )
	{
		RakSleep( m_configuration->Find( ConfigSections::Network, ConfigItems::Network::ClientSleepTime ).As< int >( ) );

		Packet* packet = m_networkInterface->Receive( );

		std::stringstream logMessage;

		if ( packet )
		{
			unsigned char packetId = NetworkUtils::GetPacketIdentifier( packet );
			DefaultMessageIDTypes messageType = static_cast< DefaultMessageIDTypes >( packetId );

			switch( packetId )
			{

			case ID_NO_FREE_INCOMING_CONNECTIONS:

				logMessage << packet->systemAddress.ToString( ) << " is full";

				break;

			case ID_CONNECTION_REQUEST_ACCEPTED:

				logMessage << packet->systemAddress.ToString( ) << " accepted the connection";

				break;

			case ID_CONNECTION_LOST:

				logMessage << packet->systemAddress.ToString( ) << " disconnected";

				break;

			case ID_CONNECTION_ATTEMPT_FAILED:

				logMessage << "Failed to connect to " << packet->systemAddress.ToString( );

				break;

			case ID_USER_PACKET_ENUM:

				this->OnPacketReceived( packet );

				break;
			}

			if( logMessage.str( ).length( ) > 0 )
			{
				Info( logMessage.str( ) );
			}

			m_networkInterface->DeallocatePacket( packet );
		}
	}

	AnyType::AnyTypeMap ClientNetworkProvider::Message( const System::Message& message, AnyType::AnyTypeMap parameters )
	{
		AnyType::AnyTypeMap results;

		if ( message == System::Messages::Network::Connect )
		{
			m_serverAddress = SystemAddress(
				parameters[ System::Parameters::Network::HostAddress ].As< std::string >( ).c_str( ),
				parameters[ System::Parameters::Network::Port ].As< int >( )
				);

			m_networkInterface->Connect( 
				m_serverAddress.ToString( false ),
				m_serverAddress.port,
				0, 0
			);
		}

		if( message == System::Messages::Network::Client::CharacterSelected )
		{
			BitStream stream;
			stream.Write( RakString( message.c_str( ) ) );

			std::string characterName = parameters[ System::Parameters::Network::Client::CharacterName ].As< std::string >( );
			stream.Write( RakString( characterName.c_str( ) ) );
			
			NetworkUtils::SendNetworkMessage( stream, m_serverAddress, m_networkInterface );
		}

		return results;
	}

	void ClientNetworkProvider::OnPacketReceived( Packet* packet )
	{
		BitStream* stream = NetworkUtils::ReceiveNetworkMessage( packet );

		RakString message;
		stream->Read( message );

		if ( message == System::Messages::Game::ChangeLevel.c_str( ) )
		{
			RakString levelName;
			stream->Read( levelName );
			
			IEventData* eventData = new LevelChangedEventData( levelName.C_String( ) );
			IEvent* event = new Event( GAME_LEVEL_CHANGED, eventData );
			Management::Get( )->GetEventManager( )->QueueEvent( event );
		}

		if ( message == System::Messages::Entity::CreateEntity.c_str( ) )
		{
			RakString filePath;
			stream->Read( filePath );

			RakString characterName;
			stream->Read( characterName );

			AnyType::AnyTypeMap parameters;
			parameters[ System::Attributes::Name ] = characterName.C_String( );
			parameters[ System::Attributes::FilePath ] = filePath.C_String( );

			Management::Get( )->GetServiceManager( )->FindService( System::Types::ENTITY )->Message( System::Messages::Entity::CreateEntity, parameters );
		}

		if ( message == System::Messages::Network::ComponentUpdate.c_str( ) )
		{
			RakString messageForEntity;
			stream->Read( messageForEntity );

			RakString entityName;
			stream->Read( entityName );

			AnyType::AnyTypeMap parameters;

			if ( messageForEntity == System::Messages::SetPosition.c_str( ) )
			{
				MathVector3 position;
				stream->Read( position );

				parameters[ System::Attributes::Position ] = position;
			}

			m_networkSystem->MessageComponent( entityName.C_String( ), messageForEntity.C_String( ), parameters );
		}

		delete stream;
	}

	void ClientNetworkProvider::PushMessage( const System::Message& message, AnyType::AnyTypeMap parameters )
	{
		if ( 
			message == System::Messages::Move_Forward_Pressed ||
			message == System::Messages::Move_Backward_Pressed ||
			message == System::Messages::Move_Forward_Released ||
			message == System::Messages::Move_Backward_Released ||
			message == System::Messages::Strafe_Right_Pressed ||
			message == System::Messages::Strafe_Left_Pressed ||
			message == System::Messages::Strafe_Right_Released ||
			message == System::Messages::Strafe_Left_Released ||
			message == System::Messages::Jump ||
			message == System::Messages::Mouse_Moved
			)
		{
			std::string entityName = parameters[ System::Attributes::Name ].As< std::string >( );

			BitStream stream;

			stream.Write( System::Messages::Network::ComponentUpdate.c_str( ) );
			stream.Write( message.c_str( ) );
			stream.Write( entityName.c_str( ) );

			if ( message == System::Messages::Mouse_Moved )
			{
				float deltaX = parameters[ System::Parameters::DeltaX ].As< float >( );
				stream.Write( deltaX );
			}

			NetworkUtils::SendNetworkMessage( stream, m_serverAddress, m_networkInterface );
		}
	}
}