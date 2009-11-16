#include <gtest/gtest.h>
using namespace testing;

#include "NetworkClientEndpoint.h"
using namespace Network;

#include "Mocks/MockNetworkInterface.hpp"
#include "Mocks/MockServerCache.hpp"
#include "Mocks/MockServiceManager.hpp"
#include "Mocks/MockService.h"
#include "Mocks/MockNetworkSystemScene.hpp"
#include "Mocks/MockEventManager.hpp"

#include "Events/EventManager.h"
using namespace Events;

#include "MessageIdentifiers.h"
using namespace RakNet;

namespace given_the_client_is_looking_for_servers
{
	class NetworkClientEndpoint_BaseContext : public TestHarness< NetworkClientEndpoint >
	{

	protected:

		MockNetworkInterface* m_networkInterface;
		MockServerCache* m_serverCache;
		MockEventManager* m_eventManager;
		MockServiceManager* m_serviceManager;
		MockNetworkSystemScene* m_scene;

		virtual void EstablishContext( )
		{
			m_networkInterface = new MockNetworkInterface( );
			m_scene = new MockNetworkSystemScene( );
			m_serverCache = new MockServerCache( );
			m_eventManager = new MockEventManager( );
			m_serviceManager = new MockServiceManager( );
		}

		virtual void DestroyContext( )
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

	void DestroyPacket( Packet* packet )
	{
		delete[ ] packet->data;
		delete packet;
	}

	class when_a_server_advertises : public NetworkClientEndpoint_BaseContext
	{
		Packet* m_packet;

	protected:

		void Expecting( )
		{
			EXPECT_CALL( *m_eventManager, QueueEvent( An< const IEvent* >( ) ) );

			EXPECT_CALL( *m_networkInterface, Receive( ) )
				.WillOnce( Return( m_packet ) );

			EXPECT_CALL( *m_networkInterface, DeAllocatePacket( m_packet ) )
				.WillOnce( Invoke( &DestroyPacket ) );
		}

		void EstablishContext( )
		{
			NetworkClientEndpoint_BaseContext::EstablishContext( );

			m_packet = new Packet( );
			m_packet->data = new unsigned char[ 1 ];
			m_packet->data[ 0 ] = ID_PONG;
		}

		void When( )
		{
			m_subject->Update( 0 );
		}
	};

	TEST_F( when_a_server_advertises, then_the_client_should_inform_the_game_of_the_advertisement )	{ }
};