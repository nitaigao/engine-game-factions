/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockProgramOptions.hpp
*  @date   2009/11/24
*/
#pragma once
#ifndef MOCKPROGRAMOPTIONS_HPP
#define MOCKPROGRAMOPTIONS_HPP

#include <gmock/gmock.h>

#include "Platform/IProgramOptions.hpp"

namespace
{
	class MockProgramOptions : public Platform::IProgramOptions
	{

	public:

		MOCK_METHOD0( Initialize, void( ) );
		MOCK_CONST_METHOD1( HasOption, bool( const std::string& optionName ) );
		MOCK_CONST_METHOD1( GetOption, std::string( const std::string& optionName ) );

		
	};
};

#endif