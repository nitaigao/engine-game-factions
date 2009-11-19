#include "ScriptFactory.h"

#include "ScriptSystem.h"
#include "ScriptSystemScene.h"

#include "LuaState.h"
#include "ScriptComponentFactory.h"
#include "ScriptFacadeManager.h"
#include "ScriptFacadeFactory.h"

#include "Management/Management.h"

#include "Configuration/Configuration.h"
using namespace Configuration;

namespace Script
{
	IScriptSystem* ScriptFactory::CreateScriptSystem( Configuration::IConfiguration* configuration )
	{
		return new ScriptSystem( this->CreateScriptSystemScene( configuration ), this->CreateScriptSystemScene( configuration ), Management::Get( )->GetServiceManager( ) );
	}

	IScriptSystemScene* ScriptFactory::CreateScriptSystemScene( Configuration::IConfiguration* configuration )
	{
		ILuaState* state = new LuaState( Management::Get( )->GetResourceManager( ) );
		IScriptFacadeFactory* facadeFactory = new ScriptFacadeFactory( );
		IScriptComponentFactory* componentFactory = new ScriptComponentFactory( state, Management::Get( )->GetEventManager( ), facadeFactory );

		return new ScriptSystemScene( 
			configuration,
			componentFactory,
			state, 
			Management::Get( )->GetServiceManager( ) 
			);
	}
}