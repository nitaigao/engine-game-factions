/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockService.h
*  @date   2009/08/22
*/
#pragma once
#ifndef MOCKSERVICE_H
#define MOCKSERVICE_H

#include <gmock/gmock.h>

#include "Service/IService.hpp"

namespace
{
	class MockService : public Services::IService
	{

	public:

		MOCK_CONST_METHOD0( GetType, System::Types::Type( ) );
		MOCK_METHOD2( ProcessMessage, AnyType::AnyTypeMap( const System::MessageType&, AnyType::AnyTypeMap ) );
		
	};
};

#endif