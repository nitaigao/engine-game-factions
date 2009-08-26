/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockSoundEventSystem.hpp
*  @date   2009/08/26
*/
#pragma once
#ifndef MOCKSOUNDEVENTSYSTEM_HPP
#define MOCKSOUNDEVENTSYSTEM_HPP

#include <gmock/gmock.h>

#include "ISoundEventSystem.hpp"

namespace
{
	class MockSoundEventSystem : public ISoundEventSystem
	{

	public:

		MOCK_METHOD1( Initialize, void( FMOD::System* ) );
		MOCK_METHOD1( TriggerEvent, FMOD::Event*( const std::string& ) );
		MOCK_METHOD1( KeyOutEvent, void( const std::string& ) );
		MOCK_METHOD1( SetListenerPosition, void( const Maths::MathVector3& ) );
		MOCK_METHOD0( Destroy, void( ) );
		MOCK_METHOD1( Update, void( float ) );
		
	};
};

#endif