#include <gtest/gtest.h>
using namespace testing;

#include "SoundSystem.h"
using namespace Sound;

#include "Mocks/MockSoundSystemScene.hpp"

class SoundSystem_Tests : public TestHarness< SoundSystem >
{

protected:

	MockSoundSystemScene* m_scene;

	void EstablishContext( )
	{
		m_scene = new MockSoundSystemScene( );
	}


	void DestroyContext( )
	{
		delete m_scene;
	}

	SoundSystem* CreateSubject( )
	{
		return new SoundSystem( m_scene );
	}
};

TEST_F( SoundSystem_Tests, should_create_scene )
{
	ISystemScene* scene = m_subject->CreateScene( );
	EXPECT_EQ( m_scene, scene );
}