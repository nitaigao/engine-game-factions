/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IScriptComponentFactory.hpp
*  @date   2009/08/27
*/
#pragma once
#ifndef ISCRIPTCOMPONENTFACTORY_HPP
#define ISCRIPTCOMPONENTFACTORY_HPP

#include "IScriptComponent.hpp"

#include "Export.hpp"

namespace Script
{
	/*! 
	 *  Creates Script Components
	 */
	class GAMEAPI IScriptComponentFactory
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~IScriptComponentFactory( ) { };


		/*! Creates a Script Component
		 *
		 * @param[in] const std::string & name
		 * @param[in] const std::string & type
		 * @return ( IScriptComponent* )
		 */
		virtual IScriptComponent* CreateComponent( const std::string& name, const std::string& type ) = 0;
		
	};
};

#endif