#include "UXFactory.h"

#include <MyGui.h>
#include "GUI.h"
#include "UXSystem.h"
#include "UXSystemScene.h"
#include "UXSystemComponentFactory.h"

#include "LuaState.h"
#include "SystemFacade.h"
#include "ScriptFacadeFactory.h"
using namespace Script;

#include "Management/Management.h"

namespace UX
{
	IUXSystem* UXFactory::CreateUXSystem( Configuration::IConfiguration* configuration )
	{
		Services::IServiceManager* serviceManager = Management::Get( )->GetServiceManager( );
		Events::IEventManager* eventManager = Management::Get( )->GetEventManager( );

		ILuaState* masterState = new LuaState( Management::Get( )->GetResourceManager( ) );
		IGUI* gui = this->CreateUXGUI( );
		IScriptFacadeFactory* scriptFacadeFactory = new ScriptFacadeFactory( masterState );

		IUXSystemComponentFactory* factory = new UXSystemComponentFactory( masterState, gui, eventManager, scriptFacadeFactory );
		IUXSystemScene* scene = new UXSystemScene( gui, serviceManager, masterState, factory, configuration, eventManager );

		return new UXSystem( gui, scene, eventManager, serviceManager );
	}

	IGUI* UXFactory::CreateUXGUI()
	{
		MyGUI::Gui* myGUI = new MyGUI::Gui( );
		return new GUI( myGUI, Management::Get( )->GetServiceManager( ) );
	}
}