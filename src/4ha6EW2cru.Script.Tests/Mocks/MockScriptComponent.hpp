/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockScriptComponent.hpp
*  @date   2009/08/27
*/
#pragma once
#ifndef MOCKSCRIPTCOMPONENT_HPP
#define MOCKSCRIPTCOMPONENT_HPP

#include <gmock/gmock.h>

#include "IScriptComponent.hpp"

namespace
{
	class MockScriptComponent : public IScriptComponent
	{

	public:

		MOCK_METHOD1( Serialize, void( IO::IStream* ) );
		MOCK_METHOD1( DeSerialize, void( IO::IStream* ) );
		MOCK_METHOD0( Initialize, void( ) );
		MOCK_METHOD1( Update, void( float ) );
		MOCK_METHOD0( Destroy, void( ) );
		MOCK_CONST_METHOD0( GetAttributes, AnyType::AnyTypeMap( ) );
		MOCK_METHOD2( SetAttribute, void( const System::Attribute&, const AnyType& ) );
		MOCK_METHOD3( Observe, AnyType( const ISubject*, const System::MessageType&, AnyType::AnyTypeMap ) );
		MOCK_METHOD1( AddObserver, void( IObserver* ) );
		MOCK_METHOD2( PushMessage, AnyType( const System::MessageType&, AnyType::AnyTypeMap ) );

		MOCK_METHOD2( RegisterEventHandler, void( const std::string&, const luabind::object& ) );
		MOCK_METHOD2( RegisterEventHandler, void( const std::string&, IScriptFunctionHandler* ) );

		MOCK_METHOD2( SubscribeMessage, void( const System::MessageType&, const luabind::object& ) );
		MOCK_METHOD2( UnSubscribeMessage, void( const System::MessageType&,  const luabind::object& ) );

		MOCK_METHOD1( RegisterUpdateHandler, void( const luabind::object& ) );
		MOCK_METHOD1( UnRegisterUpdateHandler, void( const luabind::object& ) );
		
		MOCK_CONST_METHOD0( GetState, lua_State*( ) );
		MOCK_METHOD0( RunScript, void( ) );
	};
};

#endif