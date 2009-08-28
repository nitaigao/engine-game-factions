/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockScriptFacadeFactory.hpp
*  @date   2009/08/27
*/
#pragma once
#ifndef MOCKSCRIPTFACADEFACTORY_HPP
#define MOCKSCRIPTFACADEFACTORY_HPP

#include <gmock/gmock.h>

#include "IScriptFacadeFactory.hpp"

namespace
{
	class MockScriptFacadeFactory : public IScriptFacadeFactory
	{

	public:

		MOCK_METHOD2( CreateScriptFacade, IScriptFacade*( IScriptFacade::FacadeType, IScriptComponent* ) );
		
	};
};

#endif