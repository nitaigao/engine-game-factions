#include <gtest/gtest.h>
using namespace testing;

#include "SoundEventSystem.h"
using namespace Sound;

class SoundEventSystem_Tests : public TestHarness< SoundEventSystem >
{

protected:

	void EstablishContext( )
	{

	}


	void DestroyContext( )
	{

	}

	SoundEventSystem* CreateSubject( )
	{
		return new SoundEventSystem( );
	}
};

