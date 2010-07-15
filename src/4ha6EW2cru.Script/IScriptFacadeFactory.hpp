/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IScriptFacadeFactory.hpp
*  @date   2009/08/27
*/
#pragma once
#ifndef ISCRIPTFACADEFACTORY_HPP
#define ISCRIPTFACADEFACTORY_HPP

#include "System/SystemType.hpp"

#include "IScriptFacade.hpp"
#include "IScriptComponent.hpp"
#include "ILuaState.hpp"

#include "Export.hpp"

namespace Script
{
  /*! 
   *  Create ScriptFacade's
   */
  class GAMEAPI IScriptFacadeFactory
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~IScriptFacadeFactory() { };


    /*! Creates a ScriptFacade of the given type
     *
     * @param[in] IScriptFacade::FacadeType
     * @return (IScriptFacade*)
     */
    virtual IScriptFacade* CreateScriptFacade(IScriptFacade::FacadeType facadeType, ISystemComponent* component, ILuaState* state) = 0;
    
  };
};

#endif