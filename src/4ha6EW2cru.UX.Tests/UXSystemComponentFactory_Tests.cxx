#include <gtest/gtest.h>
using namespace testing;

#include "UXSystemComponentFactory.h"
using namespace UX;

#include "Mocks/MockLuaState.hpp"
#include "Mocks/MockGUI.hpp"

class UXSystemComponentFactory_Tests : public TestHarness< UXSystemComponentFactory >
{

protected:

	MockLuaState* m_masterState;
	MockGUI* m_gui;

	void EstablishContext( )
	{
		m_masterState = new MockLuaState( );
		m_gui = new MockGUI( );
	}


	void DestroyContext( )
	{

	}

	UXSystemComponentFactory* CreateSubject( )
	{
		return new UXSystemComponentFactory( m_masterState, m_gui ); 
	}
};