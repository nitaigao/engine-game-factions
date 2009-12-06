#include "HavokPhysicsSystem.h"
using namespace Physics;

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


BOOL __stdcall DllMain( HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved )
{
	return true;
}

extern "C" void __stdcall Initialize( Logger* logger )
{

}

extern "C" ISystem* __stdcall CreateSystem( IConfiguration* configuration, IServiceManager* serviceManager, IResourceCache* resourceCache, IEventManager* eventManager, IInstrumentation* instrumentation )
{
	return new Physics::HavokPhysicsSystem( serviceManager, resourceCache );
}

extern "C" void __stdcall DestroySystem( ISystem* system )
{
	delete system;
	system = 0;
}