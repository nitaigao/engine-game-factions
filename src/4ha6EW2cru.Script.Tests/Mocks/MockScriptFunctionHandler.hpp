/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockScriptFunctionHandler.hpp
*  @date   2009/09/04
*/
#pragma once
#ifndef MOCKSCRIPTFUNCTIONHANDLER_HPP
#define MOCKSCRIPTFUNCTIONHANDLER_HPP

#include <gmock/gmock.h>

#include "IScriptFunctionHandler.hpp"

namespace
{
	class MockScriptFunctionHandler : public IScriptFunctionHandler
	{

	public:

		MOCK_METHOD0( MarkForDeletion, void( ) );
		MOCK_CONST_METHOD0( IsMarkedForDeletion, bool( ) );
		MOCK_METHOD1( CallFunction, void( AnyType::AnyTypeMap ) );
		MOCK_CONST_METHOD0( GetFunction, luabind::object( ) );
		
	};
};

#endif