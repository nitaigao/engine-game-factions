#include "precompiled.h"

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

#include "System/ISystem.hpp"
using namespace System;

#include "NullSystem.hpp"

#ifdef WINDOWS
BOOL __stdcall DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
  return true;
}
#endif

extern "C" void Initialize(Logger* logger)
{
  std::cout << "Initialize in Null has been called";
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
  std::cout << "CreateSystem in Null has been called";
  return new Null::NullSystem();
}

extern "C" void DestroySystem(ISystem* system)
{
  std::cout << "DestroySystem in Null has been called";
  delete system;
  system = 0;
}