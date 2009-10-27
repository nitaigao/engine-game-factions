#include <gtest/gtest.h>
using namespace testing;

#include "NetworkClientEndpoint.h"
using namespace Network;

#include "Mocks/MockNetworkInterface.hpp"
#include "Mocks/MockServerCache.hpp"
#include "Mocks/MockServiceManager.hpp"
#include "Mocks/MockService.h"
#include "Mocks/MockNetworkSystemScene.hpp"

#include "Events/EventManager.h"
using namespace Events;

namespace given_the_client_is_looking_for_servers
{
	class NetworkClientEndpoint_BaseContext : public TestHarness< NetworkClientEndpoint >
	{

	protected:

		MockNetworkInterface* m_networkInterface;
		MockServerCache* m_serverCache;
		EventManager* m_eventManager;
		MockServiceManager* m_serviceManager;
		MockNetworkSystemScene* m_scene;

		void EstablishContext( )
		{
			m_networkInterface = new MockNetworkInterface( );
			m_scene = new MockNetworkSystemScene( );
			m_serverCache = new MockServerCache( );
			m_eventManager = new EventManager( );
			m_serviceManager = new MockServiceManager( );
		}

		void DestroyContext( )
		{
			delete m_networkInterface;
			delete m_scene;
			delete m_serverCache;
			delete m_eventManager;
			delete m_serviceManager;
		}

		NetworkClientEndpoint* CreateSubject( )
		{
			return new NetworkClientEndpoint( m_networkInterface, m_scene, m_serverCache, m_eventManager, m_serviceManager );
		}
	};

	class when_a_server_advertises : public NetworkClientEndpoint_BaseContext
	{

	protected:

		void EstablishContext( )
		{
			NetworkClientEndpoint_BaseContext::EstablishContext( );
		}
	};

	TEST_F( when_a_server_advertises, then_the_client_should_inform_the_game_of_the_advertisement )
	{
		
	}
};