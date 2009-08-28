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
	IScriptSystem* ScriptFactory::CreateScriptSystem( )
	{
		return new ScriptSystem( this->CreateScriptSystemScene( ), this->CreateScriptSystemScene( ), Management::Get( )->GetServiceManager( ) );
	}

	IScriptSystemScene* ScriptFactory::CreateScriptSystemScene( )
	{
		ILuaState* state = new LuaState( );
		IScriptFacadeFactory* facadeFactory = new ScriptFacadeFactory( state );
		IScriptComponentFactory* componentFactory = new ScriptComponentFactory( state, Management::Get( )->GetEventManager( ), facadeFactory );

		return new ScriptSystemScene( 
			new ClientConfiguration( ), // TODO: possible bug
			componentFactory,
			state, 
			Management::Get( )->GetServiceManager( ) 
			);
	}
}