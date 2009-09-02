/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   GUI.h
*  @date   2009/09/02
*/
#pragma once
#ifndef GUI_H
#define GUI_H

#include "IGUI.hpp"
#include "Service/IServiceManager.h"

#include <MyGui.h>

namespace UX
{
	/*! 
	 *  The interface to the GUI System
	 */
	class GAMEAPI GUI : public IGUI
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~GUI( );


		/*! Default Constructor
		*
		* @return (  )
		*/
		GUI( MyGUI::Gui* gui, Services::IServiceManager* serviceManager )
			: m_gui( gui )
			, m_serviceManager( serviceManager )
		{

		}


		/*! Returns the ViewPort Width
		*
		* @return ( int )
		*/
		int GetViewWidth( ) const;


		/*! Returns the ViewPort Height
		*
		* @return ( int )
		*/
		int GetViewHeight( ) const;


		/*! Finds a widget within the GUI
		*
		* @param[in] const std::string & widgetName
		* @return ( MyGUI::WidgetPtr )
		*/
		MyGUI::WidgetPtr FindWidget( const std::string& widgetName ) const;


		/*! Shows the mouse on the Screen
		*
		* @return ( void )
		*/
		void ShowMouse( ) const;


		/*! Hides the mouse on the Screen
		*
		* @return ( void )
		*/
		void HideMouse( ) const;


		/*! Instructs the GUI that the window has been resized
		*
		* @return ( void )
		*/
		void WindowResized( ) const;


		/*! Initializes the GUI
		*
		* @param[in] const std::string & skinPath
		* @return ( void )
		*/
		void Initialize( const std::string& skinPath );


		/*! Destroys the GUI
		*
		* @return ( void )
		*/
		void Destroy( );


		/*! Informs the GUI that the mouse has been moved
		*
		* @param[in] int x
		* @param[in] int y
		* @param[in] int z
		* @return ( void )
		*/
		void MouseMoved( int x, int y, int z );


		/*! Informs the GUI that a mouse button has been pressed
		*
		* @param[in] int x
		* @param[in] int y
		* @param[in] int mouseButtonID
		* @return ( void )
		*/
		void MousePressed( int x, int y, int mouseButtonID );


		/*! Informs the GUI that a mouse button has been released
		*
		* @param[in] int x
		* @param[in] int y
		* @param[in] int mouseButtonID
		* @return ( void )
		*/
		void MouseReleased( int x, int y, int mouseButtonID );



		/*! Informs the GUI that a key has been released
		*
		* @param[in] int keyCode
		* @return ( void )
		*/
		void KeyReleased( int keyCode );


		/*! Informs the GUI that a key has been pressed
		*
		* @param[in] int keyCode
		* @return ( void )
		*/
		void KeyPressed( int keyCode );


		/*! Loads a layout from the file system
		*
		* @param[in] const std::string & layoutPath
		* @return ( void )
		*/
		void LoadLayout( const std::string& layoutPath );


		/*! Updates the GUI
		*
		* @param[in] float deltaMilliseconds
		* @return ( void )
		*/
		void Update( float deltaMilliseconds );

	private:

		GUI( const GUI & copy ) { };
		GUI & operator = ( const GUI & copy ) { return *this; };

		Services::IServiceManager* m_serviceManager;
		MyGUI::Gui* m_gui;
		
	};
};

#endif