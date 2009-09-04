/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ScriptFacadeManager.h
*  @date   2009/08/27
*/
#pragma once
#ifndef SCRIPTFACADEMANAGER_H
#define SCRIPTFACADEMANAGER_H

#include "IScriptFacadeManager.hpp"
#include "IScriptFacadeFactory.hpp"
#include "ILuaState.hpp"

namespace UX
{
	/*! 
	 *  Manages all of the Facades exposed to the Lua Script Engine
	 */
	class GAMEAPI UXFacadeManager : public Script::IScriptFacadeManager
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~UXFacadeManager( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		UXFacadeManager( Script::IScriptFacadeFactory* facadeFactory, Script::ILuaState* state )
			: m_facadeFactory( facadeFactory )
			, m_state( state )
		{

		}


		/*! Initializes the Facade Manager with the given ScriptComponent
		*
		* @param[in] IScriptComponent *
		* @return ( void )
		*/
		void Initialize( Script::IScriptComponent* scriptComponent );


		/*! Destroys each ScriptFacade
		*
		* @return ( void )
		*/
		void Destroy( );

	private:

		UXFacadeManager( const UXFacadeManager & copy ) { };
		UXFacadeManager & operator = ( const UXFacadeManager & copy ) { return *this; };

		Script::IScriptFacadeFactory* m_facadeFactory;
		Script::IScriptFacade::ScriptFacadeList m_facades;
		Script::ILuaState* m_state;
		
	};
};

#endif