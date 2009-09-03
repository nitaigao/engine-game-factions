/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   UXSystemComponentFactory.h
*  @date   2009/09/02
*/
#pragma once
#ifndef UXSYSTEMCOMPONENTFACTORY_H
#define UXSYSTEMCOMPONENTFACTORY_H

#include "IUXSystemComponentFactory.hpp"

#include "ILuaState.hpp"
#include "IGUI.hpp"
#include "Events/IEventManager.hpp"

namespace UX
{
	/*! 
	 *  Creates UX System Components
	 */
	class UXSystemComponentFactory : public IUXSystemComponentFactory
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~UXSystemComponentFactory( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		UXSystemComponentFactory( Script::ILuaState* masterState, IGUI* gui, Events::IEventManager* eventManager )
			: m_masterState( masterState )
			, m_gui( gui )
			, m_eventManager( eventManager )
		{

		}


		/*! Creates a Script Component
		*
		* @param[in] const std::string & name
		* @return ( IUXSystemComponent* )
		*/
		IUXSystemComponent* CreateComponent( const std::string& name );

	private:

		UXSystemComponentFactory( const UXSystemComponentFactory & copy ) { };
		UXSystemComponentFactory & operator = ( const UXSystemComponentFactory & copy ) { return *this; };

		Script::ILuaState* m_masterState;
		Events::IEventManager* m_eventManager;
		IGUI* m_gui;

	};
};

#endif