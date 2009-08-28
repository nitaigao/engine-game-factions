/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockScriptFacade.hpp
*  @date   2009/08/27
*/
#pragma once
#ifndef MOCKSCRIPTFACADE_HPP
#define MOCKSCRIPTFACADE_HPP

#include <gmock/gmock.h>

#include "IScriptFacade.hpp"

namespace
{
	class MockScriptFacade : public IScriptFacade
	{

	public:

		MOCK_METHOD0( Initialize, void( ) );
		MOCK_METHOD0( GetName, std::string( ) );

		
	};
};

#endif