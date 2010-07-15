/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ScriptFacadeManager.h
*  @date   2009/08/27
*/
#pragma once
#ifndef SCRIPTFACADEMANAGER_H
#define SCRIPTFACADEMANAGER_H

#include "IScriptFacadeManager.hpp"
#include "IScriptFacadeFactory.hpp"
#include "ILuaState.hpp"

namespace Script
{
  /*! 
   *  Manages all of the Facades exposed to the Lua Script Engine
   */
  class GAMEAPI ScriptFacadeManager : public IScriptFacadeManager
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    ~ScriptFacadeManager() { };


    /*! Default Constructor
    *
    * @return ()
    */
    ScriptFacadeManager(IScriptFacadeFactory* facadeFactory, ILuaState* state)
      : m_facadeFactory(facadeFactory)
      , m_state(state)
    {

    }


    /*! Initializes the Facade Manager with the given ScriptComponent
    *
    * @param[in] IScriptComponent *
    * @return (void)
    */
    void Initialize(ISystemComponent* scriptComponent);


    /*! Destroys each ScriptFacade
    *
    * @return (void)
    */
    void Destroy();

  private:

    ScriptFacadeManager(const ScriptFacadeManager & copy) { };
    ScriptFacadeManager & operator = (const ScriptFacadeManager & copy) { return *this; };

    IScriptFacadeFactory* m_facadeFactory;
    IScriptFacade::ScriptFacadeList m_facades;
    ILuaState* m_state;
    
  };
};

#endif