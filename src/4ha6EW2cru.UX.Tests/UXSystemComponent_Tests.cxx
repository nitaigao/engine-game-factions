#include <gtest/gtest.h>
using namespace testing;

#include "UXSystemComponent.h"
using namespace UX;

#include "Mocks/MockGUI.hpp"
#include "Mocks/MockLuaState.hpp"
#include "Mocks/MockEventManager.hpp"
#include "Mocks/MockScriptFacadeManager.hpp"
#include "Mocks/MockScriptFunctionHandler.hpp"

#include "Events/IEventListener.hpp"
using namespace Events;

namespace in_general
{
	class UXSystemComponent_BaseContext : public TestHarness< UXSystemComponent >
	{

	protected:

		MockEventManager* m_eventManager;
		MockLuaState* m_state;
		MockScriptFacadeManager* m_facadeManager;

		void EstablishContext( )
		{
			m_state = new MockLuaState( );
			m_eventManager = new MockEventManager( );
			m_facadeManager = new MockScriptFacadeManager( );
		}

		void DestroyContext( )
		{
			delete m_eventManager;
		}

		UXSystemComponent* CreateSubject( )
		{
			return new UXSystemComponent( m_state, m_eventManager, m_facadeManager ); 
		}
	};
	
	class when_the_script_subscribes_for_an_event : public UXSystemComponent_BaseContext
	{
	
	protected:
	
		void Expecting( )
		{
			EXPECT_CALL( *m_eventManager, AddEventListener( A< const std::string& >( ), An< IEventListener* >( ) ) )
				.WillOnce( Invoke( MockEventManager::ConsumeEventListener ) );
		}
	
		void When( )
		{
			m_subject->RegisterEventHandler( EventTypes::TEST_EVENT, new MockScriptFunctionHandler( ) );
			m_subject->Destroy( );
		}
		
	};

	TEST_F( when_the_script_subscribes_for_an_event, then_the_game_should_register_the_subscriber ) { };

	class when_the_script_unsubscribes_from_an_event : public UXSystemComponent_BaseContext
	{

		MockScriptFunctionHandler* m_originalHandler;
		MockScriptFunctionHandler* m_handlerToRemove;
		std::string m_eventType;
	
	protected:

		void EstablishContext()
		{
			UXSystemComponent_BaseContext::EstablishContext( );
			m_eventType = EventTypes::TEST_EVENT;
			m_originalHandler = new MockScriptFunctionHandler( );
			m_handlerToRemove = new MockScriptFunctionHandler( );
		}
	
		void Expecting( )
		{
			EXPECT_CALL( *m_eventManager, AddEventListener( m_eventType, An< IEventListener* >( ) ) )
				.WillOnce( Invoke( MockEventManager::ConsumeEventListener ) );

			EXPECT_CALL( *m_originalHandler, Compare( m_handlerToRemove ) )
				.WillOnce( Return( true ) );

			EXPECT_CALL( *m_eventManager, RemoveEventListener( m_eventType, An< IEventListener* >( ) ) )
				.WillOnce( Invoke( MockEventManager::ConsumeEventListener ) );
		}
	
		void When( )
		{
			m_subject->RegisterEventHandler( m_eventType, m_originalHandler );
			m_subject->UnregisterEventHandler( m_eventType, m_handlerToRemove );
		}
		
	};

	TEST_F( when_the_script_unsubscribes_from_an_event, then_the_game_should_unregister_the_subscriber ) { };
};