/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ScriptUpdateDispatcher.h
*  @date   2009/11/08
*/
#pragma once
#ifndef SCRIPTUPDATEDISPATCHER_H
#define SCRIPTUPDATEDISPATCHER_H

#include "IScriptUpdateDispatcher.hpp"

#include "Export.hpp"

namespace Script
{
  /*! 
   *  Dispatches Update Calls to the Script
   */
  class GAMEAPI ScriptUpdateDispatcher : public IScriptUpdateDispatcher
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    ~ScriptUpdateDispatcher() { };


    /*! Default Constructor
    *
    * @return ()
    */
    ScriptUpdateDispatcher() { };


    /*! Destroys the Dispatcher
    *
    * @return (void)
    */
    void Destroy();


    /*! Registers an Update Handler to be called on each System Tick
    *
    * @param[in] IScriptFunctionHandler* handler
    * @return (void)
    */
    void RegisterUpdateHandler(IScriptFunctionHandler* handler);


    /*! Updates all registered Update Handlers
    *
    * @param[in] float deltaMilliseconds
    * @return (void)
    */
    void Update(float deltaMilliseconds);


    /*! UnRegisters an Update Handler from being called on each System Tick
    *
    * @param[in] IScriptFunctionHandler* handler
    * @return (void)
    */
    void UnRegisterUpdateHandler(IScriptFunctionHandler* handler);

  private:

    ScriptUpdateDispatcher(const ScriptUpdateDispatcher & copy) { };
    ScriptUpdateDispatcher & operator = (const ScriptUpdateDispatcher & copy) { return *this; };

    IScriptFunctionHandler::FunctionList m_updateHandlers;
    
  };
};

#endif