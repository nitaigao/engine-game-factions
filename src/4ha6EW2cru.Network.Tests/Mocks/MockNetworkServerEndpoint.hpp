/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockNetworkServerEndpoint.hpp
*  @date   2009/08/17
*/
#pragma once
#ifndef MOCKNETWORKSERVERENDPOINT_HPP
#define MOCKNETWORKSERVERENDPOINT_HPP

#include "NetworkServerEndpoint.h"

namespace
{
	class MockNetworkServerEndpoint : public INetworkServerEndpoint
	{

	public:

		MOCK_METHOD1( Update, void( float ) );
		MOCK_METHOD0( Initialize, void( ) );
		
	};
};

#endif