/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IInputFactory.hpp
*  @date   2009/11/07
*/
#pragma once
#ifndef IINPUTFACTORY_HPP
#define IINPUTFACTORY_HPP

#include "IInputSystem.hpp"

namespace Input
{
	/*! 
	 *  Creates Input Objects
	 */
	class IInputFactory
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~IInputFactory( ) { };


		/*! Creates an Input System
		 *
		 * @return ( IInputSystem* )
		 */
		virtual IInputSystem* CreateInputSystem( ) = 0;
		
	};
};

#endif