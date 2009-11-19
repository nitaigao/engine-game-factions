#include "NetworkClientProvider.h"

#include "NetworkInterface.h"
#include "NetworkClientEndpoint.h"
#include "NetworkClientController.h"
#include "ServerCache.h"

#include "Configuration/ConfigurationTypes.hpp"
using namespace Configuration;

namespace Network
{
	NetworkClientProvider::~NetworkClientProvider( )
	{
		delete m_endpoint;
		delete m_controller;
		delete m_networkInterface;
		delete m_configuration;
	}

	void NetworkClientProvider::Connect( const std::string& serverAddress )
	{
		int serverPort = m_configuration->Find( ConfigSections::Network, ConfigItems::Network::ServerPort ).As< int >( );
		m_networkInterface->Connect( serverPort, serverAddress );
	}

	void NetworkClientProvider::Disconnect()
	{
		m_networkInterface->Disconnect( );
	}

	void NetworkClientProvider::Initialize( int maxConnections )
	{
		m_networkInterface->Initialize( 0, maxConnections );
		m_controller->Initialize( );
		m_endpoint->Initialize( );
	}

	void NetworkClientProvider::Update( float deltaMilliseconds )
	{
		m_endpoint->Update( deltaMilliseconds );
	}

	void NetworkClientProvider::SelectCharacter( const std::string& characterName )
	{
		m_controller->SelectCharacter( characterName );
	}

	void NetworkClientProvider::FindServers( )
	{
		int serverPort = m_configuration->Find( ConfigSections::Network, ConfigItems::Network::ServerPort ).As< int >( );
		m_controller->FindServers( serverPort );
	}

	void NetworkClientProvider::Message( const std::string& entityName, const System::MessageType& message, AnyType::AnyTypeMap parameters )
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
			m_controller->MessageEntity( entityName, message, parameters );
		}
	}
}