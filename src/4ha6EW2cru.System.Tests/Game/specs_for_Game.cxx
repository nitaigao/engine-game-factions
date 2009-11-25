#include <gtest/gtest.h>
using namespace testing;

#include "Game/Game.h"
using namespace Game;

#include "../Mocks/MockPlatformManager.hpp"
#include "../Mocks/MockProgramOptions.hpp"
#include "../Mocks/MockSystemManager.hpp"
#include "../Mocks/MockEventManager.hpp"
#include "../Mocks/MockServiceManager.hpp"
#include "../Mocks/MockWorld.hpp"

#include "Events/EventType.hpp"
#include "Events/EventData.hpp"
using namespace Events;

#include "Configuration/Configuration.h"
using namespace Configuration;

#include "System/AnyType.hpp"

namespace base_context
{
	class Game_BaseContext : public TestHarness< GameRoot >
	{

	protected:

		MockPlatformManager* m_platformManager;
		MockProgramOptions* m_programOptions;
		MockSystemManager* m_systemManager;
		MockEventManager* m_eventManager;
		MockServiceManager* m_serviceManager;
		MockWorld* m_world;

		ClientConfiguration* m_configuration;

		virtual void EstablishContext( )
		{
			m_programOptions = new MockProgramOptions( );
			m_platformManager = new MockPlatformManager( );
			m_systemManager = new MockSystemManager( );
			m_configuration = new ClientConfiguration( );
			m_eventManager = new MockEventManager( );
			m_serviceManager = new MockServiceManager( );
			m_world = new MockWorld( );
		}

		virtual void DestroyContext( )
		{
			delete m_programOptions;
			delete m_platformManager;
			delete m_systemManager;
			delete m_eventManager;
			delete m_configuration;
			delete m_serviceManager;
		}

		GameRoot* CreateSubject( )
		{
			return new GameRoot( m_programOptions, m_configuration, m_platformManager, m_systemManager, m_eventManager, m_serviceManager ); 
		}
	};
};

namespace given_the_game_is_a_dedicated_server
{
	class when_the_game_is_initializing : public base_context::Game_BaseContext
	{
	
	protected:
	
		void Expecting( )
		{
			EXPECT_CALL( *m_programOptions, HasOption( System::Options::DedicatedServer ) ).WillOnce( Return( true ) );
			EXPECT_CALL( *m_programOptions, HasOption( System::Options::LevelName ) ).WillOnce( Return( false ) );

			EXPECT_CALL( *m_systemManager, LoadSystems( true ) );
			EXPECT_CALL( *m_systemManager, InitializeAllSystems( ) );

			EXPECT_CALL( *m_platformManager, CreateConsoleWindow( ) );

			EXPECT_CALL( *m_eventManager, AddEventListener( EventTypes::GAME_QUIT, An< IEventListener* >( ) ) ).WillOnce( Invoke( &MockEventManager::ConsumeEventListener ) );
			EXPECT_CALL( *m_eventManager, AddEventListener( EventTypes::GAME_LEVEL_CHANGED, An< IEventListener* >( ) ) ).WillOnce( Invoke( &MockEventManager::ConsumeEventListener ) );
			EXPECT_CALL( *m_eventManager, AddEventListener( EventTypes::GAME_ENDED, An< IEventListener* >( ) ) ).WillOnce( Invoke( &MockEventManager::ConsumeEventListener ) );


			EXPECT_CALL( *m_eventManager, RemoveEventListener( EventTypes::GAME_QUIT, An< IEventListener* >( ) ) ).WillOnce( Invoke( &MockEventManager::ConsumeEventListener ) );
			EXPECT_CALL( *m_eventManager, RemoveEventListener( EventTypes::GAME_LEVEL_CHANGED, An< IEventListener* >( ) ) ).WillOnce( Invoke( &MockEventManager::ConsumeEventListener ) );
			EXPECT_CALL( *m_eventManager, RemoveEventListener( EventTypes::GAME_ENDED, An< IEventListener* >( ) ) ).WillOnce( Invoke( &MockEventManager::ConsumeEventListener ) );

			EXPECT_CALL( *m_serviceManager, MessageAll( System::Messages::PostInitialize, An< AnyType::AnyTypeMap >( ) ) ).WillOnce( Return( AnyType::AnyTypeMap( ) ) );

			EXPECT_CALL( *m_systemManager, CreateWorld( ) ).WillOnce( Return( m_world ) );
			EXPECT_CALL( *m_world, Initialize( ) );
		}
	
		void When( )
		{
			m_subject->Initialize( );
			m_subject->Release( );
		}

	};

	TEST_F( when_the_game_is_initializing, then_a_console_window_should_spawn ) { }
}

namespace given_a_level_has_been_passed_on_the_command_line
{
	class when_the_game_is_initializing_and_is_a_dedicated_server : public base_context::Game_BaseContext
	{
	
	protected:
	
		void Expecting( )
		{
			std::string levelName = "levelName";

			bool isDedicated = true;

			EXPECT_CALL( *m_programOptions, HasOption( System::Options::DedicatedServer ) ).WillOnce( Return( isDedicated ) );
			EXPECT_CALL( *m_programOptions, HasOption( System::Options::LevelName ) ).WillOnce( Return( true ) );
			EXPECT_CALL( *m_programOptions, GetOption( System::Options::LevelName ) ).WillOnce( Return( levelName ) );

			EXPECT_CALL( *m_systemManager, LoadSystems( isDedicated ) );
			EXPECT_CALL( *m_systemManager, InitializeAllSystems( ) );

			EXPECT_CALL( *m_platformManager, CreateConsoleWindow( ) );

			EXPECT_CALL( *m_eventManager, AddEventListener( EventTypes::GAME_QUIT, An< IEventListener* >( ) ) ).WillOnce( Invoke( &MockEventManager::ConsumeEventListener ) );
			EXPECT_CALL( *m_eventManager, AddEventListener( EventTypes::GAME_LEVEL_CHANGED, An< IEventListener* >( ) ) ).WillOnce( Invoke( &MockEventManager::ConsumeEventListener ) );
			EXPECT_CALL( *m_eventManager, AddEventListener( EventTypes::GAME_ENDED, An< IEventListener* >( ) ) ).WillOnce( Invoke( &MockEventManager::ConsumeEventListener ) );


			EXPECT_CALL( *m_eventManager, RemoveEventListener( EventTypes::GAME_QUIT, An< IEventListener* >( ) ) ).WillOnce( Invoke( &MockEventManager::ConsumeEventListener ) );
			EXPECT_CALL( *m_eventManager, RemoveEventListener( EventTypes::GAME_LEVEL_CHANGED, An< IEventListener* >( ) ) ).WillOnce( Invoke( &MockEventManager::ConsumeEventListener ) );
			EXPECT_CALL( *m_eventManager, RemoveEventListener( EventTypes::GAME_ENDED, An< IEventListener* >( ) ) ).WillOnce( Invoke( &MockEventManager::ConsumeEventListener ) );

			EXPECT_CALL( *m_eventManager, QueueEvent( EventTypes::GAME_LEVEL_CHANGED, An< IEventData* >( ) ) ).WillOnce( Invoke( &MockEventManager::ConsumeEventData ) );

			EXPECT_CALL( *m_serviceManager, MessageAll( System::Messages::PostInitialize, An< AnyType::AnyTypeMap >( ) ) ).WillOnce( Return( AnyType::AnyTypeMap( ) ) );

			EXPECT_CALL( *m_systemManager, CreateWorld( ) ).WillOnce( Return( m_world ) );
			EXPECT_CALL( *m_world, Initialize( ) );
		}
	
		void When( )
		{
			m_subject->Initialize( );
			m_subject->Release( );
		}
		
	};

	TEST_F( when_the_game_is_initializing_and_is_a_dedicated_server, then_the_game_should_automatically_load_the_level ) { }
}


namespace given_in_general
{
	class when_the_game_is_initialized : public base_context::Game_BaseContext
	{
	
	protected:
	
		void Expecting( )
		{
			EXPECT_CALL( *m_eventManager, AddEventListener( EventTypes::GAME_QUIT, An< IEventListener* >( ) ) ).WillOnce( Invoke( &MockEventManager::ConsumeEventListener ) );
			EXPECT_CALL( *m_eventManager, AddEventListener( EventTypes::GAME_LEVEL_CHANGED, An< IEventListener* >( ) ) ).WillOnce( Invoke( &MockEventManager::ConsumeEventListener ) );
			EXPECT_CALL( *m_eventManager, AddEventListener( EventTypes::GAME_ENDED, An< IEventListener* >( ) ) ).WillOnce( Invoke( &MockEventManager::ConsumeEventListener ) );


			EXPECT_CALL( *m_eventManager, RemoveEventListener( EventTypes::GAME_QUIT, An< IEventListener* >( ) ) ).WillOnce( Invoke( &MockEventManager::ConsumeEventListener ) );
			EXPECT_CALL( *m_eventManager, RemoveEventListener( EventTypes::GAME_LEVEL_CHANGED, An< IEventListener* >( ) ) ).WillOnce( Invoke( &MockEventManager::ConsumeEventListener ) );
			EXPECT_CALL( *m_eventManager, RemoveEventListener( EventTypes::GAME_ENDED, An< IEventListener* >( ) ) ).WillOnce( Invoke( &MockEventManager::ConsumeEventListener ) );

			EXPECT_CALL( *m_serviceManager, MessageAll( System::Messages::PostInitialize, An< AnyType::AnyTypeMap >( ) ) ).WillOnce( Return( AnyType::AnyTypeMap( ) ) );

			EXPECT_CALL( *m_systemManager, CreateWorld( ) ).WillOnce( Return( m_world ) );
			EXPECT_CALL( *m_world, Initialize( ) );
		
		}
	
		void When( )
		{
			m_subject->Initialize( );
			m_subject->Release( );
		}
		
	};

	TEST_F( when_the_game_is_initialized, then_the_game_should_register_for_the_relevent_in_game_events_and_release_them ) { }

	TEST_F( when_the_game_is_initialized, then_the_game_should_instruct_all_services_to_initialize ) { }
}