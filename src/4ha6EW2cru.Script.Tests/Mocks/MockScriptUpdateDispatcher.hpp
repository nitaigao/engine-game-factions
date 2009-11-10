/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockScriptUpdateDispatcher.hpp
*  @date   2009/11/08
*/
#pragma once
#ifndef MOCKSCRIPTUPDATEDISPATCHER_HPP
#define MOCKSCRIPTUPDATEDISPATCHER_HPP

#include <gmock/gmock.h>

#include "IScriptUpdateDispatcher.hpp"

namespace
{
	class MockScriptUpdateDispatcher : public IScriptUpdateDispatcher
	{

	public:

		MOCK_METHOD1( RegisterUpdateHandler, void( IScriptFunctionHandler* ) );
		MOCK_METHOD1( Update, void( float ) );
		MOCK_METHOD1( UnRegisterUpdateHandler, void( IScriptFunctionHandler* ) );
		MOCK_METHOD0( Destroy, void( ) );


		static void ConsumeFunctionHandler( IScriptFunctionHandler* handler )
		{
			delete handler;
		}

	};
};

#endif