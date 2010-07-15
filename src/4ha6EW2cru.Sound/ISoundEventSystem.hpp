/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ISoundEventSystem.hpp
*  @date   2009/08/26
*/
#pragma once
#ifndef ISOUNDEVENTSYSTEM_HPP
#define ISOUNDEVENTSYSTEM_HPP

#include <fmod.hpp>
#include <fmod_event.hpp>

#include "Maths/MathVector3.hpp"

#include "Export.hpp"

namespace Sound
{
  /*! 
   *  Manages the control of Sound Events
   */
  class GAMEAPI ISoundEventSystem
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~ISoundEventSystem() { };


    /*! Initializes the Event System
     *
     * @return (void)
     */
    virtual void Initialize(FMOD::System* fmodSystem) = 0;


    /*! Triggers a Sound Event
     *
     * @param[in] const std::string & eventPath
     * @return (FMOD::Event*)
     */
    virtual FMOD::Event* TriggerEvent(const std::string& eventPath) = 0;    


    /*! Keys out a Sound Event
    *
    * @param[in] const std::string & eventPath
    * @return (void)
    */
    virtual void KeyOutEvent(const std::string& eventPath) = 0;  


    /*! Sets the Position the Speakers would be listening from
     *
     * @param[in] const Maths::MathVector3 & position
     * @return (void)
     */
    virtual void SetListenerPosition(const Maths::MathVector3& position) = 0;


    /*! Destroys the Event System
     *
     * @return (void)
     */
    virtual void Destroy() = 0;


    /*! Updates the Event System
     *
     * @param[in] float deltaMilliseconds
     * @return (void)
     */
    virtual void Update(float deltaMilliseconds) = 0;
  };
};

#endif