/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   GameFactory.h
*  @date   2009/11/24
*/
#pragma once
#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

#include "IGameFactory.hpp"

#include "../Platform/IPlatformManager.h"
#include "../Platform/IProgramOptions.hpp"
#include "../Configuration/IConfiguration.hpp"
#include "../System/ISystemManager.hpp"
#include "../Events/IEventManager.hpp"
#include "../Service/IServiceManager.h"
#include "../IO/IResourceCache.hpp"
#include "../IO/IFileSystem.hpp"
#include "../IO/IPathInformation.hpp"
#include "../System/IInstrumentation.hpp"
#include "../Platform/IClock.hpp"

#include "../Export.hpp"

namespace Game
{
  /*! 
   *  Creates Game Instances
   */
  class GAMEAPI GameFactory : public IGameFactory
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    ~GameFactory();


    /*! Default Constructor
    *
    * @return ()
    */
    GameFactory();


    /*! Creates a Game System
    *
    * @return (IGame*)
    */
    IGame* CreateGame() const;


  private:

    GameFactory(const GameFactory & copy) { };
    GameFactory & operator = (const GameFactory & copy) { return *this; };


    Platform::IProgramOptions* m_programOptions;
    Configuration::IConfiguration* m_configuration;
    Platform::IPlatformManager* m_platformManager;
    ISystemManager* m_systemManager;
    Events::IEventManager* m_eventManager;
    Services::IServiceManager* m_serviceManager;
    Resources::IResourceCache* m_resourceCache;
    IO::IFileSystem* m_fileSystem;
    IO::IPathInformation* m_pathInformation;
    System::IInstrumentation* m_instrumentation;
    Platform::IClock* m_clock;

    
  };
};

#endif