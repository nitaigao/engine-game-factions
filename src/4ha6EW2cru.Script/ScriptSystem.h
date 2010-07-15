/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ScriptSystem.h
*  @date   2009/04/27
*/
#pragma once
#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H

#include "Service/IServiceManager.h"
#include "Configuration/IConfiguration.hpp"

#include "IScriptSystem.hpp"
#include "IScriptSystemScene.hpp"

namespace Script
{
  /*!
   *  The Scripting System 
   */
  class GAMEAPI ScriptSystem : public IScriptSystem, public Services::IService
  {

  public:

    /*! Default Destructor
    *
    *  @return ()
    */
    ~ScriptSystem( );


    /*! Default Constructor
    *
    *  @return ()
    */
    ScriptSystem( IScriptSystemScene* scene, IScriptSystemScene* auxScene, Services::IServiceManager* serviceManager )
      : m_scene( scene )
      , m_auxScene( auxScene )
      , m_serviceManager( serviceManager )
      , m_configuration( 0 )
    {

    }


    /*! Initializes the System
    *
    *  @return (void)
    */
    void Initialize( Configuration::IConfiguration* configuration );


    /*! Steps the System's internal data
    *
    *  @param[in] float deltaMilliseconds
    *  @return (void)
    */
    void Update( float deltaMilliseconds );


    /*! Releases internal data of the System
    *
    *  @return (System::Types::Type)
    */
    void Release( );


    /*! Messages the system with a command
    *
    * @param[in] const std::string & message
    * @param[in] AnyType::AnyTypeMap parameters
    * @return ( void )
    */
    AnyType::AnyTypeMap ProcessMessage( const System::MessageType& message, AnyType::AnyTypeMap parameters );


    /*! Returns the type of the System
    *
    *  @return (System::Types::Type)
    */
    inline System::Types::Type GetType( ) const { return System::Types::SCRIPT; };


    /*! Creates a System Scene
    *
    *  @return (ISystemScene*)
    */
    ISystemScene* CreateScene( );


    /*! Gets the System's Properties
    *
    *  @return (AnyTypeMap)
    */
    inline AnyType::AnyTypeMap GetAttributes( ) const { return m_attributes; };


    /*! Sets a System Property
    *
    *  @param[in] const std::string & name
    *  @param[in] AnyType value
    *  @return (void)
    */
    inline void SetAttribute( const std::string& name, AnyType value ) { };

  private:

    ScriptSystem( const ScriptSystem & copy ) { };
    ScriptSystem & operator = ( const ScriptSystem & copy ) { return *this; };

    AnyType::AnyTypeMap m_attributes;
    Configuration::IConfiguration* m_configuration;

    IScriptSystemScene* m_scene;
    IScriptSystemScene* m_auxScene;
    Services::IServiceManager* m_serviceManager;

  };
};

#endif
