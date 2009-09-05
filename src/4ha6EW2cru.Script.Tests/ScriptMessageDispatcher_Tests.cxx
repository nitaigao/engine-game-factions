#include <gtest/gtest.h>
using namespace testing;

#include "ScriptMessageDispatcher.h"
using namespace Script;

#include "Mocks/MockScriptFunctionHandler.hpp"

class ScriptMessageDispatcher_Tests : public TestHarness< ScriptMessageDispatcher >
{

protected:

	void EstablishContext( )
	{

	}


	void DestroyContext( )
	{

	}

	ScriptMessageDispatcher* CreateSubject( )
	{
		return new ScriptMessageDispatcher(  ); 
	}
};

TEST_F( ScriptMessageDispatcher_Tests, should_add_a_message_handler )
{
	luabind::object delegateFunction;
	System::MessageType message = System::Messages::SetPosition;

	m_subject->AddMessageHandler( message, delegateFunction );

	EXPECT_TRUE( m_subject->HasHandler( message, delegateFunction ) );
}

TEST_F( ScriptMessageDispatcher_Tests, should_remove_message_handler )
{
	luabind::object delegateFunction;
	System::MessageType message = System::Messages::SetPosition;

	m_subject->AddMessageHandler( message, delegateFunction );

	EXPECT_TRUE( m_subject->HasHandler( message, delegateFunction ) );

	m_subject->RemoveHandler( message, delegateFunction );

	EXPECT_TRUE( m_subject->HasHandler( message, delegateFunction ) );

	m_subject->Update( 10.0f );

	EXPECT_FALSE( m_subject->HasHandler( message, delegateFunction ) );
}

TEST_F( ScriptMessageDispatcher_Tests, should_dispatch_messages )
{
	System::MessageType message = System::Messages::SetPosition;
	AnyType::AnyTypeMap parameters;

	m_subject->DisptchMessage( message, parameters );
}