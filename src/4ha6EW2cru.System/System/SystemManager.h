/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   SystemManager.h
*  @date   2009/04/25
*/
#pragma once
#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include "ISystemManager.hpp"
#include "../State/World.h"

#include "../Configuration/IConfiguration.hpp"
#include "../Service/IServiceManager.h"
#include "../IO/IResourceCache.hpp"
#include "../Events/IEventManager.hpp"
#include "../System/IInstrumentation.hpp"
#include "../Platform/IPlatformManager.h"

/*! 
*  Manages each System of the Game
*/
class GAMEAPI SystemManager : public ISystemManager
{

//  typedef std::map< ISystem*, HMODULE > SystemLibraryList;
  typedef std::map< ISystem*, void* > SystemLibraryList;

public:

	/*! Default Destructor
	*
	*  @return ()
	*/
	~SystemManager( ) { };


	/*! Default Constructor
	 *
	 *  @return ()
	 */
	SystemManager( 
		Configuration::IConfiguration* configuration, Services::IServiceManager* serviceManager, Resources::IResourceCache* resourceCache, 
		Events::IEventManager* eventManager, System::IInstrumentation* instrumentation, Platform::IPlatformManager* platformManager )
		: m_accumulator( 0.0f )
		, m_configuration( configuration )
		, m_serviceManager( serviceManager )
		, m_resourceCache( resourceCache )
		, m_eventManager( eventManager )
		, m_instrumentation( instrumentation )
		, m_platformManager( platformManager )
	{

	}


	/*! Loads the relevant Game Systems
	*
	* @param[in] bool isDedicated
	* @return ( void )
	*/
	void LoadSystems( bool isDedicated );

	
	/*! Loads a System dll and returns a pointer to the contained ISystem
	*
	* @param[in] const std::string & systemPath
	* @return ( ISystem* )
	*/
	ISystem* LoadSystem( const std::string& systemPath );


	/*! Registers a System
	*
	*  @param[in] ISystem * system
	*  @return (void)
	*/
	void RegisterSystem( const System::Queues::Queue& systemQueue, ISystem* system );


	/*! Gets a Registered System
	*
	*  @param[in] System::Types::Type systemType
	*  @return (ISystem*)
	*/
	ISystem* GetSystem( const System::Types::Type& systemType ) const;


	/*! Initializes all Registered Systems
	*
	*  @return (void)
	*/
	void InitializeAllSystems(  );


	/*! Checks to see if a system has been registered
	 *
	 *  @param[in] const System::Types::Type & systemType
	 *  @return (bool)
	 */
	bool HasSystem( const System::Types::Type& systemType ) const;


	/*! Steps each Registered System
	*
	*  @param[in] float deltaMilliseconds
	*  @return (void)
	*/
	void Update( float deltaMilliseconds );
	

	/*! Releases all Registered Systems
	*
	*  @return (void)
	*/
	void Release( );


	/*! Creates a World from All Registered Systems
	*
	*  @return (IWorld*)
	*/
	State::IWorld* CreateWorld( );

private:

	SystemManager( const SystemManager & copy ) { };
	SystemManager & operator = ( const SystemManager & copy ) { return *this; };

	ISystem::SystemTypeMap _systemsByType;
	ISystem::SystemQueueMap _systemsByQueue;

	SystemLibraryList m_systemLibraries;

	float m_accumulator;

	Configuration::IConfiguration* m_configuration;
	Services::IServiceManager* m_serviceManager;
	Resources::IResourceCache* m_resourceCache;
	Events::IEventManager* m_eventManager;
	System::IInstrumentation* m_instrumentation;
	Platform::IPlatformManager* m_platformManager;

};

#endif
