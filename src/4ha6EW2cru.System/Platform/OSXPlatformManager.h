/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   OSXPlatformManager.h
*  @date   2009/04/26
*/
#pragma once
#ifndef OSXPLATFORMMANAGER_H
#define OSXPLATFORMMANAGER_H

#include "IPlatformManager.h"

#include "../Events/IEvent.hpp"
#include "../Events/IEventManager.hpp"
#include "../IO/IPathInformation.hpp"

#include "../Export.hpp"

namespace Platform
{
	/*! 
	*  Interfaces with the Windows Platform
	*/
	class GAMEAPI OSXPlatformManager : public IPlatformManager
	{

	public:

		/*! Default Destructor
		*
		*  @return ()
		*/
		~OSXPlatformManager( );


		/*! Default Constructor
		 *
		 *  @return ()
		 */
		OSXPlatformManager( Events::IEventManager* eventManager, IO::IPathInformation* pathInformation, IClock* clock )
			: m_hWnd( 0 )
			, m_pathInformation( pathInformation )
			, m_eventManager( eventManager )
			, m_clock( clock )
		{

		}


		/*! Initializes the Platform Manager and all Sub Components
		*
		* @return ( void )
		*/
		void Initialize( );


		/*! Creates an Interactive Window for the Player
		*
		*  @param[in] const std::string & title
		*  @param[in] const int & width
		*  @param[in] const int & height
		*  @param[in] const bool & fullScreen
		*  @return (void)
		*/
		void CreateInteractiveWindow( const std::string& title, int width, int height, bool fullScreen );
		

		/*! Closes the Open Window
		*
		*  @return (void)
		*/
		void CloseWindow( );


		/*! Creates a Console Window
		*
		*  @return (void)
		*/
		void CreateConsoleWindow( );


		/*! Outputs the given message to std::cout
		*
		* @param[in] const std::string & message
		* @return ( void )
		*/
		void OutputToConsole( const std::string& message );


		/*! Steps internal data structures
		*
		*  @param[in] float deltaMilliseconds
		*  @return (void)
		*/
		void Update( float deltaMilliseconds );
		

		/*! Gets the id of the active game window
		*
		*  @return (size_t)
		*/
		size_t GetWindowId( ) const;


		/*! Returns the Clock from the Win32 Platform
		*
		* @return ( IClock& )
		*/
		inline IClock* GetClock( ) { return m_clock; };


		/*! Outputs a message to the Debug Console
		*
		*  @return (void)
		*/
		void OutputDebugMessage( const std::string& message );


		/*! Generates a unique UUID
		*
		* @return ( std::string )
		*/
		std::string GenUUID( ) const;


		/*! Returns the Path Information for the platform
		*
		* @return ( IPathInformation* )
		*/
		inline IO::IPathInformation* GetPathInformation( ) { return m_pathInformation; };

	private:

		size_t m_hWnd;
		IClock* m_clock;
		IO::IPathInformation* m_pathInformation;
		Events::IEventManager* m_eventManager;

		OSXPlatformManager( const OSXPlatformManager & copy ) { };
		OSXPlatformManager & operator = ( const OSXPlatformManager & copy ) { return *this; };

	};
};

#endif
