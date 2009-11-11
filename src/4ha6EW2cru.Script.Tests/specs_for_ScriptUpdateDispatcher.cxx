#include <gtest/gtest.h>
using namespace testing;

#include "ScriptUpdateDispatcher.h"
using namespace Script;

#include "Mocks/MockScriptFunctionHandler.hpp"

namespace given_a_script_is_running
{
	class ScriptUpdateDispatcher_BaseContext : public TestHarness< ScriptUpdateDispatcher >
	{

	protected:

		virtual void EstablishContext( )
		{
	
		}

		virtual void DestroyContext( )
		{
			
		}

		ScriptUpdateDispatcher* CreateSubject( )
		{
			return new ScriptUpdateDispatcher(  ); 
		}
	};
	
	class when_it_registers_for_updates : public ScriptUpdateDispatcher_BaseContext
	{

		MockScriptFunctionHandler* m_handler;
		float m_delta;
	
	protected:

		void EstablishContext( )
		{
			ScriptUpdateDispatcher_BaseContext::EstablishContext( );

			m_delta = 10;
			m_handler = new MockScriptFunctionHandler( );
		}
	
		void Expecting( )
		{
			EXPECT_CALL( *m_handler, CallFunction( m_delta ) );
		}
	
		void When( )
		{
			m_subject->RegisterUpdateHandler( m_handler );
			m_subject->Update( m_delta );
			m_subject->Destroy( );
		}
		
	};

	TEST_F( when_it_registers_for_updates, then_it_should_receive_updates_on_each_game_loop ) { }

	class when_it_unregisters_for_updates : public ScriptUpdateDispatcher_BaseContext
	{

		MockScriptFunctionHandler* m_add_handler;
		MockScriptFunctionHandler* m_remove_handler;

		float m_delta;

	protected:

		void EstablishContext( )
		{
			ScriptUpdateDispatcher_BaseContext::EstablishContext( );

			m_delta = 10;

			m_add_handler = new MockScriptFunctionHandler( );
			m_remove_handler = new MockScriptFunctionHandler( );
		}

		void Expecting( )
		{
			EXPECT_CALL( *m_add_handler, CallFunction( m_delta ) ).Times( 0 );
			EXPECT_CALL( *m_add_handler, Compare( m_remove_handler ) )
				.WillOnce( Return( true ) );
			EXPECT_CALL( *m_add_handler, IsMarkedForDeletion( ) ).WillOnce( Return( true ) );
		}

		void When( )
		{
			m_subject->RegisterUpdateHandler( m_add_handler );
			m_subject->UnRegisterUpdateHandler( m_remove_handler );

			m_subject->Update( m_delta );
			m_subject->Destroy( );
		}

	};

	TEST_F( when_it_unregisters_for_updates, then_it_should_not_receive_updates_on_each_game_loop ) { }
};