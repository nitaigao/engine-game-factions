#include <gtest/gtest.h>
using namespace testing;

#include "ScriptComponentFactory.h"
using namespace Script;

#include "Mocks/MockLuaState.hpp"
#include "Mocks/MockEventManager.hpp"

using namespace luabind::adl;

class ScriptComponentFactory_Tests : public TestHarness< ScriptComponentFactory >
{

protected:

	MockLuaState* m_masterState;
	MockEventManager* m_eventManager;

	void EstablishContext( )
	{
		m_masterState = new MockLuaState( );
		m_eventManager = new MockEventManager( );
	}


	void DestroyContext( )
	{
		delete m_masterState;
		delete m_eventManager;
	}

	ScriptComponentFactory* CreateSubject( )
	{
		return new ScriptComponentFactory( m_masterState, m_eventManager ); 
	}
};

TEST_F( ScriptComponentFactory_Tests, should_create_component )
{
	MockLuaState childState;
	EXPECT_CALL( *m_masterState, CreateChild(  ) ).WillOnce( Return( &childState ) );

	IScriptComponent* actual = m_subject->CreateComponent( "name", "type" );
	IScriptComponent* expected = 0;

	EXPECT_NE( expected, actual );

	delete actual;
}


/* TODO	INject a Mock LUA state, have the component factory use that as a master state which also gets stored in the scene.
		Finish off the ScriptScene::CreateComponent method to use the factory and store the component in the global variable
		( this should possibly be action'd inside the factory or maybe some clever template method on the LuaState object to allow any
		kind of registeration. ) */