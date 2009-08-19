/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockServiceManager.hpp
*  @date   2009/08/18
*/
#pragma once
#ifndef MOCKSERVICEMANAGER_HPP
#define MOCKSERVICEMANAGER_HPP

#include "Service/IServiceManager.h"

namespace
{
	class MockServiceManager : public Services::IServiceManager
	{

	public:

		MOCK_METHOD1( RegisterService, void( Services::IService* ) );
		MOCK_METHOD2( MessageAll, AnyType::AnyTypeMap( const System::Message&, AnyType::AnyTypeMap ) );
		MOCK_CONST_METHOD1( FindService, Services::IService*( System::Types::Type ) );
		
	};
};

#endif