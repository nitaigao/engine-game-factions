/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockEventManager.hpp
*  @date   2009/08/27
*/
#pragma once
#ifndef MOCKEVENTMANAGER_HPP
#define MOCKEVENTMANAGER_HPP

#include <gmock/gmock.h>

#include "Events/IEventManager.hpp"

namespace
{
	class MockEventManager : public Events::IEventManager
	{

	public:
		
		MOCK_METHOD1( QueueEvent, void( const Events::IEvent* event ) );
		MOCK_METHOD1( TriggerEvent, void( const Events::IEvent* event ) );
		MOCK_METHOD1( Update, void( float ) );
		MOCK_METHOD1( AddEventListener, void( Events::IEventListener* ) );
		MOCK_METHOD1( RemoveEventListener, void( Events::IEventListener* ) );

	};
};

#endif