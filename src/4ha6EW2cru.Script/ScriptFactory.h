/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ScriptFactory.h
*  @date   2009/08/27
*/
#pragma once
#ifndef SCRIPTFACTORY_H
#define SCRIPTFACTORY_H

#include "IScriptSystem.hpp"
#include "IScriptSystemScene.hpp"

#include "Configuration/IConfiguration.hpp"
#include "Service/IServiceManager.h"
#include "IO/IResourceCache.hpp"
#include "Events/IEventManager.hpp"

namespace Script
{
	/*! 
	 *  Creates Script System Classes
	 */
	class ScriptFactory
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~ScriptFactory( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		ScriptFactory( 
			Configuration::IConfiguration* configuration, Services::IServiceManager* serviceManager, 
			Resources::IResourceCache* resourceCache, Events::IEventManager* eventManager 
			)
			: m_configuration( configuration )
			, m_serviceManager( serviceManager )
			, m_resourceCache( resourceCache )
			, m_eventManager( eventManager )
		{

		}


		/*! Creates the Script System
		 *
		 * @return ( IScriptSystem* )
		 */
		IScriptSystem* CreateScriptSystem(  );


		/*! Creates a Script System Scene
		 *
		 * @return ( IScriptSystemScene* )
		 */
		IScriptSystemScene* CreateScriptSystemScene( );

	private:

		ScriptFactory( const ScriptFactory & copy ) { };
		ScriptFactory & operator = ( const ScriptFactory & copy ) { return *this; };


		Configuration::IConfiguration* m_configuration;
		Services::IServiceManager* m_serviceManager;
		Resources::IResourceCache* m_resourceCache;
		Events::IEventManager* m_eventManager;
		
	};
};

#endif