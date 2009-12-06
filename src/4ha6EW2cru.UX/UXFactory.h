/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   UXFactory.h
*  @date   2009/09/02
*/
#pragma once
#ifndef UXFACTORY_H
#define UXFACTORY_H

#include "IUXSystem.hpp"
#include "IGUI.hpp"

#include "Configuration/IConfiguration.hpp"
#include "Service/IServiceManager.h"
#include "Events/IEventManager.hpp"
#include "IO/IResourceCache.hpp"
#include "Platform/IPlatformManager.h"
#include "System/IInstrumentation.hpp"

namespace UX
{
	class IUXFactory
	{
		/*! Creates a UX System
		 *
		 * @return ( IUXSystem* )
		 */
		virtual IUXSystem* CreateUXSystem( ) = 0;


		/*! Creates a UX GUI
		 *
		 * @return ( IGUI* )
		 */
		virtual IGUI* CreateUXGUI( ) = 0;

	};


	/*! 
	 *  Creates UX Classes
	 */
	class UXFactory : public IUXFactory
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~UXFactory( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		UXFactory( Configuration::IConfiguration* configuration, Events::IEventManager* eventManager, 
			Services::IServiceManager* serviceManager, Resources::IResourceCache* resourceCache,
			Platform::IPlatformManager* platformManager, System::IInstrumentation* instrumentation
			)
			: m_configuration( configuration )
			, m_eventManager( eventManager )
			, m_serviceManager( serviceManager )
			, m_resourceCache( resourceCache )
			, m_platformManager( platformManager )
			, m_instrumentation( instrumentation )
		{

		}


		
		/*! Creates a UX System
		 *
		 * @param[in] IConfiguration * configuration
		 * @return ( IUXSystem* )
		 */
		IUXSystem* CreateUXSystem( );


		/*! Creates a UX GUI
		*
		* @return ( IGUI* )
		*/
		IGUI* CreateUXGUI( );

	private:

		UXFactory( const UXFactory & copy ) { };
		UXFactory & operator = ( const UXFactory & copy ) { return *this; };

		Services::IServiceManager* m_serviceManager;
		Events::IEventManager* m_eventManager;
		Configuration::IConfiguration* m_configuration;
		Resources::IResourceCache* m_resourceCache;
		Platform::IPlatformManager* m_platformManager;
		System::IInstrumentation* m_instrumentation;
		
	};
};

#endif