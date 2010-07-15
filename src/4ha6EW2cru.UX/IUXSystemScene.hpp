/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IUXSystemScene.hpp
*  @date   2009/04/26
*/
#pragma once
#ifndef IUXSYSTEMSCENE_H
#define IUXSYSTEMSCENE_H

#include "System/ISystemScene.hpp"

namespace UX
{
  /*! 
   *  A scene specific to the UX System
   */
  class GAMEAPI IUXSystemScene : public ISystemScene
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~IUXSystemScene() { };

  };
};

#endif
