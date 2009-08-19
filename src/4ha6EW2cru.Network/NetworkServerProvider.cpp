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
	NetworkServerProvider::NetworkServerProvider( IConfiguration* configuration )
		: m_configuration( configuration )
		, m_networkInterface( new NetworkInterface( ) )
		, m_controller( new NetworkServerController( m_networkInterface ) )
		, m_endpoint( new NetworkServerEndpoint( m_networkInterface, m_controller ) )
	{

	}

	NetworkServerProvider::~NetworkServerProvider( )
	{
		if ( m_endpoint != 0 )
		{
			delete m_endpoint;
		}

		if ( m_controller != 0 )
		{
			delete m_controller;
		}

		if ( m_networkInterface != 0 )
		{
			delete m_networkInterface;
		}
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
	}

	void NetworkServerProvider::Message( const std::string& entityName, const System::Message& message, AnyType::AnyTypeMap parameters )
	{
		if ( message == System::Messages::SetPosition )
		{
			m_controller->SetPosition( entityName, parameters[ System::Attributes::Position ].As< MathVector3 >( ) );
		}

		if ( message == System::Messages::SetOrientation )
		{
			//m_attributes[ System::Attributes::Orientation ] = parameters[ System::Attributes::Orientation ].As< MathQuaternion >( );
		}

		if ( message == System::Messages::Mouse_Moved )
		{
			//m_attributes[ System::Parameters::DeltaX ] = parameters[ System::Parameters::DeltaX ].As< float >( );
		}
	}

	void NetworkServerProvider::OnGameLevelChanged( IEvent* event )
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