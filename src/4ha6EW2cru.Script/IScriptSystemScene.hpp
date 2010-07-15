/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IScriptSystemScene.hpp
*  @date   2009/04/27
*/
#pragma once
#ifndef ISCRIPTSYSTEMSCENE_HPP
#define ISCRIPTSYSTEMSCENE_HPP

#include "System/ISystemScene.hpp"
#include "System/ISystemComponent.hpp"

extern "C" 
{
#  include <lua.h>
}

namespace Script
{
  /*!
   *  A Script System Scene 
   */
  class GAMEAPI IScriptSystemScene : public ISystemScene
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~IScriptSystemScene() { };


    /*! Unloads and Destroys a Script Component
     *
     * @param[in] const std::string & name
     * @return (void)
     */
    virtual void UnloadComponent(const std::string& name) = 0;


  };
};

#endif
