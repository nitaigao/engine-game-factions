/**/
#pragma once
#ifndef SYSTEMEXPORTS_HPP
#define SYSTEMEXPORTS_HPP

#include "ISystem.hpp"

#include "../Configuration/IConfiguration.hpp"
#include "../Service/IServiceManager.h"
#include "../IO/IResourceCache.hpp"
#include "../Events/IEventManager.hpp"
#include "../Logging/Logger.h"
#include "../System/IInstrumentation.hpp"
#include "../Platform/IPlatformManager.h"

extern "C"
{
	typedef void ( __stdcall* InitializeSystemFunction ) ( Logger* logger );
	typedef ISystem* ( __stdcall* CreateSystemFunction ) ( Configuration::IConfiguration* configuration, Services::IServiceManager* serviceManager, Resources::IResourceCache* resourceCache, Events::IEventManager* eventManager, System::IInstrumentation* instrumentation, Platform::IPlatformManager* platformManager );
	typedef void ( __stdcall* DestroySystemFunction ) ( ISystem* system );
};

#endif
