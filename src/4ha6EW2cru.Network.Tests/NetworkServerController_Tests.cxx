#include <gtest/gtest.h>
using namespace testing;

#include <gtest/gtest.h>
using namespace testing;

#include "NetworkServerController.h"
using namespace Network;

#include "Mocks/MockServiceManager.hpp"
#include "Mocks/MockNetworkInterface.hpp"
#include "Mocks/MockService.h"

class NetworkServerController_Tests : public TestHarness< NetworkServerController >
{

protected:

	MockNetworkInterface* m_networkInterface;
	MockServiceManager* m_serviceManager;

	void EstablishContext( )
	{
		m_networkInterface = new MockNetworkInterface( );
		m_serviceManager = new MockServiceManager( );
	}


	void DestroyContext( )
	{
		delete m_networkInterface;
		delete m_serviceManager;
	}

	NetworkServerController* CreateSubject( )
	{
		return new NetworkServerController( m_networkInterface, m_serviceManager );
	}
};

TEST_F( NetworkServerController_Tests, should_destroy_entity_on_client_disconnection )
{
	MockService service;

	EXPECT_CALL( *m_serviceManager, FindService( System::Types::ENTITY ) )
		.WillOnce( Return( &service ) );

	EXPECT_CALL( service, ProcessMessage( System::Messages::Entity::DestroyEntity, An< AnyType::AnyTypeMap >( ) ) )
		.WillOnce( Return( AnyType::AnyTypeMap( ) ) );

	m_subject->ClientDisconnected( SystemAddress( "127.0.0.1", 3242 ) );
}

