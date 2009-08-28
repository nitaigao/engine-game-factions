#include <gtest/gtest.h>
using namespace testing;

#include "ScriptFacadeFactory.h"
using namespace Script;

#include "Mocks/MockLuaState.hpp"
#include "Mocks/MockScriptComponent.hpp"

class ScriptFacadeFactory_Tests : public TestHarness< ScriptFacadeFactory >
{

protected:

	MockLuaState* m_state;

	void EstablishContext( )
	{
		m_state = new MockLuaState( );
	}

	void DestroyContext( )
	{
		delete m_state;
	}

	ScriptFacadeFactory* CreateSubject( )
	{
		return new ScriptFacadeFactory( m_state ); 
	}
};

TEST_F( ScriptFacadeFactory_Tests, should_create_component )
{
	MockScriptComponent component;

	IScriptFacade* facade = m_subject->CreateScriptFacade( IScriptFacade::ANIMATION, &component );
	delete facade;
}