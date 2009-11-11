#include "UXSystem.h"

#include "UXSystemScene.h"
#include "UXSystemComponent.h"

#include "Management/Management.h"

#include <MyGUI.h>
using namespace MyGUI;

#include <Ogre.h>

#include <luabind/luabind.hpp>
#include <luabind/table_policy.hpp>
#include <luabind/copy_policy.hpp>
using namespace luabind;

#include "Events/EventType.hpp"
#include "Events/EventData.hpp"
#include "Events/EventListener.h"
#include "Events/InputEventData.hpp"
using namespace Events;

#include "ScriptConfiguration.h"
#include "LuaState.h"
using namespace Script;

namespace UX
{
	ISystemScene* UXSystem::CreateScene( )
	{
		return m_scene;
	}

	AnyType::AnyTypeMap UXSystem::ProcessMessage( const System::MessageType& message, AnyType::AnyTypeMap parameters )
	{
		AnyType::AnyTypeMap results;

		if ( message == System::Messages::PostInitialize )
		{
			m_scene->Initialize( ); 
		}

		if ( message == System::Messages::RegisterScriptFunctions )
		{
			scope luaScope = 
			(

			class_< ScriptConfiguration >( "Config" )
				.def( constructor< Configuration::IConfiguration* >( ) )
					.property( "isFullScreen", &ScriptConfiguration::IsFullScreen, &ScriptConfiguration::SetFullScreen )
					.property( "displayWidth", &ScriptConfiguration::GetDisplayWidth, &ScriptConfiguration::SetDisplayWidth )
					.property( "displayHeight", &ScriptConfiguration::GetDisplayHeight, &ScriptConfiguration::SetDisplayHeight )
					.property( "isConsole", &ScriptConfiguration::IsConsole, &ScriptConfiguration::SetConsole )
					.property( "isInvertY", &ScriptConfiguration::IsInvertY, &ScriptConfiguration::SetInvertY )
					.property( "isSmoothMouse", &ScriptConfiguration::IsSmoothMouse, &ScriptConfiguration::SetSmoothMouse )
					.property( "mouseSmoothAmount", &ScriptConfiguration::GetMouseSmoothAmount, &ScriptConfiguration::SetMouseSmoothAmount )
					.property( "sfxVolume", &ScriptConfiguration::GetSFXVolume, &ScriptConfiguration::SetSFXVolume )
					.property( "musicVolume", &ScriptConfiguration::GetMusicVolume, &ScriptConfiguration::SetMusicVolume )
					.property( "serverPort", &ScriptConfiguration::GetServerPort, &ScriptConfiguration::SetServerPort )
					.property( "serverBotCount", &ScriptConfiguration::GetServerBotCount, &ScriptConfiguration::SetServerBotCount )
					.property( "serverName", &ScriptConfiguration::GetServerName, &ScriptConfiguration::SetServerName )
					.property( "serverTimeLimit", &ScriptConfiguration::GetServerTimeLimit, &ScriptConfiguration::SetServerTimeLimit )
					.property( "serverFragLimit", &ScriptConfiguration::GetServerFragLimit, &ScriptConfiguration::SetServerFragLimit )
					.property( "serverMaxPlayers", &ScriptConfiguration::GetServerMaxPlayers, &ScriptConfiguration::SetServerMaxPlayers )
					,

			class_< UXSystemComponent >( "UXSystemComponent" )
				.def( "registerEventHandler", ( void ( UXSystemComponent::* ) ( const std::string&, const luabind::object& ) ) &UXSystemComponent::RegisterEventHandler )
				.def( "unregisterEventHandler", ( void ( UXSystemComponent::* ) ( const std::string&, const luabind::object& ) ) &UXSystemComponent::UnregisterEventHandler )
				.def( "registerUpdateHandler", &UXSystemComponent::RegisterUpdate )
				.def( "unregisterUpdateHandler", &UXSystemComponent::UnRegisterUpdate )
				.def( "executeString", &UXSystemComponent::ExecuteString )
				,

			class_< UXSystemScene >( "UXSystemScene" )
				.def( "findWidget", &UXSystemScene::FindWidget )
				.def( "loadComponent", &UXSystemScene::LoadComponent )
				.def( "getScreenWidth", &UXSystemScene::GetScreenWidth )
				.def( "getScreenHeight", &UXSystemScene::GetScreenHeight )
				.def( "getSupportedResolutions", &UXSystemScene::GetSupportedResolutions, copy_table( result ) )
				.def( "scriptWidget", &UXSystemScene::ScriptWidget )
				.def( "unscriptWidget", &UXSystemScene::UnScriptWidget) 
				.def( "showMouse", &UXSystemScene::ShowMouse )
				.def( "hideMouse", &UXSystemScene::HideMouse )
				.def( "setInputAllowed", &UXSystemScene::SetInputAllowed )
				.def( "changeResolution", &UXSystemScene::ChangeResolution )
				.def( "showScreen", &UXSystemScene::ShowScreen )
				,

			class_< Widget >( "Widget" )
				.def( constructor< WidgetStyle, const IntCoord&, Align, WidgetSkinInfo*, WidgetPtr, ICroppedRectangle*, IWidgetCreator*, const std::string& >( ) )
				.def( "getDimensions", &Widget::getClientCoord )
				.def( "setSize", ( void( Widget::* )( int, int ) ) &Widget::setSize )
				.def( "setPosition", ( void( Widget::* )( int, int ) ) &Widget::setPosition )
				.def( "getType", &Widget::getClassTypeName )
				.def( "setVisible", &Widget::setVisible )
				.def( "isVisible", &Widget::isVisible )
				.def( "getAlpha", &Widget::getAlpha )
				.def( "setAlpha", &Widget::setAlpha )
				.def( "getText", &UXSystemScene::GetText )
				.def( "setText", &UXSystemScene::SetText )
				.def( "asButton", &UXSystemScene::AsButton )
				.def( "asComboBox", &UXSystemScene::AsComboBox )
				.def( "asEditBox", &UXSystemScene::AsEditBox )
				.def( "asProgressBar", &UXSystemScene::AsProgressBar )
				.def( "asMultiList", &UXSystemScene::AsMultiList )
				.def( "asWindow", &UXSystemScene::AsWindow )
				.def( "asScrollbar", &UXSystemScene::AsScrollBar )
				.def( "setFocus", &UXSystemScene::SetFocus )
				,

			class_< Button, Widget >( "Button" )
				.def( constructor< WidgetStyle, const IntCoord&, Align, WidgetSkinInfo*, WidgetPtr, ICroppedRectangle*, IWidgetCreator*, const std::string& >( ) )
				.def( "setChecked", &Button::setStateCheck )
				.def( "getChecked", &Button::getStateCheck )
				,

			class_< ComboBox, Widget >( "ComboBox" )
				.def( constructor< WidgetStyle, const IntCoord&, Align, WidgetSkinInfo*, WidgetPtr, ICroppedRectangle*, IWidgetCreator*, const std::string& >( ) )
				.def( "addItem", ( void ( ComboBox::* ) ( const std::string&, const std::string& ) ) &ComboBox::addItem )
				.def( "getValueAt", ( const std::string& ( ComboBox::* ) ( int ) ) &ComboBox::getItemNameAt )
				.def( "getSelectedIndex", &ComboBox::getIndexSelected )
				.def( "setSelectedIndex", &ComboBox::setIndexSelected )
				,

			class_< Edit, Widget >( "EditBox" )
				.def( constructor< WidgetStyle, const IntCoord&, Align, WidgetSkinInfo*, WidgetPtr, ICroppedRectangle*, IWidgetCreator*, const std::string& >( ) )
				.def( "addText", &UXSystemScene::Edit_AddText )
				.def( "eraseText", &UXSystemScene::Edit_EraseText )
				.def( "getLength", &UXSystemScene::Edit_GetLength )
				,

			class_< Progress, Widget >( "ProgressBar" )
				.def( constructor< WidgetStyle, const IntCoord&, Align, WidgetSkinInfo*, WidgetPtr, ICroppedRectangle*, IWidgetCreator*, const std::string& >( ) )
				.def( "setProgress", &Progress::setProgressPosition ),

			class_< MultiList, Widget >( "MultiList" )
				.def( constructor< WidgetStyle, const IntCoord&, Align, WidgetSkinInfo*, WidgetPtr, ICroppedRectangle*, IWidgetCreator*, const std::string& >( ) )
				.def( "addColumn", &UXSystemScene::MultiList_AddColumn )
				.def( "removeAllColumns", &MultiList::removeAllColumns )
				.def( "removeAllItems", &MultiList::removeAllItems )
				.def( "addItem", &UXSystemScene::MultiList_AddItem )
				.def( "getItemName", &UXSystemScene::MultiList_GetItemName )
				.def( "getSubItemName", &UXSystemScene::MultiList_GetSubItemName )
				.def( "setSubItemName", &UXSystemScene::MultiList_SetSubItemName  )
				.def( "getColumnCount", &UXSystemScene::MultiList_GetColumnCount )
				.def( "getColumnWidthAt", &UXSystemScene::MultiList_GetColumnWidthAt )
				.def( "setColumnWidthAt", &UXSystemScene::MultiList_SetColumnWidthAt )
				.def( "getItemCount", &UXSystemScene::MultiList_GetItemCount )
				.def( "getSelectedIndex", &UXSystemScene::MultiList_GetSelectedIndex )
				,

			class_< VScroll, Widget >( "Scrollbar" )
				.def( constructor< WidgetStyle, const IntCoord&, Align, WidgetSkinInfo*, WidgetPtr, ICroppedRectangle*, IWidgetCreator*, const std::string& >( ) )
				.def( "getScrollPosition", &VScroll::getScrollPosition )
				.def( "setScrollPosition", &VScroll::setScrollPosition )
				,

			class_< Window, Widget >( "Window" )
				.def( constructor< WidgetStyle, const IntCoord&, Align, WidgetSkinInfo*, WidgetPtr, ICroppedRectangle*, IWidgetCreator*, const std::string& >( ) )
				,

			class_< IntCoord >( "IntCoord" )
				.def( constructor< >( ) )
				.def_readonly( "x" , &IntCoord::left )
				.def_readonly( "y" , &IntCoord::top )
				.def_readonly( "width" , &IntCoord::width )
				.def_readonly( "height" , &IntCoord::height )
				,

			class_< Any >( "Any" )
				.def( constructor<>( ) )
				,

			class_< EventType >( "EventType" )
			,

			class_< UIEventData, IEventData >( "UIEventData" )
				.def( "getParam1", &UIEventData::GetParameter1 )
				.def( "getParam2", &UIEventData::GetParameter2 )

			);

			results[ System::TypeStrings::UX ] = luaScope;
		}

		return results;
	}

	void UXSystem::Update( float deltaMilliseconds )
	{
		m_gui->Update( deltaMilliseconds );
		m_scene->Update( deltaMilliseconds );
	}

	void UXSystem::Initialize( Configuration::IConfiguration* configuration )
	{
		m_serviceManager->RegisterService( this );

		m_eventManager->RegisterEventType( EventTypes::UI_SHOW_PANE );
		m_eventManager->AddEventListener( EventTypes::INPUT_MOUSE_PRESSED, MakeEventListener( this, &UXSystem::OnMousePressed ) );
		m_eventManager->AddEventListener( EventTypes::INPUT_MOUSE_MOVED, MakeEventListener( this, &UXSystem::OnMouseMoved ) );
		m_eventManager->AddEventListener( EventTypes::INPUT_MOUSE_RELEASED, MakeEventListener( this, &UXSystem::OnMouseReleased ) );
		m_eventManager->AddEventListener( EventTypes::INPUT_KEY_DOWN, MakeEventListener( this, &UXSystem::OnKeyDown ) );
		m_eventManager->AddEventListener( EventTypes::INPUT_KEY_UP, MakeEventListener( this, &UXSystem::OnKeyUp ) );

		m_gui->Initialize( "/data/interface/core/core.xml" );//, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, "" );
		m_gui->HideMouse( );
	}

	UXSystem::~UXSystem()
	{
		delete m_gui;
	}

	void UXSystem::Release( )
	{
		m_eventManager->RemoveEventListener( EventTypes::INPUT_MOUSE_PRESSED, MakeEventListener( this, &UXSystem::OnMousePressed ) );
		m_eventManager->RemoveEventListener( EventTypes::INPUT_MOUSE_MOVED, MakeEventListener( this, &UXSystem::OnMouseMoved ) );
		m_eventManager->RemoveEventListener( EventTypes::INPUT_MOUSE_RELEASED, MakeEventListener( this, &UXSystem::OnMouseReleased ) );
		m_eventManager->RemoveEventListener( EventTypes::INPUT_KEY_DOWN, MakeEventListener( this, &UXSystem::OnKeyDown ) );
		m_eventManager->RemoveEventListener( EventTypes::INPUT_KEY_UP, MakeEventListener( this, &UXSystem::OnKeyUp ) );

		m_gui->Destroy( );
	}

	void UXSystem::OnMouseMoved( const IEvent* event )
	{
		MouseEventData* eventData = static_cast< MouseEventData* >( event->GetEventData( ) );
		m_gui->MouseMoved( eventData->GetX( ), eventData->GetY( ), eventData->GetZ( ) );
	}

	void UXSystem::OnMousePressed( const IEvent* event )
	{
		MouseEventData* eventData = static_cast< MouseEventData* >( event->GetEventData( ) );
		m_gui->MousePressed( eventData->GetX( ), eventData->GetY( ), MouseButton::Enum( eventData->GetMouseButtonId( ) ) );
	}

	void UXSystem::OnMouseReleased( const IEvent* event )
	{
		MouseEventData* eventData = static_cast< MouseEventData* >( event->GetEventData( ) );
		m_gui->MouseReleased( eventData->GetX( ), eventData->GetY( ), MouseButton::Enum( eventData->GetMouseButtonId( ) ) );
	}

	void UXSystem::OnKeyUp( const IEvent* event )
	{
		KeyEventData* eventData = static_cast< KeyEventData* >( event->GetEventData( ) );
		m_gui->KeyReleased( KeyCode::Enum( eventData->GetKeyCode( ) ) );
	}

	void UXSystem::OnKeyDown( const IEvent* event )
	{
		KeyEventData* eventData = static_cast< KeyEventData* >( event->GetEventData( ) );
		m_gui->KeyPressed( KeyCode::Enum( eventData->GetKeyCode( ) ) );
	}
};