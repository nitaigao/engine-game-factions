#include "NetworkClientProvider.h"

#include "NetworkInterface.h"
#include "NetworkClientEndpoint.h"
#include "NetworkClientController.h"

namespace Network
{
	NetworkClientProvider::NetworkClientProvider( Configuration::IConfiguration* configuration )
		: m_configuration( configuration )
		, m_networkInterface( new NetworkInterface( ) )
		, m_controller( new NetworkClientController( m_networkInterface ) )
		, m_endpoint( new NetworkClientEndpoint( m_networkInterface ) )
	{

	}

	NetworkClientProvider::~NetworkClientProvider( )
	{
		delete m_endpoint;
		delete m_controller;
		delete m_networkInterface;
	}

	void NetworkClientProvider::Connect( const std::string& serverAddress, unsigned int port )
	{
		m_networkInterface->Connect( serverAddress, port );
	}

	void NetworkClientProvider::Disconnect()
	{
		m_networkInterface->Disconnect( );
	}

	void NetworkClientProvider::Initialize( unsigned int port, int maxConnections )
	{
		m_networkInterface->Initialize( port, maxConnections );
		m_controller->Initialize( );
		m_endpoint->Initialize( );
	}

	void NetworkClientProvider::Update( float deltaMilliseconds )
	{
		m_endpoint->Update( deltaMilliseconds );
	}

	void NetworkClientProvider::Destroy()
	{

	}

	void NetworkClientProvider::SelectCharacter( const std::string& characterName )
	{
		m_controller->SelectCharacter( characterName );
	}
}