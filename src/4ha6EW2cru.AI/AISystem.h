/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   AISystem.h
*  @date   2009/04/25
*/
#pragma once
#ifndef AISYSTEM_H
#define AISYSTEM_H

#include "IAISystem.hpp"

#include "Service/IServiceManager.h"

namespace AI
{
  /*! 
   *  The Artificial Intelligence System
   */
  class AISystem : public IAISystem
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    ~AISystem() { };


    /*! Default Constructor
     *
     *  @return ()
     */
    AISystem(Services::IServiceManager* serviceManager)
      : m_scene(0)
      , m_serviceManager(serviceManager)
    {

    }


    /*! Initializes the System
     *
     *  @return (void)
     */
    inline void Initialize(Configuration::IConfiguration* configuration) { };


    /*! Steps the System's internal data
     *
     *  @param[in] float deltaMilliseconds
     *  @return (void)
     */
    void Update(float deltaMilliseconds);


    /*! Releases the System
     *
     *  @return (void)
     */
    inline void Release() { };
    

    /*! Returns the type of the System
     *
     *  @return (System::Types::Type)
     */
    inline System::Types::Type GetType() const { return System::Types::AI; };


    /*! Creates a System Scene
     *
     *  @return (ISystemScene*)
     */
    ISystemScene* CreateScene();


    /*! Gets the System's Properties
     *
     *  @return (AnyTypeMap)
     */
    inline AnyType::AnyTypeMap GetAttributes() const { return m_attributes; };


    /*! Sets a System Property
     *
     *  @param[in] const std::string & name
     *  @param[in] AnyType value
     *  @return (void)
     */
    inline void SetAttribute(const std::string& name, AnyType value) { };

  private:

    AISystem(const AISystem & copy) { };
    AISystem & operator = (const AISystem & copy) { return *this; };

    AnyType::AnyTypeMap m_attributes;
    ISystemScene* m_scene;
    Services::IServiceManager* m_serviceManager;
  };
};

#endif
