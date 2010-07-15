/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ISoundFactory.hpp
*  @date   2009/08/26
*/
#pragma once
#ifndef ISOUNDFACTORY_HPP
#define ISOUNDFACTORY_HPP

#include "ISoundSystem.hpp"

namespace Sound
{
  /*! 
   *  A factory to create sound system objects
   */
  class ISoundFactory
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~ISoundFactory() { };


    /*! Creates a SoundSystem Object
     *
     * @return (ISoundSystem*)
     */
    virtual ISoundSystem* CreateSoundSystem() = 0;
    
  };
};

#endif