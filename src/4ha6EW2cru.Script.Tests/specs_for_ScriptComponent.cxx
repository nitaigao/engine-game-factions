#include <gtest/gtest.h>
using namespace testing;

#include "ScriptComponent.h"
using namespace Script;

#include "Mocks/MockLuaState.hpp"
#include "Mocks/MockScriptFacadeManager.hpp"
#include "Mocks/MockEventManager.hpp"
#include "Mocks/MockScriptMessageDispatcher.hpp"
#include "Mocks/MockScriptEventDispatcher.hpp"
#include "Mocks/MockScriptFunctionHandler.hpp"
#include "Mocks/MockScriptUpdateDispatcher.hpp"

#include "Events/IEventListener.hpp"
#include "Events/Event.h"
#include "Events/EventData.hpp"
using namespace Events;

namespace given_a_script_is_running
{
	class ScriptComponent_BaseContext : public TestHarness< ScriptComponent >
	{

	protected:

		MockLuaState* m_state;
		
		MockScriptFacadeManager* m_scriptFacadeManager;
		MockScriptMessageDispatcher* m_messageDispatcher;
		MockScriptEventDispatcher* m_eventDispatcher;
		MockScriptUpdateDispatcher* m_updateDispatcher;

		virtual void EstablishContext( )
		{
			m_state = new MockLuaState( );
			m_scriptFacadeManager = new MockScriptFacadeManager( );
			m_messageDispatcher = new MockScriptMessageDispatcher( );
			m_eventDispatcher = new MockScriptEventDispatcher( );
			m_updateDispatcher = new MockScriptUpdateDispatcher( );
		}

		virtual void DestroyContext( )
		{

		}

		ScriptComponent* CreateSubject( )
		{
			return new ScriptComponent( m_state, m_scriptFacadeManager, m_messageDispatcher, m_eventDispatcher, m_updateDispatcher );
		}
	};
	
	class when_the_script_registers_an_event_handler : public ScriptComponent_BaseContext
	{

		std::string m_eventType;
	
	protected:

		void EstablishContext( )
		{
			ScriptComponent_BaseContext::EstablishContext( );

			m_eventType = "TestEvent";
		}
	
		void Expecting( )
		{
			EXPECT_CALL( *m_eventDispatcher, RegisterEventHandler( m_eventType, A< IScriptFunctionHandler* >( ) ) )
				.WillOnce( Invoke( MockScriptEventDispatcher::ConsumeFunctionHandler ) );
		}
	
		void When( )
		{
			m_subject->RegisterEventHandler( m_eventType, luabind::object( ) );
		}
		
	};

	TEST_F( when_the_script_registers_an_event_handler, then_the_request_should_be_forwareded_to_the_dispatcher ) { };

	class when_a_script_registers_an_update_handler : public ScriptComponent_BaseContext
	{

		float m_delta;
	
	protected:

		void EstablishContext()
		{
			ScriptComponent_BaseContext::EstablishContext( );

			m_delta = 10;
		}

		void Expecting( )
		{
			EXPECT_CALL( *m_updateDispatcher, RegisterUpdateHandler( An< IScriptFunctionHandler* >( ) ) )
				.WillOnce( Invoke( MockScriptUpdateDispatcher::ConsumeFunctionHandler ) );

			EXPECT_CALL( *m_updateDispatcher, Update( m_delta ) );
		}
	
		void When( )
		{
			m_subject->RegisterUpdateHandler( luabind::object( ) );
			m_subject->Update( m_delta );
		}
		
	};

	TEST_F( when_a_script_registers_an_update_handler, then_it_should_receive_updates ) { }


	class when_a_script_unregisters_an_update_handler : public ScriptComponent_BaseContext
	{

		float m_delta;

	protected:

		void EstablishContext()
		{
			ScriptComponent_BaseContext::EstablishContext( );

			m_delta = 10;
		}

		void Expecting( )
		{
			EXPECT_CALL( *m_updateDispatcher, UnRegisterUpdateHandler( An< IScriptFunctionHandler* >( ) ) )
				.WillOnce( Invoke( MockScriptUpdateDispatcher::ConsumeFunctionHandler ) );
		}

		void When( )
		{
			m_subject->UnRegisterUpdateHandler( luabind::object( ) );
		}

	};

	TEST_F( when_a_script_unregisters_an_update_handler, then_it_should_not_receive_updates ) { }
};