/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockWorld.hpp
*  @date   2009/08/14
*/
#pragma once
#ifndef MOCKWORLD_HPP
#define MOCKWORLD_HPP


#include <gmock/gmock.h>
#include "State/IWorld.hpp"

namespace
{
	class MockWorld : public IWorld
	{

	public:


		MOCK_METHOD0( Initialize, void( ) );
		MOCK_METHOD1( CreateEntity, IWorldEntity*( const std::string& ) );
		MOCK_METHOD3( CreateEntity, IWorldEntity*( const std::string&, const std::string&, const std::string& ) );
		MOCK_METHOD1( DestroyEntity, void( const std::string& ) );
		MOCK_METHOD1( AddSystemScene, void( ISystemScene* systemScene ) );
		MOCK_CONST_METHOD0( GetSystemScenes, const ISystemScene::SystemSceneMap&( ) );
		MOCK_METHOD1( Update, void( float ) );
		MOCK_METHOD0( Clear, void( ) );
		MOCK_METHOD0( Destroy, void( ) );
		MOCK_METHOD1( LoadLevel, void( const std::string& ) );
		MOCK_METHOD1( Serialize, void( IO::IStream* ) );
		MOCK_METHOD1( DeSerialize, void( IO::IStream* ) );
		
	};
};

#endif