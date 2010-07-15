/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   SoundEventSystem.h
*  @date   2009/08/26
*/
#pragma once
#ifndef SOUNDEVENTSYSTEM_H
#define SOUNDEVENTSYSTEM_H

#include "ISoundEventSystem.hpp"

namespace Sound
{
  /*! 
   *  Manages the control of Sound Events
   */
  class GAMEAPI SoundEventSystem : public ISoundEventSystem
  {

  public:

    typedef std::map< std::string, FMOD::Event* > SoundEventList;

    /*! Default Destructor
     *
     *  @return ()
     */
    ~SoundEventSystem( ) { };


    /*! Default Constructor
    *
    * @return (  )
    */
    SoundEventSystem( )
      : m_eventSystem( )
    {

    }


    /*! Initializes the Event System
    *
    * @return ( void )
    */
    void Initialize( FMOD::System* fmodSystem );


    /*! Triggers a Sound Event
    *
    * @param[in] const std::string & eventPath
    * @return ( FMOD::Event* )
    */
    FMOD::Event* TriggerEvent( const std::string& eventPath );  


    /*! Keys out a Sound Event
    *
    * @param[in] const std::string & eventPath
    * @return ( void )
    */
    void KeyOutEvent( const std::string& eventPath );  


    /*! Sets the Position the Speakers would be listening from
    *
    * @param[in] const Maths::MathVector3 & position
    * @return ( void )
    */
    void SetListenerPosition( const Maths::MathVector3& position );


    /*! Destroys the Event System
    *
    * @return ( void )
    */
    void Destroy( );


    /*! Updates the Event System
    *
    * @param[in] float deltaMilliseconds
    * @return ( void )
    */
    void Update( float deltaMilliseconds );

  private:

    SoundEventSystem( const SoundEventSystem & copy ) { };
    SoundEventSystem & operator = ( const SoundEventSystem & copy ) { return *this; };

    FMOD::EventSystem* m_eventSystem;
    SoundEventList m_activeSoundEvents;
    
  };
};

#endif