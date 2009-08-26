#include <gtest/gtest.h>
using namespace testing;

#include "SoundSystem.h"
using namespace Sound;

#include "Mocks/MockSoundSystemScene.hpp"
#include "Mocks/MockSoundEventSystem.hpp"

#include "Mocks/MockServiceManager.hpp"

#include "Configuration/Configuration.h"
using namespace Configuration;

#include <fmod.h>

class SoundSystem_Tests : public TestHarness< SoundSystem >
{

protected:

	MockSoundSystemScene* m_scene;
	MockSoundEventSystem* m_eventSystem;
	MockServiceManager* m_serviceManager;

	void EstablishContext( )
	{
		m_serviceManager = new MockServiceManager( );
		m_scene = new MockSoundSystemScene( );
		m_eventSystem = new MockSoundEventSystem( );
	}


	void DestroyContext( )
	{
		delete m_scene;
		delete m_serviceManager;
	}

	SoundSystem* CreateSubject( )
	{
		return new SoundSystem( m_serviceManager, m_scene, m_eventSystem );
	}
};

TEST_F( SoundSystem_Tests, should_create_scene )
{
	ISystemScene* scene = m_subject->CreateScene( );
	EXPECT_EQ( m_scene, scene );
}

TEST_F( SoundSystem_Tests, should_destroy_the_event_system )
{
	EXPECT_CALL( *m_eventSystem, Destroy( ) ); 
	m_subject->Release( );
}

TEST_F( SoundSystem_Tests, should_update_the_event_system )
{
	float delta = 10.0f;
	EXPECT_CALL( *m_eventSystem, Update( delta ) );
	m_subject->Update( delta );
}

TEST_F( SoundSystem_Tests, should_initialize_the_event_system )
{
	ClientConfiguration config;

	EXPECT_CALL( *m_eventSystem, Initialize( An< FMOD::System* >( ) ) );
	m_subject->Initialize( &config );
}

TEST_F( SoundSystem_Tests, should_add_to_the_service_manager )
{
	ClientConfiguration config;
	EXPECT_CALL( *m_serviceManager, RegisterService( m_subject ) );
	m_subject->Initialize( &config );
}