/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ScriptFunctionHandler.hpp
*  @date   2009/04/28
*/
#pragma once
#ifndef SCRIPTFUNCTIONHANDLER_H
#define SCRIPTFUNCTIONHANDLER_H

#include "IScriptFunctionHandler.hpp"
#include "Export.hpp"

namespace Script
{
  /*!
   *  A Container for handling Updates or Events from the Game 
   */
  class GAMEAPI ScriptFunctionHandler : public IScriptFunctionHandler
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    ~ScriptFunctionHandler( ) { };

    /*! Default Constructor
     *
     *  @return ()
     */
    ScriptFunctionHandler( const luabind::object& functionHandler )
      : m_functionHandler( functionHandler )
      , m_isMarkedForDeletion( false )
    {

    }


    /*! Marks the Handler for deletion on the next UX Update or Event Tick
     *
     *  @return (void)
     */
    inline void MarkForDeletion( ) { m_isMarkedForDeletion = true; };


    /*! Returns whether or not the handler is marked for deletion on the next UX Update or Event Tick
     *
     *  @return (bool)
     */
    inline bool IsMarkedForDeletion( ) const { return m_isMarkedForDeletion; };


    /*! Calls a Function Handler with the given parameters
    *
    * @param[in] float deltaMilliseconds
    * @return ( void )
    */
    void CallFunction( float deltaMilliseconds );


    /*! Calls the Function Handler with the given parameters
    *
    * @param[in] AnyType::AnyTypeMap parameters
    * @return ( void )
    */
    void CallFunction( AnyType::AnyTypeMap parameters );


    /*! Calls the Function Handler with the given parameters
     *
     * @param[in] const std::string & eventType
     * @param[in] Events::IEventData * eventData
     * @return ( void )
     */
    void CallFunction( const std::string& eventType, Events::IEventData* eventData );


    void CallFunction( const System::MessageType& message, AnyType::AnyTypeMap& parameters );


    bool Compare( IScriptFunctionHandler* input )
    {
      return static_cast< ScriptFunctionHandler* >( input )->m_functionHandler == m_functionHandler;
    }


  private:

    bool m_isMarkedForDeletion;
    luabind::object m_functionHandler;

    ScriptFunctionHandler( const ScriptFunctionHandler & copy ) { };
    ScriptFunctionHandler & operator = ( const ScriptFunctionHandler & copy ) { return *this; };

  };
};

#endif
