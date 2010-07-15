/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IUXSystemComponent.hpp
*  @date   2009/04/26
*/
#pragma once
#ifndef IUXSYSTEMCOMPONENT_H
#define IUXSYSTEMCOMPONENT_H

#include "System/ISystemComponent.hpp"

#include "IScriptFunctionHandler.hpp"
#include <luabind/luabind.hpp>

namespace UX
{
  /*! 
  *  A UX System Scene Component
  */
  class GAMEAPI IUXSystemComponent : public ISystemComponent
  {

  public:

    typedef std::deque<IUXSystemComponent*> UXSystemComponentList;

    virtual ~IUXSystemComponent() { };


    /*! Registers a Script Function to receive Events
    *
    * @param[in] const std::string & eventType
    * @param[in] luabind::object handlerFunction
    * @return (void)
    */
    virtual void RegisterEventHandler(const std::string& eventType, const luabind::object& handlerFunction) = 0;


    /*! Unregisters a Script Function from receiving Events
    *
    * @param[in] const std::string & eventType
    * @param[in] luabind::object handlerFunction
    * @return (void)
    */
    virtual void UnregisterEventHandler(const std::string& eventType, const luabind::object& handlerFunction) = 0;

  };
};

#endif
