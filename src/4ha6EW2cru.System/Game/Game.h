/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   GameRoot.h
*  @date   2009/04/25
*/
#pragma once
#ifndef GAME_H
#define GAME_H

#include "../Configuration/IConfiguration.hpp"

#include "../Events/IEvent.hpp"
#include "../State/IWorld.hpp"

#include "IGame.hpp"

#include "../Configuration/Configuration.h"
#include "../Platform/IPlatformManager.h"
#include "../Platform/IProgramOptions.hpp"
#include "../System/ISystemManager.hpp"
#include "../Events/IEventManager.hpp"
#include "../Service/IServiceManager.h"
#include "../IO/IFileSystem.hpp"

#include "../Export.hpp"

namespace Game
{
	/*! 
	 *  The core container of the GameRoot
	 */
	class GAMEAPI GameRoot : public IGame
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~GameRoot( ) { };


		/*! Default Constructor
		 *
		 *  @return ()
		 */
		GameRoot( 
			Platform::IProgramOptions* programOptions, Configuration::IConfiguration* configuration, Platform::IPlatformManager* platformManager, 
			ISystemManager* systemManager, Events::IEventManager* eventManager, Services::IServiceManager* serviceManager, IO::IFileSystem* fileSystem
			)
			: m_isQuitting( false )
			, m_isInitialized( false )
			, m_world( 0 )
			, m_platformManager( platformManager )
			, m_programOptions( programOptions )
			, m_systemManager( systemManager )
			, m_configuration( configuration )
			, m_eventManager( eventManager )
			, m_serviceManager( serviceManager )
			, m_fileSystem( fileSystem )
		{

		}
		

		/*! Initializes the GameRoot
		 *
		 *  @return (void)
		 */
		void Initialize( );


		/*! Steps the GameRoot forward
		 *
		 *  @param[in] float deltaMilliseconds
		 *  @return (void)
		 */
		void Update( );

		
		/*! Releases the GameRoot
		 *
		 *  @return (void)
		 */
		void Release( );


		/*! Returns whether or not the GameRoot is ready to Quit
		 *
		 *  @return (bool)
		 */
		bool IsQuitting( ) const { return m_isQuitting; };

	private:

		void OnGameQuit( const Events::IEvent* event );
		void OnGameLevelChanged( const Events::IEvent* event );
		void OnGameEnded( const Events::IEvent* event );

		bool m_isQuitting;
		bool m_isInitialized;

		Configuration::IConfiguration* m_configuration;
		State::IWorld* m_world;
		Platform::IPlatformManager* m_platformManager;
		Platform::IProgramOptions* m_programOptions;
		ISystemManager* m_systemManager;
		Events::IEventManager* m_eventManager;
		Services::IServiceManager* m_serviceManager;
		IO::IFileSystem* m_fileSystem;

		GameRoot( const GameRoot & copy ) { };
		GameRoot & operator = ( const GameRoot & copy ) { return *this; };

	};
};

#endif


// EOF