#include "precompiled.h"

#include "RendererSystem.h"
using namespace Renderer;

#include "Configuration/IConfiguration.hpp"
using namespace Configuration;

#include "Service/IServiceManager.h"
using namespace Services;

#include "IO/IResourceCache.hpp"
using namespace Resources;

#include "Events/IEventManager.hpp"
using namespace Events;

#include "System/IInstrumentation.hpp"
using namespace System;

#include "Logging/Logger.h"
using namespace Logging;

#include "Platform/IPlatformManager.h"
using namespace Platform;

#ifdef WINDOWS
BOOL __stdcall DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
  return true;
}
#endif

extern "C" void Initialize(Logger* logger)
{
  
}

extern "C" ISystem* CreateSystem(
  IConfiguration* configuration, 
  IServiceManager* serviceManager, 
  IResourceCache* resourceCache, 
  IEventManager* eventManager, 
  IInstrumentation* instrumentation,
  IPlatformManager* platformManager
 )
{
  return new Renderer::RendererSystem(eventManager, platformManager, serviceManager, resourceCache);
}

extern "C" void DestroySystem(ISystem* system)
{
  delete system;
  system = 0;
}