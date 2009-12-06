/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   InputFactory.h
*  @date   2009/11/07
*/
#pragma once
#ifndef INPUTFACTORY_H
#define INPUTFACTORY_H

#include "IInputFactory.hpp"

#include "Events/IEventManager.hpp"
#include "Platform/IPlatformManager.h"
#include "Service/IServiceManager.h"

namespace Input
{
	/*! 
	 *  Creates Input Objects
	 */
	class InputFactory : public IInputFactory
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~InputFactory( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		InputFactory( Events::IEventManager* eventManager, Platform::IPlatformManager* platformManager, Services::IServiceManager* serviceManager ) 
			: m_eventManager( eventManager )
			, m_platformManager( platformManager )
			, m_serviceManager( serviceManager )
		{

		}


		/*! Creates an Input System
		*
		* @return ( IInputSystem* )
		*/
		IInputSystem* CreateInputSystem( );

	private:

		InputFactory( const InputFactory & copy ) { };
		InputFactory & operator = ( const InputFactory & copy ) { return *this; };

		Events::IEventManager* m_eventManager;
		Platform::IPlatformManager* m_platformManager;
		Services::IServiceManager* m_serviceManager;
	};
};

#endif