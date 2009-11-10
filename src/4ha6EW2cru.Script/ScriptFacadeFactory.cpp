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
	IScriptFacade* ScriptFacadeFactory::CreateScriptFacade( IScriptFacade::FacadeType facadeType, ISystemComponent* component )
	{
		IScriptFacade* facade = 0;

		if ( typeid( *m_state ) == typeid( LuaState ) )
		{
			LuaState* state = static_cast< LuaState* >( m_state );

			switch( facadeType )
			{

			case IScriptFacade::ANIMATION:

				facade = new AnimationFacade( component );
				state->SetGlobal( "animation", static_cast< AnimationFacade* >( facade ) );

				break;

			case IScriptFacade::INPUT:

				facade = new InputFacade( );
				state->SetGlobal( "input", static_cast< InputFacade* >( facade ) );

				break;

			case IScriptFacade::INSTRUMENTATION:

				facade = new InstrumentationFacade( );
				state->SetGlobal( "instrumentation", static_cast< InstrumentationFacade* >( facade ) );

				break;

			case IScriptFacade::NETWORK:

				facade = new NetworkFacade( );
				state->SetGlobal( "network", static_cast< NetworkFacade* >( facade ) );

				break;

			case IScriptFacade::PHYSICS:

				facade = new PhysicsFacade( );
				state->SetGlobal( "physics", static_cast< PhysicsFacade* >( facade ) );

				break;

			case IScriptFacade::SOUND:

				facade = new SoundFacade( component );
				state->SetGlobal( "sfx", static_cast< SoundFacade* >( facade ) );

				break;

			case IScriptFacade::SYSTEM:

				facade = new SystemFacade( );
				state->SetGlobal( "system", static_cast< SystemFacade* >( facade ) );

				break;
			}
		}

		return facade;
	}
}