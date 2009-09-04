#include "SoundEventSystem.h"

#include "Logging/Logger.h"
#include "Maths/MathTools.hpp"
using namespace Maths;

using namespace FMOD;

namespace Sound
{
	void SoundEventSystem::Initialize( System* fmodSystem )
	{
		FMOD_RESULT result = EventSystem_Create( &m_eventSystem );

		if ( result != FMOD_OK )
		{
			Fatal( "Error creating FMOD event system" );
		}

		result = m_eventSystem->getSystemObject( &fmodSystem );

		if ( result != FMOD_OK )
		{
			Fatal( "Error getting the FMOD system object" );
		}

		result = m_eventSystem->init( 256, FMOD_INIT_NORMAL, 0);

		if ( result != FMOD_OK )
		{
			Fatal( "Error initializing the FMOD event system" );
		}

		result = m_eventSystem->load( "/data/sound/game.fev", 0, 0 );

		if ( result != FMOD_OK )
		{
			Fatal( "Couldn't load the game sound archive" );
		}
	}

	FMOD::Event* SoundEventSystem::TriggerEvent( const std::string& eventPath )
	{
		FMOD::Event* event = 0;
		FMOD_RESULT result = m_eventSystem->getEvent( eventPath.c_str( ), FMOD_EVENT_DEFAULT, &event );

		if ( result == FMOD_OK )
		{
			result = event->start( );
			m_activeSoundEvents.insert( std::make_pair( eventPath, event ) );
		}

		return event;
	}

	void SoundEventSystem::KeyOutEvent( const std::string& eventPath )
	{
		if ( m_activeSoundEvents.find( eventPath ) != m_activeSoundEvents.end( ) )
		{
			FMOD::Event* event = m_activeSoundEvents[ eventPath ];

			int numParameters = 0;
			event->getNumParameters( &numParameters );

			for ( int index = 0; index < numParameters; index++ )
			{
				FMOD::EventParameter* eventParameter = 0;
				event->getParameterByIndex( index, &eventParameter );
				eventParameter->keyOff( );
			}

			event->stop( );

			m_activeSoundEvents.erase( eventPath );
		}
	}

	void SoundEventSystem::SetListenerPosition( const Maths::MathVector3& position )
	{
		FMOD_VECTOR oldPosition, oldVelocity, oldForward, oldUp;

		m_eventSystem->get3DListenerAttributes( 0, &oldPosition, &oldVelocity, &oldForward, &oldUp );
		
		m_eventSystem->set3DListenerAttributes( 
			0, 
			&MathTools::AsFMODVector( position ), 
			&oldVelocity,
			&MathTools::AsFMODVector( MathVector3::Forward( ) ), 
			&MathTools::AsFMODVector( MathVector3::Up( ) ) 
			);
	}

	void SoundEventSystem::Destroy()
	{
		for( SoundEventList::iterator i = m_activeSoundEvents.begin( ); i != m_activeSoundEvents.end( ); )
		{
			( *i ).second->stop( );
			i = m_activeSoundEvents.erase( i );
		}

		m_eventSystem->release( );
	}

	void SoundEventSystem::Update( float deltaMilliseconds )
	{
		m_eventSystem->update( );
	}
}