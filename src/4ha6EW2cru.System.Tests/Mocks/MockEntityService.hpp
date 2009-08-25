/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockEntityService.hpp
*  @date   2009/08/25
*/
#pragma once
#ifndef MOCKENTITYSERVICE_HPP
#define MOCKENTITYSERVICE_HPP

#include <gmock/gmock.h>

#include "State/IEntityService.hpp"

namespace
{
	class MockEntityService : public IEntityService
	{

	public:

		MOCK_CONST_METHOD0( GetType, System::Types::Type( ) );
		MOCK_METHOD2( ProcessMessage, AnyType::AnyTypeMap( const System::MessageType&, AnyType::AnyTypeMap ) );
		
	};
};

#endif