#include "precompiled.h"

#include "ScriptFactory.h"

#include "ScriptSystem.h"
#include "ScriptSystemScene.h"

#include "LuaState.h"
#include "ScriptComponentFactory.h"
#include "ScriptFacadeManager.h"
#include "ScriptFacadeFactory.h"

#include "Configuration/Configuration.h"
using namespace Configuration;

namespace Script
{
	IScriptSystem* ScriptFactory::CreateScriptSystem( )
	{
		return new ScriptSystem( 
			this->CreateScriptSystemScene( ), 
			this->CreateScriptSystemScene( ), 
			m_serviceManager 
			);
	}

	IScriptSystemScene* ScriptFactory::CreateScriptSystemScene( )
	{
		ILuaState* state = new LuaState( m_resourceCache );
		IScriptFacadeFactory* facadeFactory = new ScriptFacadeFactory( m_serviceManager, m_eventManager, m_platformManager, m_instrumentation, m_resourceCache );
		IScriptComponentFactory* componentFactory = new ScriptComponentFactory( state, m_eventManager, facadeFactory );

		return new ScriptSystemScene( m_configuration, componentFactory, state, m_serviceManager );
	}
}