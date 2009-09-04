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

#include "IO/IResourceCache.hpp"

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
		LuaState( Resources::IResourceCache* resourceCache )
			: m_state( 0 )
			, m_resourceCache( resourceCache )
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


		/*! Loads a Script File from the FileSystem
		*
		* @param[in] const std::string & scriptPath
		* @return ( void )
		*/
		void LoadScript( const std::string& scriptPath );


		/*! Executes this Script State
		*
		* @return ( void )
		*/
		void Execute( );


		/*! Runs a new Parse over a Script
		*
		* @return ( void )
		*/
		void ReParse( );


		/*! Executes the given string as Lua code
		*
		* @param[in] const std::string & scriptString
		* @return ( void )
		*/
		void ExecuteString( const std::string& scriptString );

	private:

		LuaState( const LuaState & copy ) { };
		LuaState & operator = ( const LuaState & copy ) { return *this; };

		static int LuaPanic( lua_State* state ); 

		lua_State* m_state;
		Resources::IResourceCache* m_resourceCache;
		
	};
};

#endif