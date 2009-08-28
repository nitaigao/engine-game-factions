/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockLuaState.hpp
*  @date   2009/08/27
*/
#pragma once
#ifndef MOCKLUASTATE_HPP
#define MOCKLUASTATE_HPP

#include <gmock/gmock.h>

#include "ILuaState.hpp"

namespace
{
	class MockLuaState : public ILuaState
	{

	public:

		MOCK_METHOD0( Initialize, void( ) );
		MOCK_METHOD0( Destroy, void( ) );
		MOCK_METHOD0( CreateChild, ILuaState*( ) );
		MOCK_METHOD1( RegisterTypes, void( const luabind::scope& ) );
		MOCK_METHOD1( LoadScript, void( const std::string& ) );
		MOCK_METHOD0( Execute, void( ) );
		MOCK_METHOD0( ReParse, void( ) );
		MOCK_METHOD1( ExecuteString, void( const std::string& ) );
		
	};
};

#endif