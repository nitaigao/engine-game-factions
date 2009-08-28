#include <gtest/gtest.h>
using namespace testing;

#include "ScriptComponent.h"
using namespace Script;

#include "Mocks/MockEventManager.hpp"
#include "Mocks/MockLuaState.hpp"
#include "Mocks/MockScriptFacadeManager.hpp"

#include "Events/IEventListener.hpp"

using namespace Events;

class ScriptComponent_Tests : public TestHarness< ScriptComponent >
{

protected:

	MockLuaState* m_state;
	MockEventManager* m_eventManager;
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

	ScriptComponent* CreateSubject( )
	{
		return new ScriptComponent( m_state, m_eventManager, m_facadeManager );
	}
};

TEST_F( ScriptComponent_Tests, should_initialize )
{
	std::string scriptpath = "script/path";

	m_subject->SetAttribute( System::Parameters::ScriptPath, scriptpath );

	EXPECT_CALL( *m_eventManager, AddEventListener( An< IEventListener* >( ) ) )
		.WillOnce( Invoke( MockEventManager::ConsumeEventListener ) );

	EXPECT_CALL( *m_state, LoadScript( scriptpath ) );

	EXPECT_CALL( *m_facadeManager, Initialize( m_subject ) );

	m_subject->Initialize( );
}

TEST_F( ScriptComponent_Tests, should_destroy )
{
	EXPECT_CALL( *m_eventManager, RemoveEventListener( An< IEventListener* >( ) ) )
		.WillOnce( Invoke( MockEventManager::ConsumeEventListener ) );

	EXPECT_CALL( *m_facadeManager, Destroy( ) );

	m_subject->Destroy( );
}

TEST_F( ScriptComponent_Tests, should_run_script )
{
	EXPECT_CALL( *m_state, Execute( ) );
	m_subject->RunScript( );
}

TEST_F( ScriptComponent_Tests, should_include_script )
{
	std::string scriptPath = "/path/to/script";

	EXPECT_CALL( *m_state, LoadScript( scriptPath ) );
	EXPECT_CALL( *m_state, ReParse( ) );

	m_subject->IncludeScript( scriptPath );
}

TEST_F( ScriptComponent_Tests, should_execute_a_string )
{
	std::string scriptString = "print( 'hello world!' )";

	EXPECT_CALL( *m_state, ExecuteString( scriptString ) );

	m_subject->ExecuteString( scriptString );
}