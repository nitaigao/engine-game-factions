/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   LuaState.h
*  @date   2009/08/27
*/
#pragma once
#ifndef LUASTATE_H
#define LUASTATE_H

#include "ILuaState.hpp"

namespace Script
{
	/*! 
	 *  The Interface to the LUA Scripting Engine
	 */
	class GAMEAPI LuaState : public ILuaState
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~LuaState( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		LuaState( )
			: m_state( 0 )
		{

		}


		/*! Initializes a new Lua State 
		*
		* @return ( void )
		*/
		void Initialize( );


		/*! Destroys the lua_State
		*
		* @return ( void )
		*/
		void Destroy( );


		/*! Creates a Child LuaState
		*
		* @return ( ILuaState* )
		*/
		ILuaState* CreateChild( );

		
		/*! Sets a Script Global within the LuaState
		 *
		 * @param[in] const std::string & globalName
		 * @param[in] T * subject
		 * @return ( void )
		 */
		template< class T >
		void SetGlobal( const std::string& globalName, T* subject )
		{
			luabind::globals( m_state )[ globalName ] = subject;
		}

		/*! Registers Types for use in the LuaState Script
		*
		* @param[in] luabind::scope
		* @return ( void )
		*/
		void RegisterTypes( const luabind::scope& classScope );

	private:

		LuaState( const LuaState & copy ) { };
		LuaState & operator = ( const LuaState & copy ) { return *this; };

		lua_State* m_state;
		
	};
};

#endif