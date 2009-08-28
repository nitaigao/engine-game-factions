#include <gtest/gtest.h>
using namespace testing;

#include "ScriptSystem.h"
using namespace Script;

#include "Mocks/MockScriptSystemScene.hpp"
#include "Mocks/MockServiceManager.hpp"

#include "Mocks/MockScriptComponent.hpp"

#include "Configuration/Configuration.h"
using namespace Configuration;

class ScriptSystem_Tests : public TestHarness< ScriptSystem >
{

protected:

	MockScriptSystemScene* m_scene;
	MockScriptSystemScene* m_auxScene;
	MockServiceManager* m_serviceManager;

	void EstablishContext( )
	{
		m_scene = new MockScriptSystemScene( );
		m_auxScene = new MockScriptSystemScene( );
		m_serviceManager = new MockServiceManager( );
	}

	void DestroyContext( )
	{
		delete m_scene;
		delete m_serviceManager;
	}

	ScriptSystem* CreateSubject( )
	{
		return new ScriptSystem( m_scene, m_auxScene, m_serviceManager ); 
	}
};

TEST_F( ScriptSystem_Tests, should_register_with_service_manager )
{
	EXPECT_CALL( *m_serviceManager, RegisterService( m_subject ) );

	ClientConfiguration config;

	m_subject->Initialize( &config );
}

TEST_F( ScriptSystem_Tests, post_init_should_initailize_scenes )
{
	EXPECT_CALL( *m_scene, Initialize( ) );
	EXPECT_CALL( *m_auxScene, Initialize( ) );

	ClientConfiguration config;

	m_subject->ProcessMessage( System::Messages::PostInitialize, AnyType::AnyTypeMap( ) );
}

TEST_F( ScriptSystem_Tests, should_destroy_aux_scene )
{
	EXPECT_CALL( *m_auxScene, Destroy( ) );
	m_subject->Release( );
}

TEST_F( ScriptSystem_Tests, should_create_scene )
{
	ISystemScene* actual = m_subject->CreateScene( );
	EXPECT_EQ( m_scene, actual );
}

TEST_F( ScriptSystem_Tests, should_update_scenes )
{
	float delta = 10.0f;

	EXPECT_CALL( *m_auxScene, Update( delta ) );
	EXPECT_CALL( *m_scene, Update( delta ) );

	m_subject->Update( delta );
}

TEST_F( ScriptSystem_Tests, should_create_component_for_aux_scene )
{
	std::string name = "name";
	std::string type = "type";

	MockScriptComponent component;

	EXPECT_CALL( *m_auxScene, CreateComponent( name, "default" ) ).WillOnce( Return( &component ) );

	AnyType::AnyTypeMap parameters;
	parameters[ System::Attributes::Name ] = name;
	parameters[ System::Parameters::ScriptPath ] = "some/path";

	m_subject->ProcessMessage( System::Messages::LoadScript, parameters );
}

TEST_F( ScriptSystem_Tests, should_unload_component_from_aux_scene )
{
	std::string name = "name";

	EXPECT_CALL( *m_auxScene, UnloadComponent( name ) );

	AnyType::AnyTypeMap parameters;
	parameters[ System::Attributes::Name ] = name;

	m_subject->ProcessMessage( System::Messages::UnloadComponent, parameters );
}