#include "LuaState.h"

using namespace luabind;
using namespace luabind::adl;

#include "IO/IResource.hpp"
using namespace Resources;

extern "C" 
{
#	include <lua.h>
#	include <lualib.h>
}

#include "Exceptions/OutOfRangeException.hpp"
#include "Exceptions/ScriptException.hpp"

#include "Logging/Logger.h"
using namespace Logging;

namespace Script
{
	void LuaState::Initialize( )
	{
		m_state = lua_open( );

		luaL_openlibs( m_state );
		luabind::open( m_state );

		object scriptTable = newtable( m_state );
		registry( m_state )[ "Scripts" ] = scriptTable;
		
	}

	void LuaState::Destroy( )
	{
		lua_close( m_state );
		m_state = 0;
	}

	ILuaState* LuaState::CreateChild( )
	{
		LuaState* childState = new LuaState( m_resourceCache );

		int result = lua_checkstack( m_state, LUA_MINSTACK );

		if( !result )
		{
			OutOfRangeException e( "Unable to grow the LUA stack to the required size" );
			Fatal( e.what( ) );
			throw e;
			std::terminate( );
		}

		// = luabind::registry( m_state )[ "Scripts" ];

		int top = lua_gettop( m_state ); 
		lua_getfield( m_state, LUA_REGISTRYINDEX, "Scripts" ); // top + 1

		childState->m_state = lua_newthread( m_state ); // top + 2 

		lua_newtable( m_state );  // a global table for this script 
		lua_newtable( m_state );  // meta table 

		lua_getfenv( m_state,top + 2 ); // that returns the global table (we are going to protect) 
		lua_setfield( m_state, -2, "__index" ); // set global table as __index of the thread 
		lua_setmetatable( m_state, -2 );
		lua_setfenv( m_state, top + 2 );  // set environment of the new thread

		lua_pushlightuserdata( m_state, childState ); // key, the pointer to my own   Script class 
		lua_pushvalue( m_state, top + 2 );          // value, the new lua thread. 
		lua_rawset( m_state, top + 1 ); // Scripts table 
		lua_settop( m_state, top ); 

		return childState;
	}

	void LuaState::RegisterTypes( const luabind::scope& classScope )
	{
		module( m_state )
		[
			classScope
		];
	}

	void LuaState::LoadScript( const std::string& scriptPath )
	{
		IResource* resource = m_resourceCache->GetResource( scriptPath );

		int result = luaL_loadbuffer( m_state, resource->GetFileBuffer( )->fileBytes, resource->GetFileBuffer( )->fileLength, resource->GetFileBuffer( )->filePath.c_str( ) );

		if ( LUA_ERRSYNTAX == result )
		{
			std::stringstream errorMessage;
			errorMessage << lua_tostring( m_state, -1 );
			Warn( errorMessage.str( ) );
			lua_pop( m_state, 1 );
		}

		if ( LUA_ERRMEM == result )
		{
			ScriptException memE( "Script::Initialize - There is memory allocation error within the Script" );
			Fatal( memE.what( ) );
			throw memE;
		}
	}

	void LuaState::Execute( )
	{
		try
		{
			resume< void >( m_state );
		}
		catch( error& e )
		{
			object error_msg( from_stack( e.state( ) , -1) );
			std::stringstream logMessage;
			logMessage << error_msg;
			Warn( logMessage.str( ) );
		}
	}

	void LuaState::ExecuteString( const std::string& scriptString )
	{
		if ( luaL_dostring( m_state, scriptString.c_str( ) ) )
		{
			std::stringstream errorMessage;
			errorMessage << lua_tostring( m_state, -1 );
			Warn( errorMessage.str( ) );
			lua_pop( m_state, 1 );
		}
	}

	void LuaState::ReParse( )
	{
		if ( lua_pcall( m_state, 0, 0, 0 ) )
		{
			std::stringstream errorMessage;
			errorMessage << lua_tostring( m_state, -1 );
			Warn( errorMessage.str( ) );
			lua_pop( m_state, 1 );
		}
	}

	int LuaState::LuaPanic( lua_State* state )
	{
		int a= 1;

		return 0;
	}
}