/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IScriptFacadeManager.hpp
*  @date   2009/08/27
*/
#pragma once
#ifndef ISCRIPTFACADEMANAGER_HPP
#define ISCRIPTFACADEMANAGER_HPP

#include "IScriptComponent.hpp"

#include "Export.hpp"

namespace Script
{
  /*! 
   *  Manages the facades Exposed to the Lua Script Engine
   */
  class GAMEAPI IScriptFacadeManager
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~IScriptFacadeManager( ) { };


    /*! Initializes the Facade Manager with the given ScriptComponent
     *
     * @param[in] IScriptComponent *
     * @return ( void )
     */
    virtual void Initialize( ISystemComponent* scriptComponent ) = 0;


    /*! Destroys each ScriptFacade
     *
     * @return ( void )
     */
    virtual void Destroy( ) = 0;
    
  };
};

#endif