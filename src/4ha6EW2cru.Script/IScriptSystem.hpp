/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IScriptSystem.hpp
*  @date   2009/04/27
*/
#pragma once
#ifndef ISCRIPTSYSTEM_HPP
#define ISCRIPTSYSTEM_HPP

#include "System/ISystem.hpp"

namespace Script
{
  /*!
   *  The Scripting System 
   */
  class GAMEAPI IScriptSystem : public ISystem
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~IScriptSystem() { };

  };
};

#endif
