#include "NetworkClientProvider.h"

#include "NetworkInterface.h"
#include "NetworkClientEndpoint.h"

namespace Network
{
	NetworkClientProvider::NetworkClientProvider( Configuration::IConfiguration* configuration )
		: m_configuration( configuration )
		, m_networkInterface( new NetworkInterface( ) )
		, m_endpoint( new NetworkClientEndpoint( m_networkInterface ) )
	{

	}

	NetworkClientProvider::~NetworkClientProvider( )
	{
		delete m_networkInterface;
		delete m_endpoint;
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
		m_endpoint->Initialize( );
	}

	GAMEAPI void NetworkClientProvider::Update( float deltaMilliseconds )
	{
		m_endpoint->Update( deltaMilliseconds );
	}

	GAMEAPI void NetworkClientProvider::Destroy()
	{

	}
}