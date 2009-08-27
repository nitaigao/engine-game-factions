/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ILuaState.hpp
*  @date   2009/08/27
*/
#pragma once
#ifndef ILUASTATE_HPP
#define ILUASTATE_HPP

#include "Export.hpp"
#include <luabind/luabind.hpp>

namespace Script
{
	/*! 
	 *  The Interface to the LUA Script Engine
	 */
	class GAMEAPI ILuaState
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~ILuaState( ) { };


		/*! Initializes a new LuaState 
		*
		* @return ( void )
		*/
		virtual void Initialize( ) = 0;


		/*! Destroys the lua_State
		 *
		 * @return ( void )
		 */
		virtual void Destroy( ) = 0;


		/*! Creates a Child LuaState
		 *
		 * @return ( ILuaState* )
		 */
		virtual ILuaState* CreateChild( ) = 0;


		/*! Registers Types for use in the LuaState Script
		 *
		 * @param[in] luabind::scope
		 * @return ( void )
		 */
		virtual void RegisterTypes( const luabind::scope& classScope ) = 0;
		
	};
};

#endif