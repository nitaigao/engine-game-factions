/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ISoundScene.hpp
*  @date   2009/04/27
*/
#pragma once
#ifndef ISOUNDSCENE_HPP
#define ISOUNDSCENE_HPP

#include "ISoundSystem.hpp"
#include "System/ISystemScene.hpp"

namespace Sound
{
  /*!
   *  A Sound Scene 
   */
  class GAMEAPI ISoundScene : public ISystemScene
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~ISoundScene() { };

    virtual ISoundSystem* GetSoundSystem() = 0;

    

  };
};

#endif
