/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockNetworkSystemProvider.hpp
*  @date   2009/08/17
*/
#pragma once
#ifndef MOCKNETWORKSYSTEMPROVIDER_HPP
#define MOCKNETWORKSYSTEMPROVIDER_HPP

#include <gmock/gmock.h>

#include "INetworkProvider.hpp"

namespace
{
	class MockNetworkSystemProvider : public INetworkProvider
	{

	public:

		MOCK_METHOD2( Initialize, void( unsigned int, int ) );
		MOCK_METHOD1( Update, void( float ) );
		MOCK_METHOD3( Message, void( const std::string&, const System::Message&, AnyType::AnyTypeMap ) );

		
	};
};

#endif