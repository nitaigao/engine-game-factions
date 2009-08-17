/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockNetworkSystemScene.hpp
*  @date   2009/08/17
*/
#pragma once
#ifndef MOCKNETWORKSYSTEMSCENE_HPP
#define MOCKNETWORKSYSTEMSCENE_HPP

#include "INetworkSystemScene.hpp"

#include <gmock/gmock.h>

namespace
{
	class MockNetworkSystemScene : public INetworkSystemScene
	{

	public:

		MOCK_METHOD1( AddNetworkProvider, void( INetworkProvider* ) );
		MOCK_CONST_METHOD0( GetSystem, INetworkSystem*( ) );
		MOCK_METHOD3( MessageComponent, void( const std::string&, const System::Message&, AnyType::AnyTypeMap ) );


		MOCK_METHOD0( Initialize, void( ) );
		MOCK_METHOD1( Update, void( float ) );
		MOCK_METHOD0( Destroy, void( ) );
		MOCK_CONST_METHOD0( GetType, System::Types::Type( ) );
		MOCK_METHOD2( CreateComponent, ISystemComponent*( const std::string&, const std::string& ) );
		MOCK_METHOD1( DestroyComponent, void( ISystemComponent* ) );
		
	};
};

#endif