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
		* @return (  )
		*/
		ScriptFacadeFactory( ) { };


		/*! Creates a ScriptFacade of the given type
		*
		* @param[in] IScriptFacade::FacadeType
		* @return ( IScriptFacade* )
		*/
		IScriptFacade* CreateScriptFacade( IScriptFacade::FacadeType facadeType, ISystemComponent* component, ILuaState* state );

	private:

		ScriptFacadeFactory( const ScriptFacadeFactory & copy ) { };
		ScriptFacadeFactory & operator = ( const ScriptFacadeFactory & copy ) { return *this; };
		
	};
};

#endif