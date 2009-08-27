#include <gtest/gtest.h>
using namespace testing;

#include "ScriptComponent.h"
using namespace Script;

#include "Mocks/MockEventManager.hpp"

class ScriptComponent_Tests : public TestHarness< ScriptComponent >
{

protected:

	MockEventManager* m_eventManager;

	void EstablishContext( )
	{
		m_eventManager = new MockEventManager( );
	}

	void DestroyContext( )
	{
		delete m_eventManager;
	}

	ScriptComponent* CreateSubject( )
	{
		return new ScriptComponent( 0, m_eventManager );
	}
};

TEST( ScriptComponent_Tests, should_broadcast_event )
{
	
}