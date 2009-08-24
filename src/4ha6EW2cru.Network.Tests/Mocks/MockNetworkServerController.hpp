/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockNetworkServerController.hpp
*  @date   2009/08/16
*/
#pragma once
#ifndef MOCKNETWORKSERVERCONTROLLER_HPP
#define MOCKNETWORKSERVERCONTROLLER_HPP

#include "INetworkServerController.hpp"
using namespace Network;

#include "Maths/MathVector3.hpp"

#include <gmock/gmock.h>

namespace
{
	class MockNetworkServerController : public INetworkServerController
	{

	public:

		MOCK_METHOD0( Initialize, void( ) );
		MOCK_METHOD1( ClientConnected, void( const SystemAddress& ) );
		MOCK_METHOD2( CreateEntity, void( const std::string&, const std::string& ) );
		MOCK_METHOD1( DestroyEntity, void( const std::string& ) );
		MOCK_METHOD1( SendWorldUpdate, void( const SystemAddress& ) );
		MOCK_METHOD1( ClientDisconnected, void( const SystemAddress& ) );
		MOCK_METHOD2( SetEntityPosition, void( const std::string&, const Maths::MathVector3& ) );
		MOCK_METHOD3( MessageEntity, void( const std::string&, const System::MessageType&, AnyType::AnyTypeMap ) );
		MOCK_METHOD1( Update, void( float ) );
		
	};
};

#endif