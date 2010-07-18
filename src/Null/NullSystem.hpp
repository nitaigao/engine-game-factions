/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NullSystem.h
*  @date   2009/04/27
*/
#pragma once
#ifndef NULLSYSTEM_H
#define NULLSYSTEM_H

#include "Service/IService.hpp"
#include "Service/IServiceManager.h"

#include "Configuration/IConfiguration.hpp"
#include "IO/IResourceCache.hpp"

namespace Null
{
  /*!
   *  The Null System 
   */
  class GAMEAPI NullSystem : public ISystem
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    ~NullSystem() { };


    /*! Default Constructor
    *
    *  @return ()
    */
    NullSystem() { };

    /*! Initializes the System
    *
    *  @return (void)
    */
    void Initialize(Configuration::IConfiguration* configuration) { };


    /*! Steps the System's internal data
    *
    *  @param[in] float deltaMilliseconds
    *  @return (void)
    */
    void Update(float deltaMilliseconds) { };


    /*! Releases internal data of the System
    *
    *  @return (System::Types::Type)
    */
    void Release() { };


    /*! Messages the system with a command
    *
    * @param[in] const std::string & message
    * @param[in] AnyType::AnyTypeMap parameters
    * @return (void)
    */
    AnyType::AnyTypeMap ProcessMessage(const System::MessageType& message, AnyType::AnyTypeMap parameters) { };


    /*! Returns the type of the System
    *
    *  @return (System::Types::Type)
    */
    inline System::Types::Type GetType() const { return System::Types::SOUND; };


    /*! Creates a System Scene
    *
    *  @return (ISystemScene*)
    */
    ISystemScene* CreateScene() { };


    /*! Gets the System's Properties
    *
    *  @return (AnyTypeMap)
    */
    inline AnyType::AnyTypeMap GetAttributes() const { return AnyType::AnyTypeMap(); };


    /*! Sets a System Property
    *
    *  @param[in] const std::string & name
    *  @param[in] AnyType value
    *  @return (void)
    */
    inline void SetAttribute(const std::string& name, AnyType value) { };  


  private:

    NullSystem(const NullSystem & copy) { };
    NullSystem & operator = (const NullSystem & copy) { return *this; };

  };
};

#endif
