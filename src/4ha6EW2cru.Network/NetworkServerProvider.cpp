#include "NetworkServerProvider.h"

#include "NetworkInterface.h"
#include "NetworkServerEndpoint.h"
#include "NetworkServerController.h"

#include "Maths/MathVector3.hpp"
using namespace Maths;

#include "Events/EventData.hpp"
using namespace Events;

#include "Configuration/ConfigurationTypes.hpp"
using namespace Configuration;

#include "Management/Management.h"

#include <BitStream.h>
using namespace RakNet;

namespace Network
{
	NetworkServerProvider::~NetworkServerProvider( )
	{
		delete m_configuration;
		delete m_endpoint;
		delete m_controller;
		delete m_networkInterface;
	}

	void NetworkServerProvider::Initialize( unsigned int port, int maxConnections)
	{
		m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::MaxServerConnections, 10 );
		m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::ServerSleepTime, 30 );
		m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::MaxServerReleaseTime, 10 );
		m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::ServerName, "Factions Server" );
		m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::MaxPlayers, 10 );
		m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::ServerSnapshotRate, 33 );

		m_networkInterface->Initialize( port, maxConnections );
		m_controller->Initialize( );
		m_endpoint->Initialize( );
	}

	void NetworkServerProvider::Message( const std::string& entityName, const System::MessageType& message, AnyType::AnyTypeMap parameters )
	{
		if ( message == System::Messages::SetPosition )
		{
			m_controller->SetEntityPosition( entityName, parameters[ System::Attributes::Position ].As< MathVector3 >( ) );
		}

		if ( message == System::Messages::SetOrientation )
		{
			//m_attributes[ System::Attributes::Orientation ] = parameters[ System::Attributes::Orientation ].As< MathQuaternion >( );
		}

		if ( message == System::Messages::Mouse_Moved )
		{
			//m_attributes[ System::Parameters::DeltaX ] = parameters[ System::Parameters::DeltaX ].As< float >( );
		}

		if ( message == System::Messages::Entity::CreateEntity )
		{
			m_controller->CreateEntity( entityName, parameters[ System::Attributes::EntityType ].As< std::string >( ) );
		}

		if ( message == System::Messages::Entity::DestroyEntity )
		{
			m_controller->DestroyEntity( entityName );
		}
	}

	void NetworkServerProvider::OnGameLevelChanged( const IEvent* event )
	{
		LevelChangedEventData* eventData = static_cast< LevelChangedEventData* >( event->GetEventData( ) );

		BitStream stream;
		stream.Write( RakString( m_configuration->Find( ConfigSections::Network, ConfigItems::Network::ServerName ).As< std::string >( ) ) );
		stream.Write( m_configuration->Find( ConfigSections::Network, ConfigItems::Network::MaxPlayers ).As< int >( ) );
		stream.Write( m_networkInterface->GetConnectionCount( ) );
		stream.Write( RakString( eventData->GetLevelName( ) ) );

		m_networkInterface->SetOfflinePingInformation( &stream );
	}

	void NetworkServerProvider::Update( float deltaMilliseconds )
	{
		m_endpoint->Update( deltaMilliseconds );
	}

	void NetworkServerProvider::Destroy( )
	{
	}
}