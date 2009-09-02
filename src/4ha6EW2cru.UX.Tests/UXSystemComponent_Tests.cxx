#include <gtest/gtest.h>
using namespace testing;

#include "UXSystemComponent.h"
using namespace UX;

#include "Mocks/MockGUI.hpp"
#include "Mocks/MockLuaState.hpp"

class UXSystemComponent_Tests : public TestHarness< UXSystemComponent >
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

	UXSystemComponent* CreateSubject( )
	{
		return new UXSystemComponent( m_state ); 
	}
};

