/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ILuaState.hpp
*  @date   2009/08/27
*/
#pragma once
#ifndef ILUASTATE_HPP
#define ILUASTATE_HPP

#include "Export.hpp"
#include <luabind/luabind.hpp>

namespace Script
{
  /*! 
   *  The Interface to the LUA Script Engine
   */
  class GAMEAPI ILuaState
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~ILuaState() { };


    /*! Initializes a new LuaState 
    *
    * @return (void)
    */
    virtual void Initialize() = 0;


    /*! Destroys the lua_State
     *
     * @return (void)
     */
    virtual void Destroy() = 0;


    /*! Creates a Child LuaState
     *
     * @return (ILuaState*)
     */
    virtual ILuaState* CreateChild() = 0;


    /*! Registers Types for use in the LuaState Script
     *
     * @param[in] luabind::scope
     * @return (void)
     */
    virtual void RegisterTypes(const luabind::scope& classScope) = 0;


    /*! Loads a Script File from the FileSystem
     *
     * @param[in] const std::string & scriptPath
     * @return (void)
     */
    virtual void LoadScript(const std::string& scriptPath) = 0; 


    /*! Executes this Script State
     *
     * @return (void)
     */
    virtual void Execute() = 0;


    /*! Runs a new Parse over a Script
     *
     * @return (void)
     */
    virtual void ReParse() = 0;


    /*! Executes the given string as Lua code
     *
     * @param[in] const std::string & scriptString
     * @return (void)
     */
    virtual void ExecuteString(const std::string& scriptString) = 0;
    
  };
};

#endif