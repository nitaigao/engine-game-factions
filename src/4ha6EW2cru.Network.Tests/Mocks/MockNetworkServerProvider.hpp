/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockNetworkServerProvider.hpp
*  @date   2009/08/20
*/
#pragma once
#ifndef MOCKNETWORKSERVERPROVIDER_HPP
#define MOCKNETWORKSERVERPROVIDER_HPP

#include <gmock/gmock.h>

#include "INetworkServerProvider.hpp"

namespace
{
	class MockNetworkServerProvider : public INetworkServerProvider
	{

	public:

		MOCK_METHOD2( Connect, void( const std::string&, unsigned int ) );
		MOCK_METHOD0( Disconnect, void( ) );
		MOCK_METHOD2( Initialize, void ( unsigned int, int ) );
		MOCK_METHOD1( Update, void( float ) );
		MOCK_METHOD3( Message, void( const std::string&, const System::Message&, AnyType::AnyTypeMap ) );
		MOCK_METHOD0( Destroy, void( ) );
		MOCK_METHOD1( OnGameLevelChanged, void( const Events::IEvent* ) );
		
	};
};

#endif