#include "ScriptFacadeFactory.h"

#include "LuaState.h"

#include "PhysicsFacade.h"
#include "SystemFacade.h"
#include "SoundFacade.h"
#include "InstrumentationFacade.h"
#include "AnimationFacade.h"
#include "NetworkFacade.h"
#include "InputFacade.h"

namespace Script
{
	IScriptFacade* ScriptFacadeFactory::CreateScriptFacade( IScriptFacade::FacadeType facadeType, ISystemComponent* component, ILuaState* state )
	{
		IScriptFacade* facade = 0;

		if ( typeid( *state ) == typeid( LuaState ) )
		{
			LuaState* luaState = static_cast< LuaState* >( state );

			switch( facadeType )
			{

			case IScriptFacade::ANIMATION:

				facade = new AnimationFacade( component );
				luaState->SetGlobal( "animation", static_cast< AnimationFacade* >( facade ) );

				break;

			case IScriptFacade::INPUT:

				facade = new InputFacade( m_serviceManager );
				luaState->SetGlobal( "input", static_cast< InputFacade* >( facade ) );

				break;

			case IScriptFacade::INSTRUMENTATION:

				facade = new InstrumentationFacade( m_instrumentation );
				luaState->SetGlobal( "instrumentation", static_cast< InstrumentationFacade* >( facade ) );

				break;

			case IScriptFacade::NETWORK:

				facade = new NetworkFacade( m_serviceManager, m_resourceCache );
				luaState->SetGlobal( "network", static_cast< NetworkFacade* >( facade ) );

				break;

			case IScriptFacade::PHYSICS:

				facade = new PhysicsFacade( m_serviceManager );
				luaState->SetGlobal( "physics", static_cast< PhysicsFacade* >( facade ) );

				break;

			case IScriptFacade::SOUND:

				facade = new SoundFacade( component, m_serviceManager );
				luaState->SetGlobal( "sfx", static_cast< SoundFacade* >( facade ) );

				break;

			case IScriptFacade::SYSTEM:

				facade = new SystemFacade( m_eventManager, m_platformManager ) ;
				luaState->SetGlobal( "system", static_cast< SystemFacade* >( facade ) );

				break;
			}
		}

		return facade;
	}
}