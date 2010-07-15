/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkFactory.hpp
*  @date   2009/08/20
*/
#pragma once
#ifndef NETWORKFACTORY_HPP
#define NETWORKFACTORY_HPP

#include "INetworkProvider.hpp"
#include "INetworkSystem.hpp"
#include "INetworkSystemScene.hpp"

#include "Configuration/IConfiguration.hpp"
#include "Service/IServiceManager.h"
#include "IO/IResourceCache.hpp"
#include "Events/IEventManager.hpp"
#include "System/IInstrumentation.hpp"

namespace Network
{
  class INetworkFactory
  {
    virtual INetworkSystem* CreateNetworkSystem() = 0;
  };

  /*! 
   *  Creates Network Objects
   */
  class NetworkFactory : public INetworkFactory
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    ~NetworkFactory() { };

    
    /*! Default Constructor
     *
     * @param[in] Configuration::IConfiguration * configuration
     * @param[in] Services::IServiceManager * serviceManager
     * @param[in] Resources::IResourceCache * resourceCache
     * @param[in] Events::IEventManager * eventManager
     * @param[in] System::IInstrumentation * instrumentation
     * @return ()
     */
    NetworkFactory(
      Configuration::IConfiguration* configuration, Services::IServiceManager* serviceManager, 
      Resources::IResourceCache* resourceCache, Events::IEventManager* eventManager, System::IInstrumentation* instrumentation
     )
      : m_configuration(configuration)
      , m_serviceManager(serviceManager)
      , m_resourceCache(resourceCache)
      , m_eventManager(eventManager)
      , m_instrumentation(instrumentation)
    {

    }

    INetworkSystem* CreateNetworkSystem();

  private:

    NetworkFactory(const NetworkFactory & copy) { };
    NetworkFactory & operator = (const NetworkFactory & copy) { return *this; };


    Configuration::IConfiguration* m_configuration;
    Services::IServiceManager* m_serviceManager;
    Resources::IResourceCache* m_resourceCache;
    Events::IEventManager* m_eventManager;
    System::IInstrumentation* m_instrumentation;
    
  };
};

#endif