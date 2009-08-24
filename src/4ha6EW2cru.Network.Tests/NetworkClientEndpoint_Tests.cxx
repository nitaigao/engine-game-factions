#include <gtest/gtest.h>
using namespace testing;

#include "NetworkClientEndpoint.h"
using namespace Network;

#include <PluginInterface2.h>
#include <MessageIdentifiers.h>
#include <GetTIme.h>
using namespace RakNet;

#include "Mocks/MockNetworkInterface.hpp"
#include "Mocks/MockServerCache.hpp"
#include "Mocks/MockServiceManager.hpp"
#include "Mocks/MockService.h"
#include "Mocks/MockNetworkSystemScene.hpp"

#include "Events/EventManager.h"
using namespace Events;

#include "Maths/MathVector3.hpp"
using namespace Maths;

class NetworkClientEndpoint_Tests : public TestHarness< NetworkClientEndpoint >
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

TEST_F( NetworkClientEndpoint_Tests, should_receive_offline_pong_messages )
{
	std::string serverName = "serverName";
	int players = 10;
	int maxPlayers = 32;
	std::string mapName = "mapName";
	std::string serverAddress = "127.0.0.1";
	unsigned int port = 8989;

	BitStream stream;
	stream.Write( ( MessageID ) ID_PONG );
	stream.Write( GetTime( ) );
	stream.Write( RakString( serverName ) );
	stream.Write( players );
	stream.Write( maxPlayers );
	stream.Write( RakString( mapName ) );

	Packet* p = new Packet( );
	p->systemAddress = SystemAddress( serverAddress.c_str( ), port );
	p->data = stream.GetData( );
	p->length = stream.GetNumberOfBytesUsed( );

	EXPECT_CALL( *m_networkInterface, Receive( ) )
		.WillOnce( Return( p ) );

	EXPECT_CALL( *m_serverCache, Add( serverName, mapName, players, maxPlayers, An< int >( ), serverAddress, port ) );
	EXPECT_CALL( *m_networkInterface, DeAllocatePacket( p ) );

	m_subject->Update( 99 );

	m_serverCache->Clear( );

	delete p;
}

TEST_F( NetworkClientEndpoint_Tests, should_destroy_an_entity_if_not_passive )
{
	MockService mockService;

	EXPECT_CALL( *m_serviceManager, FindService( System::Types::ENTITY ) )
		.WillOnce( Return( &mockService ) );

	std::string entityName = "test";
	
	EXPECT_CALL( mockService, ProcessMessage( System::Messages::Entity::DestroyEntity, An< AnyType::AnyTypeMap >( ) ) )
		.WillOnce( Return( AnyType::AnyTypeMap( ) ) );

	m_subject->DestroyEntity( entityName, 0 );
}

TEST_F( NetworkClientEndpoint_Tests, should_message_entity_mouse_moved_if_not_passive )
{
	std::string entityName = "test";

	AnyType::AnyTypeMap parameters;
	parameters[ System::Parameters::DeltaX ] = 0.1f;

	EXPECT_CALL( *m_scene, MessageComponent( entityName, System::Messages::Mouse_Moved, An< AnyType::AnyTypeMap >( ) ) );

	m_subject->MessageEntity( entityName, System::Messages::Mouse_Moved, parameters, 0 );
}

TEST_F( NetworkClientEndpoint_Tests, should_set_an_entity_position_if_not_passive )
{
	std::string entityName = "test";

	EXPECT_CALL( *m_scene, MessageComponent( entityName, System::Messages::SetPosition, An< AnyType::AnyTypeMap >( ) ) );

	m_subject->SetEntityPosition( entityName, MathVector3::Forward( ), 0 );
}