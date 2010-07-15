#include <gtest/gtest.h>
using namespace testing;

#include "SoundSystemComponent.h"
using namespace Sound;

#include "Mocks/MockSoundEventSystem.hpp"

#include "Maths/MathVector3.hpp"
using namespace Maths;

class SoundSystemComponent_Tests : public TestHarness< SoundSystemComponent >
{

protected:

  std::string m_name;
  MockSoundEventSystem* m_eventSystem;

  void EstablishContext( )
  {
    m_name = "test";
    m_eventSystem = new MockSoundEventSystem( );
  }

  void DestroyContext( )
  {
    delete m_eventSystem;
  }

  SoundSystemComponent* CreateSubject( )
  {
    return new SoundSystemComponent( m_name, m_eventSystem );
  }
};

TEST_F( SoundSystemComponent_Tests, should_play_a_sound )
{
  std::string soundEvent = "/events/dosomething";
  EXPECT_CALL( *m_eventSystem, TriggerEvent( soundEvent) );

  AnyType::AnyTypeMap parameters;
  parameters[ System::Parameters::SoundEventPath ] = soundEvent;

  m_subject->Initialize( );
  m_subject->Observe( 0, System::Messages::TriggerSoundEvent, parameters );
}

TEST_F( SoundSystemComponent_Tests, should_only_play_a_sound_once )
{
  std::string soundEvent = "/events/dosomething";
  EXPECT_CALL( *m_eventSystem, TriggerEvent( soundEvent) ).Times( 1 );

  AnyType::AnyTypeMap parameters;
  parameters[ System::Parameters::SoundEventPath ] = soundEvent;

  m_subject->Observe( 0, System::Messages::TriggerSoundEvent, parameters );
  m_subject->Observe( 0, System::Messages::TriggerSoundEvent, parameters );
}

TEST_F( SoundSystemComponent_Tests, should_not_stop_a_sound_if_it_hasnt_been_requested )
{
  std::string soundEvent = "/events/dosomething";
  EXPECT_CALL( *m_eventSystem, KeyOutEvent( soundEvent) ).Times( 0 );

  AnyType::AnyTypeMap parameters;
  parameters[ System::Parameters::SoundEventPath ] = soundEvent;

  m_subject->Observe( 0, System::Messages::KeyOutSoundEvent, parameters );
}

TEST_F( SoundSystemComponent_Tests, should_stop_a_sound_if_it_has_been_requested )
{
  std::string soundEvent = "/events/dosomething";
  EXPECT_CALL( *m_eventSystem, KeyOutEvent( soundEvent) );

  AnyType::AnyTypeMap parameters;
  parameters[ System::Parameters::SoundEventPath ] = soundEvent;

  m_subject->Observe( 0, System::Messages::TriggerSoundEvent, parameters );
  m_subject->Observe( 0, System::Messages::KeyOutSoundEvent, parameters );
}

TEST_F( SoundSystemComponent_Tests, should_not_stop_a_sound_unless_the_request_count_has_reached_zero )
{
  std::string soundEvent = "/events/dosomething";
  EXPECT_CALL( *m_eventSystem, KeyOutEvent( soundEvent) ).Times( 0 );

  AnyType::AnyTypeMap parameters;
  parameters[ System::Parameters::SoundEventPath ] = soundEvent;

  m_subject->Observe( 0, System::Messages::TriggerSoundEvent, parameters );
  m_subject->Observe( 0, System::Messages::TriggerSoundEvent, parameters );

  m_subject->Observe( 0, System::Messages::KeyOutSoundEvent, parameters );
}


TEST_F( SoundSystemComponent_Tests, should_stop_a_sound_if_the_request_count_has_reached_zero )
{
  std::string soundEvent = "/events/dosomething";
  EXPECT_CALL( *m_eventSystem, KeyOutEvent( soundEvent) );

  AnyType::AnyTypeMap parameters;
  parameters[ System::Parameters::SoundEventPath ] = soundEvent;

  m_subject->Observe( 0, System::Messages::TriggerSoundEvent, parameters );
  m_subject->Observe( 0, System::Messages::TriggerSoundEvent, parameters );

  m_subject->Observe( 0, System::Messages::KeyOutSoundEvent, parameters );
  m_subject->Observe( 0, System::Messages::KeyOutSoundEvent, parameters );
}

TEST_F( SoundSystemComponent_Tests, should_set_the_listener_position )
{
  MathVector3 position = MathVector3::Forward( );
  EXPECT_CALL( *m_eventSystem, SetListenerPosition( position ) );

  AnyType::AnyTypeMap parameters;
  parameters[ System::Attributes::Position ] = position;

  m_subject->Observe( 0, System::Messages::SetPlayerPosition, parameters );
}