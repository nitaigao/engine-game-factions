/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IScriptComponent.hpp
*  @date   2009/04/27
*/
#pragma once
#ifndef ISCRIPTCOMPONENT_HPP
#define ISCRIPTCOMPONENT_HPP

#include "System/ISystemComponent.hpp"
#include "IScriptFunctionHandler.hpp"

#include <luabind/luabind.hpp>

extern "C" 
{
#  include <lua.h>
#  include <lualib.h>
}

namespace Script
{
  /*!
   *  A Script System Component 
   */
  class GAMEAPI IScriptComponent : public ISystemComponent
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~IScriptComponent() { };


    /*! Registers a Script Function to receive Events
     *
     * @param[in] const std::string & eventType
     * @param[in] luabind::object handlerFunction
     * @return (void)
     */
    virtual void RegisterEventHandler(const std::string& eventType, const luabind::object& handlerFunction) = 0;


    /*!  Registers an LUA function to receive messages
    *
    *  @param[in] luabind::object function
    *  @return (void)
    */
    virtual void SubscribeMessage(const System::MessageType& message, const luabind::object& function) = 0;


    /*! UnRegisters an LUA function from receiving messages
    *
    *  @param[in] luabind::object function
    *  @return (void)
    */
    virtual void UnSubscribeMessage(const System::MessageType& message,  const luabind::object& function) = 0;


    /*!  Registers an LUA function to be included in the Game Update Loop
    *
    *  @param[in] luabind::object function
    *  @return (void)
    */
    virtual void RegisterUpdateHandler(const luabind::object& function) = 0;


    /*! UnRegisters an LUA function from being included in the Game Update Loop
    *
    *  @param[in] luabind::object function
    *  @return (void)
    */
    virtual void UnRegisterUpdateHandler(const luabind::object& function) = 0;

  };
};

#endif
