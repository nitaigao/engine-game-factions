#include "ScriptFactory.h"

#include "ScriptSystem.h"
#include "ScriptSystemScene.h"

#include "LuaState.h"
#include "ScriptComponentFactory.h"

#include "Management/Management.h"

#include "Configuration/Configuration.h"
using namespace Configuration;

namespace Script
{
	IScriptSystem* ScriptFactory::CreateScriptSystem()
	{
		return new ScriptSystem( this->CreateScriptSystemScene( ), this->CreateScriptSystemScene( ), Management::Get( )->GetServiceManager( ) );
	}

	IScriptSystemScene* ScriptFactory::CreateScriptSystemScene()
	{
		ILuaState* state = new LuaState( );
		IScriptComponentFactory* factory = new ScriptComponentFactory( state, Management::Get( )->GetEventManager( ) );

		return new ScriptSystemScene( 
			new ClientConfiguration( ), // TODO: possible bug
			factory,
			state, 
			Management::Get( )->GetServiceManager( ) 
			);
	}
}