#include <gtest/gtest.h>
using namespace testing;

/*#include "ScriptComponent.h"
using namespace Script;

#include "Events/EventManager.h"
using namespace Events;

class ScriptComponent_Tests : public TestHarness< ScriptComponent >
{

protected:

	EventManager* m_eventManager;

	void EstablishContext( )
	{
		m_eventManager = new EventManager( );
	}

	void DestroyContext( )
	{
		delete m_eventManager;
	}

	ScriptComponent* CreateSubject( )
	{
		return new ScriptComponent( 0 );
	}
};*/

TEST( ScriptComponent_Tests, should_broadcast_event )
{
	
}