#include <gtest/gtest.h>
using namespace testing;

#include "UXSystemComponent.h"
using namespace UX;

#include "Mocks/MockGUI.hpp"
#include "Mocks/MockLuaState.hpp"
#include "Mocks/MockEventManager.hpp"

#include "Events/IEventListener.hpp"
using namespace Events;

class UXSystemComponent_Tests : public TestHarness< UXSystemComponent >
{

protected:

	MockEventManager* m_eventManager;
	MockLuaState* m_state;

	void EstablishContext( )
	{
		m_state = new MockLuaState( );
		m_eventManager = new MockEventManager( );
	}


	void DestroyContext( )
	{
		delete m_eventManager;
	}

	UXSystemComponent* CreateSubject( )
	{
		return new UXSystemComponent( m_state, m_eventManager ); 
	}
};

TEST_F( UXSystemComponent_Tests, should_subscribe_for_events )
{
	EXPECT_CALL( *m_eventManager, AddEventListener( An< IEventListener* >( ) ) )
		.WillOnce( Invoke( MockEventManager::ConsumeEventListener ) );

	m_subject->Initialize( );
}

TEST_F( UXSystemComponent_Tests, should_unsubscribe_from_events )
{
	EXPECT_CALL( *m_eventManager, RemoveEventListener( An< IEventListener* >( ) ) )
		.WillOnce( Invoke( MockEventManager::ConsumeEventListener ) );

	m_subject->Destroy( );
}

