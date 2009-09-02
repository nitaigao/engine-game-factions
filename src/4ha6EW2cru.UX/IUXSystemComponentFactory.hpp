/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IUXSystemComponentFactory.hpp
*  @date   2009/09/02
*/
#pragma once
#ifndef IUXSYSTEMCOMPONENTFACTORY_HPP
#define IUXSYSTEMCOMPONENTFACTORY_HPP

#include "IUXSystemComponent.hpp"

namespace UX
{
	/*! 
	 *  Creates UX System Components
	 */
	class IUXSystemComponentFactory
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~IUXSystemComponentFactory( ) { };


		/*! Creates a Script Component
		*
		* @param[in] const std::string & name
		* @return ( IUXSystemComponent* )
		*/
		virtual IUXSystemComponent* CreateComponent( const std::string& name ) = 0;
		
	};
};

#endif