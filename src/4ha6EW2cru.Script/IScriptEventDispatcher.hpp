/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IScriptEventDispatcher.h
*  @date   2009/11/08
*/
#pragma once
#ifndef ISCRIPTEVENTDISPATCHER_H
#define ISCRIPTEVENTDISPATCHER_H

#include "IScriptFunctionHandler.hpp"

#include "Export.hpp"

namespace Script
{
  /*! 
   *  Dispatched Events to Script
   */
  class GAMEAPI IScriptEventDispatcher
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~IScriptEventDispatcher( ) { };


    /*! Registers a Script Function to receive Events
    *
    * @param[in] const std::string & eventType
    * @param[in] IScriptFunctionHandler * eventHandler
    * @return ( void )
    */
    virtual void RegisterEventHandler( const std::string& eventType, Script::IScriptFunctionHandler* eventHandler ) = 0;


    /*! Unregisters a Script Function from receiving Events
    *
    * @param[in] const std::string & eventType
    * @param[in] IScriptFunctionHandler * eventHandler
    * @return ( void )
    */
    virtual void UnregisterEventHandler( const std::string& eventType, Script::IScriptFunctionHandler* eventHandler ) = 0;
    

    /*! Handles incoming Events
     *
     * @param[in] const Events::IEvent * event
     * @return ( void )
     */
    virtual void EventHandler( const Events::IEvent* event ) = 0;
  };
};

#endif