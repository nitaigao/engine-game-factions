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
		ScriptFactory( ) { };


		/*! Creates the Script System
		 *
		 * @return ( IScriptSystem* )
		 */
		IScriptSystem* CreateScriptSystem( );


		/*! Creates a Script System Scene
		 *
		 * @return ( IScriptSystemScene* )
		 */
		IScriptSystemScene* CreateScriptSystemScene( );

	private:

		ScriptFactory( const ScriptFactory & copy ) { };
		ScriptFactory & operator = ( const ScriptFactory & copy ) { return *this; };
		
	};
};

#endif