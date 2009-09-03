#include <gtest/gtest.h>
using namespace testing;

#include "UXSystemComponentFactory.h"
using namespace UX;

#include "Mocks/MockLuaState.hpp"
#include "Mocks/MockGUI.hpp"
#include "Mocks/MockEventManager.hpp"

class UXSystemComponentFactory_Tests : public TestHarness< UXSystemComponentFactory >
{

protected:

	MockLuaState* m_masterState;
	MockGUI* m_gui;
	MockEventManager* m_eventManager;

	void EstablishContext( )
	{
		m_masterState = new MockLuaState( );
		m_eventManager = new MockEventManager( );
		m_gui = new MockGUI( );
	}


	void DestroyContext( )
	{
		delete m_eventManager;
	}

	UXSystemComponentFactory* CreateSubject( )
	{
		return new UXSystemComponentFactory( m_masterState, m_gui, m_eventManager ); 
	}
};