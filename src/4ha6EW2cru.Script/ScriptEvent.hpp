/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ScriptEvent.hpp
*  @date   2009/04/27
*/
#pragma once
#ifndef SCRIPTEVENT_HPP
#define SCRIPTEVENT_HPP

#include "Events/IEvent.hpp"
#include "Events/IEventData.hpp"
#include "Events/EventType.hpp"

#include <luabind/luabind.hpp>

namespace Script
{
  class IScriptEvent : public Events::IEvent
  {

  public:

    virtual ~IScriptEvent() { };


    /*! Returns the name of the Script Event
    *
    * @return (std::string)
    */
    virtual std::string GetEventName() const = 0;


    /*! Returns the number of parameters the event contains
    *
    * @return (int)
    */
    virtual int GetParameterCount() const = 0;


    /*! Executes the LUA Event Handler passing the internal parameters of the Event
    *
    * @param[in] luabind::object * handlerFunction
    * @return (void)
    */
    virtual void ExecuteHandler(const luabind::object& handlerFunction) const = 0;

  };


  template< int T0 = 0 >
  class ScriptEventT0 : public IScriptEvent
  {

  public:

    ScriptEventT0(const std::string& eventName)
      : m_eventName(eventName)
      , m_parameterCount(T0)
    {

    }


    /*! Returns the name of the Script Event
    *
    * @return (std::string)
    */
    inline std::string GetEventName() const { return m_eventName; };


    /*! Overrides the event type, so that the Script Components can forward all events to LUA
    *
    *  @return (Events::EventType)
    */
    inline Events::EventType GetEventType() const { return Events::EventTypes::ALL_EVENTS; };


    /*! Returns Event Data attached to the event, this will be null as the data is contained within the value functions GetValue1() & GetValue2()
    *
    *  @return (Events::IEventData*)
    */
    inline Events::IEventData* GetEventData() const { return 0; };


    /*! Returns the number of parameters the event contains
    *
    * @return (int)
    */
    int GetParameterCount() const { return m_parameterCount; };


    /*! Executes the LUA Event Handler passing the internal parameters of the Event
    *
    * @param[in] luabind::object * handlerFunction
    * @return (void)
    */
    virtual void ExecuteHandler(const luabind::object& handlerFunction) const
    {
      luabind::call_function< void >(handlerFunction, m_eventName);
    }

  protected:

    std::string m_eventName;
    int m_parameterCount;
  };


  template< class T1, int T0 = 1 >
  class ScriptEventT1 : public ScriptEventT0< T0 >
  {

  public:

    ScriptEventT1(const std::string& eventName, const T1& param1)
      : ScriptEventT0(eventName)
    {

    }


    /*! Returns Parameter 1 of the Event Data
    *
    * @return (T1)
    */
    inline T1 GetParam1() const { return m_param1; };


    /*! Executes the LUA Event Handler passing the internal parameters of the Event
    *
    * @param[in] luabind::object * handlerFunction
    * @return (void)
    */
    virtual void ExecuteHandler(const luabind::object& handlerFunction) const
    {
      luabind::call_function< void >(handlerFunction, m_eventName, m_param1);
    }

  protected:

    T1 m_param1;

  };

  template< class T1, class T2, int T0 = 2 >
  class ScriptEventT2 : public ScriptEventT1< T1, T0 >
  {

  public:

    ScriptEventT2(const std::string& eventName, const T1& param1, const T2& param2)
      : ScriptEventT1(eventName, param1)
      , m_param2(param2)
    {

    }

    /*! Returns Parameter 2 of the Event Data
    *
    * @return (T2)
    */
    inline T2 GetParam2() const { return m_param2; };


    /*! Executes the LUA Event Handler passing the internal parameters of the Event
    *
    * @param[in] luabind::object * handlerFunction
    * @return (void)
    */
    virtual void ExecuteHandler(const luabind::object& handlerFunction) const
    {
      luabind::call_function< void >(handlerFunction, m_eventName, m_param2);
    }

  protected:

    T2 m_param2;

  };
};

#endif
