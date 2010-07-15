/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   UXSystemScene.h
*  @date   2009/04/26
*/
#pragma once
#ifndef UXSYSTEMSCENE_H
#define UXSYSTEMSCENE_H

#include "IUXSystemScene.hpp"
#include "IUXSystemComponent.hpp"
#include "IUXSystemComponentFactory.hpp"

#include "Events/IEvent.hpp"

#include <luabind/luabind.hpp>
#include "IGUI.hpp"
#include "ILuaState.hpp"
#include "IScriptFacadeManager.hpp"
#include "IScriptConfiguration.hpp"

#include "Service/IServiceManager.h"
#include "Events/IEventManager.hpp"
#include "Configuration/IConfiguration.hpp"

namespace UX
{
  /*! 
   *  A scene specific to the UX System
   */
  class GAMEAPI UXSystemScene : public IUXSystemScene
  {

  public:

    /*! Default Destructor
    *
    *  @return ()
    */
    ~UXSystemScene( );


    /*! Default Constructor
    *
    *  @return ()
    */
    UXSystemScene( 
      IGUI* gui, 
      Services::IServiceManager* serviceManager, 
      Script::ILuaState* masterState, 
      IUXSystemComponentFactory* componentFactory, 
      Configuration::IConfiguration* configuration,
      Events::IEventManager* eventManager
      )
      : m_gui( gui )
      , m_serviceManager( serviceManager )
      , m_masterState( masterState )
      , m_componentFactory( componentFactory )
      , m_configuration( configuration )
      , m_scriptConfiguration( 0 )
      , m_eventManager( eventManager )
    {

    }


    /*!  Initializes the System Scene
    *
    *  @return (void)
    */
    void Initialize( );


    /*! Steps internal data of the SystemScene
    *
    *  @param[in] float deltaMilliseconds
    *  @return (void)
    */
    void Update( float deltaMilliseconds );


    /*! Destroys the System Scene
    *
    *  @return (void)
    */
    void Destroy( );


    /*! Gets the System::Types::Type of the SystemScene
    *
    *  @return (System::Types::Type)
    */
    inline System::Types::Type GetType( ) const { return System::Types::UX; };


    /*! Creates a SystemComponent specific to the SystemScene
    *
    *  @param[in] const std::string & name
    *  @param[in] const std::string & type
    *  @return (ISystemComponent*)
    */
    ISystemComponent* CreateComponent( const std::string& name, const std::string& type ) { return 0; };


    /*! Destroys a SystemComponent created by the SystemScene
    *
    *  @param[in] ISystemComponent * component
    *  @return (void)
    */
    void DestroyComponent( ISystemComponent* component ) { };


    /*! Sends KeyUp Events to the UX Components
    *
    * @param[in] int keyCode
    * @param[in] const std::string & keyText
    * @return ( void )
    */
    void OnKeyUp( int keyCode, const std::string& keyText ) { };


  // script helpers
  public:


    /*! Loads a UI Component for Rendering
    *
    *  @param[in] const std::string componentName
    *  @return (void)
    */
    void LoadComponent( const std::string componentName );


    /*! Retrieves a widget from the UI
    *
    *  @param[in] const std::string widgetName
    *  @return (MyGUI::WidgetPtr)
    */
    MyGUI::WidgetPtr FindWidget( const std::string widgetName ) { return m_gui->FindWidget( widgetName ); };


    /*! Attaches an LUA function to a Widget Event
    *
    *  @param[in] MyGUI::Widget * widget
    *  @param[in] const std::string eventName
    *  @param[in] luabind::object function
    *  @return (void)
    */
    void ScriptWidget( MyGUI::Widget* widget, const std::string eventName, luabind::object function );


    /*! Removes an LUA function from a Widget Event
    *
    *  @param[in] MyGUI::Widget * widget
    *  @param[in] const std::string eventName
    *  @param[in] luabind::object function
    *  @return (void)
    */
    void UnScriptWidget( MyGUI::Widget* widget, const std::string& eventName, luabind::object function );


    /*! Shows the mouse
    *
    *  @return (void)
    */
    inline void ShowMouse( ) { m_gui->ShowMouse( ); };


    /*! Hides the mouse
    *
    *  @return (void)
    */
    inline void HideMouse( ) { m_gui->HideMouse( ); };


    /*! Sets whether or not the Player controls can manipulate the scene
    *
    *  @param[in] bool inputAllowed
    *  @return (void)
    */
    void SetInputAllowed( bool inputAllowed );


    /*! Causes the Renderer to adjust the Resolution to match the Configuration
    *
    *  @param[in] int width
    *  @param[in] int height
    *  @param[in] bool isFullScreen
    *  @return (void)
    */
    void ChangeResolution( int width, int height, bool isFullScreen );


    /*!  Returns the Screen Width in pixels
    *
    *  @return (int)
    */
    int GetScreenWidth( ) { return m_gui->GetViewWidth( ); };


    /*! Returns the Screen Height in pixels
    *
    *  @return (int)
    */
    int GetScreenHeight( ) { return m_gui->GetViewHeight( ); };


    /*! -- Widget Event Handlers -- */

    /*! Forwards Mouse Button Released Events to the subscribing Widgets in Script
    *
    *  @param[in] MyGUI::WidgetPtr widget
    *  @param[in] int left
    *  @param[in] int top
    *  @param[in] MyGUI::MouseButton id
    *  @return (void)
    */
    static void OnMouseReleased( MyGUI::WidgetPtr widget, int left, int top, MyGUI::MouseButton id );


    /*! Forwards the Mouse Button Pressed Events to the subscribing Widgets in Script
    *
    * @param[in] MyGUI::WidgetPtr widget
    * @param[in] int left
    * @param[in] int top
    * @param[in] MyGUI::MouseButton id
    * @return ( void )
    */
    static void OnMousePressed( MyGUI::WidgetPtr widget, int left, int top, MyGUI::MouseButton id );


    /*! Forwards Key Up Events to the subscribing Widgets in Script
    *
    *  @param[in] MyGUI::WidgetPtr widget
    *  @param[in] MyGUI::KeyCode key
    *  @return (void)
    */
    static void OnKeyUp( MyGUI::WidgetPtr widget, MyGUI::KeyCode key );


    /*! Forwards the List Select Events to the sibscribing Widgets in Script
    *
    * @param[in] MyGUI::MultiListPtr widget
    * @param[in] size_t index
    * @return ( void )
    */
    static void OnListSelectAccept( MyGUI::MultiListPtr widget, size_t index );


    /*! Forwards the Scroll Events to the subscribed widgets in Script
    *
    * @param[in] MyGUI::VScrollPtr sender
    * @param[in] size_t position
    * @return ( void )
    */
    static void OnEventScrollChangePosition( MyGUI::VScrollPtr widget, size_t position );


    /*! Forwards Window Button Events to the widgets in Script
    *
    * @param[in] MyGUI::WindowPtr window
    * @param[in] const std::string & name
    * @return ( void )
    */
    static void OnWindowButtonPressed( MyGUI::WindowPtr widget, const std::string& name );


    /*! Forwards Window Change Coord/Resize Events to the widgets in Script
    *
    * @param[in] MyGUI::WindowPtr window
    * @return ( void )
    */
    static void OnWindowChangeCoord( MyGUI::WindowPtr widget );


    /*! Returns a list of supported Video Resolutions
    *
    *  @return (std::vector< std::string >)
    */
    std::vector< std::string > GetSupportedResolutions( );


    void ShowScreen( const std::string& screenName );


    // widget functions
    public:

    static inline void SetFocus( MyGUI::WidgetPtr widget, bool focus )
    {
      if ( focus )
      {
        MyGUI::InputManager::getInstancePtr( )->setKeyFocusWidget( widget );
      }
      else
      {
        MyGUI::InputManager::getInstancePtr( )->resetKeyFocusWidget( widget );
      }
    }

    static inline void SetText( MyGUI::WidgetPtr widget, const std::string& text ) { widget->setCaption( text ); };
    static inline std::string GetText( MyGUI::WidgetPtr widget ) { return widget->getCaption( ).asUTF8( ); };
    
    static inline void Edit_AddText( MyGUI::EditPtr editWidget, const std::string& text ) { editWidget->addText( text ); };
    static inline void Edit_EraseText( MyGUI::EditPtr editWidget, int start, int count ) { editWidget->eraseText( start, count ); };
    static inline int Edit_GetLength( MyGUI::EditPtr editWidget ) { return editWidget->getTextLength( ); };

    static inline void MultiList_AddColumn( MyGUI::MultiListPtr widget, const std::string& name, int width ) { widget->addColumn( name, width ); };
    static inline void MultiList_AddItem( MyGUI::MultiListPtr widget, const std::string& name ) { widget->addItem( name ); };
    static inline int MultiList_GetSelectedIndex( MyGUI::MultiListPtr widget ) { return static_cast< int >( widget->getIndexSelected( ) ); };
    static inline int MultiList_GetColumnCount( MyGUI::MultiListPtr widget ) { return static_cast< int >( widget->getColumnCount( ) ); };
    static inline int MultiList_GetColumnWidthAt( MyGUI::MultiListPtr widget, int index ) { return widget->getColumnWidthAt( index ); };
    static inline void MultiList_SetColumnWidthAt( MyGUI::MultiListPtr widget, int index, int width ) { return widget->setColumnWidthAt( index, width ); };
    static inline std::string MultiList_GetItemName( MyGUI::MultiListPtr widget, int index ) { return widget->getItemNameAt( index ); };
    static inline std::string MultiList_GetSubItemName( MyGUI::MultiListPtr widget, int column, int index ) { return widget->getSubItemNameAt( column, index ); };
    static inline int MultiList_GetItemCount( MyGUI::MultiListPtr widget ) { return static_cast< int >( widget->getItemCount( ) ); };
    static inline void MultiList_SetSubItemName( MyGUI::MultiListPtr widget, int column, int index, const std::string& name ) { widget->setSubItemNameAt( column,index, name ); };

    static inline MyGUI::ButtonPtr AsButton( MyGUI::WidgetPtr widget ) { return static_cast< MyGUI::ButtonPtr >( widget ); };
    static inline MyGUI::ComboBoxPtr AsComboBox( MyGUI::WidgetPtr widget ) { return static_cast< MyGUI::ComboBoxPtr >( widget ); };
    static inline MyGUI::EditPtr AsEditBox( MyGUI::WidgetPtr widget ) { return static_cast< MyGUI::EditPtr >( widget ); };
    static inline MyGUI::ProgressPtr AsProgressBar( MyGUI::WidgetPtr widget ) { return static_cast< MyGUI::ProgressPtr >( widget ); };
    static inline MyGUI::MultiListPtr AsMultiList( MyGUI::WidgetPtr widget ) { return static_cast< MyGUI::MultiListPtr >( widget ); };
    static inline MyGUI::VScrollPtr AsScrollBar( MyGUI::WidgetPtr widget ) { return static_cast< MyGUI::VScrollPtr > ( widget ); };
    static inline MyGUI::WindowPtr AsWindow( MyGUI::WidgetPtr widget ) { return static_cast< MyGUI::WindowPtr >( widget ); };

  private:

    IGUI* m_gui;
    IUXSystemComponent::UXSystemComponentList m_components;
    Services::IServiceManager* m_serviceManager;
    Script::ILuaState* m_masterState;
    Script::IScriptConfiguration* m_scriptConfiguration;
    Configuration::IConfiguration* m_configuration;
    IUXSystemComponentFactory* m_componentFactory;
    Events::IEventManager* m_eventManager;
  };
};

#endif
