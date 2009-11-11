#include <gtest/gtest.h>
using namespace testing;

#include "UXSystemScene.h"
using namespace UX;

#include "Mocks/MockGUI.hpp"
#include "Mocks/MockServiceManager.hpp"
#include "Mocks/MockService.hpp"
#include "Mocks/MockLuaState.hpp"
#include "Mocks/MockScriptFacade.hpp"
#include "Mocks/MockUXSystemComponentFactory.hpp"
#include "Mocks/MockUXSystemComponent.hpp"
#include "Mocks/MockEventManager.hpp"

#include <MyGUI.h>
using namespace MyGUI;

#include "Configuration/Configuration.h"
using namespace Configuration;

class UXSystemScene_Tests : public TestHarness< UXSystemScene >
{

protected:

	MockGUI* m_gui;
	MockServiceManager* m_serviceManager;
	MockLuaState* m_state;
	MockEventManager* m_eventManager;

	MockUXSystemComponentFactory* m_componentFactory;

	ClientConfiguration* m_configuration;

	void EstablishContext( )
	{
		m_gui = new MockGUI( );
		m_serviceManager = new MockServiceManager( );
		m_state = new MockLuaState( );
		m_componentFactory = new MockUXSystemComponentFactory( );
		m_configuration = new ClientConfiguration( );
		m_eventManager = new MockEventManager( );
	}


	void DestroyContext( )
	{
		delete m_gui;
		delete m_serviceManager;
		delete m_configuration;
		delete m_eventManager;
	}

	UXSystemScene* CreateSubject( )
	{
		return new UXSystemScene( m_gui, m_serviceManager, m_state, m_componentFactory, m_configuration, m_eventManager ); 
	}
};

TEST_F( UXSystemScene_Tests, should_initialize )
{
	// init master state
	EXPECT_CALL( *m_state, Initialize( ) );

	AnyType::AnyTypeMap results;

	// poll systems for script functions
	EXPECT_CALL( *m_serviceManager, MessageAll( System::Messages::RegisterScriptFunctions, An< AnyType::AnyTypeMap >( ) ) )
		.WillOnce( Return( results ) );

	m_subject->Initialize( );
}

TEST_F( UXSystemScene_Tests, should_destroy )
{
	EXPECT_CALL( *m_gui, ClearScene( ) );

	m_subject->Destroy( );
}

TEST_F( UXSystemScene_Tests, should_get_view_dimensions )
{
	int width = 10;
	int height = 7;

	EXPECT_CALL( *m_gui, GetViewHeight( ) ).WillOnce( Return( height ) );
	EXPECT_CALL( *m_gui, GetViewWidth( ) ).WillOnce( Return( width ) );

	int heightResult = m_subject->GetScreenHeight( );
	int widthResult = m_subject->GetScreenWidth( );

	EXPECT_EQ( width, widthResult );
	EXPECT_EQ( height, heightResult );
}

TEST_F( UXSystemScene_Tests, should_find_a_widget )
{
	std::string name = "test";

	WidgetPtr expected = 0;

	EXPECT_CALL( *m_gui, FindWidget( name ) ).WillOnce( Return( expected ) );

	WidgetPtr result = m_subject->FindWidget( name );

	EXPECT_EQ( expected, result );
}

TEST_F( UXSystemScene_Tests, should_show_mouse )
{
	EXPECT_CALL( *m_gui, ShowMouse( ) );

	m_subject->ShowMouse( );
}

TEST_F( UXSystemScene_Tests, should_hide_mouse )
{
	EXPECT_CALL( *m_gui, HideMouse( ) );

	m_subject->HideMouse( );
}

TEST_F( UXSystemScene_Tests, should_change_resolution )
{
	MockService service;

	EXPECT_CALL( *m_gui, WindowResized( ) );
	EXPECT_CALL( *m_serviceManager, FindService( System::Types::RENDER ) ).WillOnce( Return( &service ) );
	EXPECT_CALL( service, ProcessMessage( System::Messages::Graphics::ChangeResolution, An< AnyType::AnyTypeMap >( ) ) )
		.WillOnce( Return( AnyType::AnyTypeMap( ) ) );

	m_subject->ChangeResolution( 90, 10, true );
}

TEST_F( UXSystemScene_Tests, should_load_component )
{
	std::string name = "test";

	MockUXSystemComponent component;

	EXPECT_CALL( *m_componentFactory, CreateComponent( name ) ).WillOnce( Return( &component ) );
	EXPECT_CALL( *m_gui, WindowResized( ) );

	m_subject->LoadComponent( name );
}