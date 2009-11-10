/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockScriptMessageDispatcher.hpp
*  @date   2009/09/05
*/
#pragma once
#ifndef MOCKSCRIPTMESSAGEDISPATCHER_HPP
#define MOCKSCRIPTMESSAGEDISPATCHER_HPP

#include <gmock/gmock.h>

#include "IScriptMessageDispatcher.hpp"

namespace
{
	class MockScriptMessageDispatcher : public IScriptMessageDispatcher
	{

	public:

		MOCK_METHOD2( Dispatch_Message, void( const System::MessageType&, AnyType::AnyTypeMap& ) );
		MOCK_METHOD2( AddMessageHandler, void( const System::MessageType&, luabind::object ) );
		MOCK_METHOD2( HasHandler, bool( const System::MessageType&, luabind::object ) );
		MOCK_METHOD2( RemoveHandler, void( const System::MessageType&, luabind::object ) );
		MOCK_METHOD1( Update, void( float ) );
		
	};
};

#endif