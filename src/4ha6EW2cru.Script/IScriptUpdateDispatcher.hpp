/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IScriptUpdateDispatcher.hpp
*  @date   2009/11/08
*/
#pragma once
#ifndef ISCRIPTUPDATEDISPATCHER_HPP
#define ISCRIPTUPDATEDISPATCHER_HPP

#include "IScriptFunctionHandler.hpp"

namespace Script
{
  /*! 
   *  Dispatches Update Calls to the Script
   */
  class IScriptUpdateDispatcher
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~IScriptUpdateDispatcher() { };


    /*! Destroys the Dispatcher
     *
     * @return (void)
     */
    virtual void Destroy() = 0;


    /*! Registers an Update Handler to be called on each System Tick
     *
     * @param[in] IScriptFunctionHandler* handler
     * @return (void)
     */
    virtual void RegisterUpdateHandler(IScriptFunctionHandler* handler) = 0;


    /*! Updates all registered Update Handlers
     *
     * @param[in] float deltaMilliseconds
     * @return (void)
     */
    virtual void Update(float deltaMilliseconds) = 0;


    /*! UnRegisters an Update Handler from being called on each System Tick
    *
    * @param[in] IScriptFunctionHandler* handler
    * @return (void)
    */
    virtual void UnRegisterUpdateHandler(IScriptFunctionHandler* handler) = 0;
    
  };
};

#endif