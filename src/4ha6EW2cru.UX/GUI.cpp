#include "GUI.h"

using namespace MyGUI;

#include <Ogre.h>
using namespace Ogre;

#include "System/SystemType.hpp"
#include "System/AnyType.hpp"

using namespace Services;

namespace UX
{
	GUI::~GUI()
	{
		delete m_gui;
	}

	int GUI::GetViewWidth() const
	{
		return m_gui->getViewWidth( );
	}

	int GUI::GetViewHeight() const
	{
		return m_gui->getViewHeight( );
	}

	MyGUI::WidgetPtr GUI::FindWidget( const std::string& widgetName ) const
	{
		return m_gui->findWidgetT( widgetName );
	}

	void GUI::ShowMouse() const
	{
		m_gui->showPointer( );
	}

	void GUI::HideMouse() const
	{
		m_gui->hidePointer( );
	}

	void GUI::WindowResized() const
	{
		m_gui->windowResized( m_gui->getRenderWindow( ) );
	}

	void GUI::Initialize( const std::string& skinPath )
	{
		IService* renderService = m_serviceManager->FindService( System::Types::RENDER );
		Root* root = renderService->ProcessMessage( System::Messages::Graphics::GetRootSingleton, AnyType::AnyTypeMap( ) )[ "result" ].As< Root* >( );
		Root::initFromPtr( root ); 
		RenderWindow* renderWindow = renderService->ProcessMessage( System::Messages::Graphics::GetRenderWindow, AnyType::AnyTypeMap( ) )[ "renderWindow" ].As< Ogre::RenderWindow* >( );
		m_gui->initialise( renderWindow, skinPath, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, "" );

		WidgetManager::getInstancePtr( )->registerUnlinker( this );
	
	}

	void GUI::Destroy()
	{
		m_gui->shutdown( );
	}

	void GUI::MouseMoved( int x, int y, int z )
	{
		m_gui->injectMouseMove( x, y, z );
	}

	void GUI::MousePressed( int x, int y, int mouseButtonID )
	{
		m_gui->injectMousePress( x, y, MouseButton::Enum( mouseButtonID ) );
	}

	void GUI::MouseReleased( int x, int y, int mouseButtonID )
	{
		m_gui->injectMouseRelease( x, y, MouseButton::Enum( mouseButtonID ) );
	}

	void GUI::KeyReleased( int keyCode )
	{
		m_gui->injectKeyRelease( KeyCode::Enum( keyCode ) );
	}

	void GUI::KeyPressed( int keyCode )
	{
		m_gui->injectKeyPress( KeyCode::Enum( keyCode ) );
	}

	void GUI::LoadLayout( const std::string& layoutPath )
	{
		m_gui->load( layoutPath );
	}

	void GUI::Update( float deltaMilliseconds )
	{
		m_gui->injectFrameEntered( deltaMilliseconds );
	}

	void GUI::ClearScene()
	{
		m_gui->destroyAllChildWidget( );
	}

	void GUI::_unlinkWidget( WidgetPtr widget )
	{
		void* userData = widget->getUserData( );
		WidgetUserData* widgetUserData = static_cast< WidgetUserData* >( userData );

		if ( 0 != widgetUserData )
		{
			for ( WidgetUserData::iterator i = widgetUserData->begin( ); i != widgetUserData->end( ); ++i )
			{
				delete ( *i ).second;
			}

			delete widgetUserData;
		}
	}
}