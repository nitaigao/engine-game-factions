/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ScriptSystemScene.h
*  @date   2009/04/27
*/
#pragma once
#ifndef SCRIPTSYSTEMSCENE_H
#define SCRIPTSYSTEMSCENE_H

#include <luabind/luabind.hpp>

#include "Configuration/IConfiguration.hpp"
#include "Events/IEvent.hpp"
#include "Service/IServiceManager.h"

#include "ScriptConfiguration.h"
#include "IScriptSystemScene.hpp"
#include "IScriptComponentFactory.hpp"
#include "IScriptComponent.hpp"
#include "ILuaState.hpp"

namespace Script
{
  /*!
   *  A Script System Scene 
   */
  class GAMEAPI ScriptSystemScene : public IScriptSystemScene
  {
    typedef std::pair<Events::EventType, luabind::object> EventHandler;
    typedef std::deque<EventHandler> EventHandlerList;
    typedef std::map<std::string, IScriptComponent*> ScriptComponentList;

  public:

    /*! Default Destructor
    *
    *  @return ()
    */
    ~ScriptSystemScene();

    
    /*! Default Constructor
     *
     *  @return ()
     */
    ScriptSystemScene(Configuration::IConfiguration* configuration, IScriptComponentFactory* componentFactory, 
      ILuaState* masterState,  Services::IServiceManager* serviceManager)
      : m_configuration(configuration)
      , m_componentFactory(componentFactory)
      , m_masterState(masterState)
      , m_serviceManager(serviceManager)
      , m_scriptConfiguration(0)
      , m_eventHandlers(new EventHandlerList())
    {

    }


    /*! Initializes the System Scene
    *
    *  @return (void)
    */
    void Initialize();

    /*! Steps internal data of the SystemScene
    *
    *  @param[in] float deltaMilliseconds
    *  @return (void)
    */
    inline void Update(float deltaMilliseconds);


    /*! Destroys the System Scene
    *
    *  @return (void)
    */
    inline void Destroy();


    /*! Creates a SystemComponent specific to the SystemScene
    *
    *  @param[in] const std::string & name
    *  @param[in] const std::string & type
    *  @return (ISystemComponent*)
    */
    ISystemComponent* CreateComponent(const std::string& name, const std::string& type);


    /*! Destroys a SystemComponent created by the SystemScene
    *
    *  @param[in] ISystemComponent * component
    *  @return (void)
    */
    void DestroyComponent(ISystemComponent* component);


    /*! Gets the System::Types::Type of the SystemScene
    *
    *  @return (System::Types::Type)
    */
    inline System::Types::Type GetType() const { return System::Types::SCRIPT; };


    /*! Unloads and Destroys a Script Component
    *
    * @param[in] const std::string & name
    * @return (void)
    */
    void UnloadComponent(const std::string& name);

  private:

    ScriptSystemScene() { };
    ScriptSystemScene(const ScriptSystemScene & copy) { };
    ScriptSystemScene & operator = (const ScriptSystemScene & copy) { return *this; };

    ILuaState* m_masterState;
    Configuration::IConfiguration* m_configuration;
    IScriptComponentFactory* m_componentFactory;
    Services::IServiceManager* m_serviceManager;

    ScriptConfiguration* m_scriptConfiguration;
    ScriptComponentList m_components;
    EventHandlerList* m_eventHandlers;

  };
};

#endif
