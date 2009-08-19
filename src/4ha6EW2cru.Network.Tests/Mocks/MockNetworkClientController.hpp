/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockNetworkClientController.hpp
*  @date   2009/08/19
*/
#pragma once
#ifndef MOCKNETWORKCLIENTCONTROLLER_HPP
#define MOCKNETWORKCLIENTCONTROLLER_HPP

#include <gmock/gmock.h>

#include "INetworkClientController.hpp"

namespace
{
	class MockNetworkClientController : public INetworkClientController
	{

	public:

		MOCK_METHOD0( Initialize, void( ) );
		MOCK_METHOD1( SelectCharacter, void( const std::string& ) );
		
	};
};

#endif