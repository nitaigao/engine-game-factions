/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockSystemManager.hpp
*  @date   2009/11/24
*/
#pragma once
#ifndef MOCKSYSTEMMANAGER_HPP
#define MOCKSYSTEMMANAGER_HPP

#include <gmock/gmock.h>

#include "System/ISystemManager.hpp"

namespace
{
	class MockSystemManager : public ISystemManager
	{

	public:

	
		MOCK_METHOD1( LoadSystem, ISystem*( const std::string& ) );
		MOCK_METHOD1( LoadSystems, void( bool ) );
		MOCK_METHOD2( RegisterSystem, void( const System::Queues::Queue&, ISystem* ) );
		MOCK_CONST_METHOD1( GetSystem, ISystem*( const System::Types::Type& ) );
		MOCK_METHOD0( InitializeAllSystems, void( ) );
		MOCK_CONST_METHOD1( HasSystem, bool( const System::Types::Type& ) );
		MOCK_METHOD1( Update, void( float ) );
		MOCK_METHOD0( Release, void( ) );
		MOCK_METHOD0( CreateWorld, State::IWorld*( ) );

		
	};
};

#endif