/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ScriptFacadeFactory.h
*  @date   2009/08/27
*/
#pragma once
#ifndef SCRIPTFACADEFACTORY_H
#define SCRIPTFACADEFACTORY_H

#include "IScriptFacadeFactory.hpp"
#include "Service/IServiceManager.h"
#include "Events/IEventManager.hpp"
#include "Platform/IPlatformManager.h"
#include "System/IInstrumentation.hpp"
#include "IO/ResourceCache.h"

namespace Script
{
	/*! 
	 *  Creates Script Facades
	 */
	class GAMEAPI ScriptFacadeFactory : public IScriptFacadeFactory
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~ScriptFacadeFactory( ) { };


		
		/*! Default Constructor
		 *
		 * @param[in] Services::IServiceManager * serviceManager
		 * @param[in] Events::IEventManager * eventManager
		 * @param[in] Platform::IPlatformManager * platformManager
		 * @param[in] System::IInstrumentation * instrumentation
		 * @param[in] Resources::IResourceCache * resourceCache
		 * @return (  )
		 */
		ScriptFacadeFactory( Services::IServiceManager* serviceManager, Events::IEventManager* eventManager, Platform::IPlatformManager* platformManager, System::IInstrumentation* instrumentation, Resources::IResourceCache* resourceCache )
			: m_serviceManager( serviceManager )
			, m_eventManager( eventManager )
			, m_platformManager( platformManager )
			, m_instrumentation( instrumentation )
			, m_resourceCache( resourceCache )
		{

		}


		/*! Creates a ScriptFacade of the given type
		*
		* @param[in] IScriptFacade::FacadeType
		* @return ( IScriptFacade* )
		*/
		IScriptFacade* CreateScriptFacade( IScriptFacade::FacadeType facadeType, ISystemComponent* component, ILuaState* state );

	private:

		ScriptFacadeFactory( const ScriptFacadeFactory & copy ) { };
		ScriptFacadeFactory & operator = ( const ScriptFacadeFactory & copy ) { return *this; };

		Services::IServiceManager* m_serviceManager;
		Events::IEventManager* m_eventManager;
		Platform::IPlatformManager* m_platformManager;
		System::IInstrumentation* m_instrumentation;
		Resources::IResourceCache* m_resourceCache;
		
	};
};

#endif