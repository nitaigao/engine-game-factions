/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IScriptFunctionHandler.hpp
*  @date   2009/04/28
*/
#pragma once
#ifndef ISCRIPTGENERICHANDLER_HPP
#define ISCRIPTGENERICHANDLER_HPP

#include <luabind/luabind.hpp>
#include <deque>

#include "Events/IEvent.hpp"
#include "System/SystemType.hpp"
#include "System/AnyType.hpp"

namespace Script
{
  /*!
   *  A Container for handling Updates or Events from the Game  
   */
  class IScriptFunctionHandler
  {

  public:

    typedef std::deque<IScriptFunctionHandler*> FunctionList;
    typedef std::multimap<unsigned int, IScriptFunctionHandler*> FunctionMap;

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~IScriptFunctionHandler() { };


    /*! Marks the Handler for deletion on the next UX Update or Event Tick
    *
    *  @return (void)
    */
    virtual void MarkForDeletion() = 0;


    /*! Returns whether or not the handler is marked for deletion on the next UX Update or Event Tick
    *
    *  @return (bool)
    */
    virtual bool IsMarkedForDeletion() const = 0;


    /*! Calls a Function Handler with the given parameters
     *
     * @param[in] float deltaMilliseconds
     * @return (void)
     */
    virtual void CallFunction(float deltaMilliseconds) = 0;


    /*! Calls the Function Handler with the given parameters
     *
     * @param[in] AnyType::AnyTypeMap parameters
     * @return (void)
     */
    virtual void CallFunction(AnyType::AnyTypeMap parameters) = 0;


    /*! Calls the Function Handler with the given parameters
     *
     * @param[in] const std::string & eventType
     * @param[in] Events::IEventData * eventData
     * @return (void)
     */
    virtual void CallFunction(const std::string& eventType, Events::IEventData* eventData) = 0;

    virtual void CallFunction(const System::MessageType& message, AnyType::AnyTypeMap& parameters) = 0;


    virtual bool Compare(IScriptFunctionHandler* input) = 0;
  };
};

#endif
