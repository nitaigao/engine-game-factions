/**/
#pragma once
#ifndef OSXCLOCK_H
#define OSXCLOCK_H

#include "IClock.hpp"

namespace Platform
{
	class GAMEAPI OSXClock : public IClock
	{

	public:

		~OSXClock( ) { };

		OSXClock( )
			: m_endFrameTime( 0 )
			, m_startFrameTime( 0 )
		{

		}

		float GetDeltaMilliseconds( );

    float GetTime( ) const;

	private:

		float m_endFrameTime;
		float m_startFrameTime;

	};
}

#endif
