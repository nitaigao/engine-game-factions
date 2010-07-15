#include "precompiled.h"

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

#include <BitStream.h>
using namespace RakNet;

namespace Network
{
  NetworkServerProvider::~NetworkServerProvider( )
  {
    delete m_endpoint;
    delete m_controller;
    delete m_networkInterface;
  }

  void NetworkServerProvider::Initialize( int maxConnections )
  {
    m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::MaxServerConnections, 10 );
    m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::ServerSleepTime, 30 );
    m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::MaxServerReleaseTime, 10 );
    m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::ServerName, "Factions Server" );
    m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::MaxPlayers, 10 );
    m_configuration->SetDefault( ConfigSections::Network, ConfigItems::Network::ServerSnapshotRate, 33 );

    int serverPort = m_configuration->Find( ConfigSections::Network, ConfigItems::Network::ServerPort ).As< int >( );
    m_networkInterface->Initialize( serverPort, maxConnections );
    m_controller->Initialize( );
    m_endpoint->Initialize( );
  }

  void NetworkServerProvider::Message( ISystemComponent* subject, const System::MessageType& message, AnyType::AnyTypeMap parameters )
  {
    if ( message == System::Messages::Entity::CreateEntity )
    {
      m_controller->CreateEntity( subject->GetName( ), parameters[ System::Attributes::EntityType ].As< std::string >( ) );
    }

    if ( message == System::Messages::Entity::DestroyEntity )
    {
      m_controller->DestroyEntity( subject->GetName( ) );
    }

    if ( message == System::Messages::Network::Server::SetServerPosition )
    {
      m_controller->MessageEntity( subject->GetName( ), System::Messages::SetPosition, parameters );
    }

    if ( message == System::Messages::Network::Server::SetServerOrientation )
    {
      m_controller->MessageEntity( subject->GetName( ), System::Messages::SetOrientation, parameters );
    }

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
      m_controller->MessageEntity( subject->GetName( ), message, parameters );
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
}