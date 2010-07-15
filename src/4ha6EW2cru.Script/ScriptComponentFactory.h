/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ScriptComponentFactory.h
*  @date   2009/08/27
*/
#pragma once
#ifndef SCRIPTCOMPONENTFACTORY_H
#define SCRIPTCOMPONENTFACTORY_H

#include "IScriptComponentFactory.hpp"
#include "IScriptFacadeFactory.hpp"
#include "ILuaState.hpp"

#include "Events/IEventManager.hpp"

namespace Script
{
  /*! 
   *  Creates Script Components
   */
  class GAMEAPI ScriptComponentFactory : public IScriptComponentFactory
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    ~ScriptComponentFactory();


    /*! Default Constructor
    *
    * @return ()
    */
    ScriptComponentFactory(ILuaState* masterState, Events::IEventManager* eventManager, IScriptFacadeFactory* facadeFactory)
      : m_masterState(masterState)
      , m_eventManager(eventManager)
      , m_facadeFactory(facadeFactory)
    {

    }


    /*! Creates a Script Component
    *
    * @param[in] const std::string & name
    * @param[in] const std::string & type
    * @return (IScriptComponent*)
    */
    IScriptComponent* CreateComponent(const std::string& name, const std::string& type);

  private:

    ScriptComponentFactory(const ScriptComponentFactory & copy) { };
    ScriptComponentFactory & operator = (const ScriptComponentFactory & copy) { return *this; };

    ILuaState* m_masterState;
    Events::IEventManager* m_eventManager;
    IScriptFacadeFactory* m_facadeFactory;
    
  };
};

#endif