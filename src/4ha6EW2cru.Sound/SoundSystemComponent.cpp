#include "precompiled.h"

#include "SoundSystemComponent.h"

#include "Maths/MathTools.hpp"
using namespace Maths;

namespace Sound
{
	AnyType SoundSystemComponent::Observe( const ISubject* subject, const System::MessageType& message, AnyType::AnyTypeMap parameters )
	{
		if( message == System::Messages::TriggerSoundEvent  )
		{
			std::string eventPath = parameters[ System::Parameters::SoundEventPath ].As< std::string >( );

			if ( m_triggerRequests.find( eventPath ) == m_triggerRequests.end( ) )
			{
				FMOD::Event* event = m_eventSystem->TriggerEvent( eventPath );
				m_activeEvents.insert( std::make_pair( eventPath, event ) );

				if ( m_attributes.find( System::Attributes::Position ) != m_attributes.end( ) )
				{
					this->Observe( 0, System::Messages::SetPosition, m_attributes );
				}
			}

			m_triggerRequests.insert( eventPath );
		}

		if ( message == System::Messages::KeyOutSoundEvent )
		{
			std::string eventPath = parameters[ System::Parameters::SoundEventPath ].As< std::string >( );

			if ( m_triggerRequests.find( eventPath ) != m_triggerRequests.end( ) )
			{
				m_triggerRequests.erase( m_triggerRequests.find( eventPath ) );

				if ( m_triggerRequests.find( eventPath ) == m_triggerRequests.end( ) )
				{
					m_activeEvents.erase( eventPath );
					m_eventSystem->KeyOutEvent( eventPath );
				}
			}
		}

		if ( message == System::Messages::SetPosition )
		{
			m_attributes[ System::Attributes::Position ] = parameters[ System::Attributes::Position ].As< MathVector3 >( );

			for ( SoundEventMap::iterator i = m_activeEvents.begin( ); i != m_activeEvents.end( ); ++i )
			{
				FMOD_VECTOR position, velocity;

				( *i ).second->get3DAttributes( &position, &velocity );
				( *i ).second->set3DAttributes( &MathTools::AsFMODVector( parameters[ System::Attributes::Position ].As< MathVector3 >( ) ), &velocity );
			}
		}

		if ( message == System::Messages::SetOrientation )
		{
			m_attributes[ System::Attributes::Orientation ] = parameters[ System::Attributes::Orientation ].As< MathQuaternion >( );
		}

		if ( message == System::Messages::SetPlayerPosition )
		{
			m_eventSystem->SetListenerPosition( parameters[ System::Attributes::Position ].As< MathVector3 >( ) );
		}

		return true;
	}

	void SoundSystemComponent::Destroy( )
	{
		for ( SoundEventMap::iterator i = m_activeEvents.begin( ); i != m_activeEvents.end( ); )
		{
			m_eventSystem->KeyOutEvent( ( *i ).first );
			i = m_activeEvents.erase( i );
		}
	}
}