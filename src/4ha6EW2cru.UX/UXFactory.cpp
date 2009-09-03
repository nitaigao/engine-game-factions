#include "UXFactory.h"

#include <MyGui.h>
#include "GUI.h"
#include "UXSystem.h"
#include "UXSystemScene.h"
#include "UXSystemComponentFactory.h"

#include "LuaState.h"
using namespace Script;

#include "Management/Management.h"

namespace UX
{
	IUXSystem* UXFactory::CreateUXSystem()
	{
		ILuaState* masterState = new LuaState( Management::Get( )->GetResourceManager( ) );
		IGUI* gui = this->CreateUXGUI( );
		IUXSystemComponentFactory* factory = new UXSystemComponentFactory( masterState, gui, Management::Get( )->GetEventManager( ) );
		IUXSystemScene* scene = new UXSystemScene( gui, Management::Get( )->GetServiceManager( ), masterState, factory );

		return new UXSystem( gui, scene, Management::Get( )->GetEventManager( ), Management::Get( )->GetServiceManager( ) );
	}

	IGUI* UXFactory::CreateUXGUI()
	{
		MyGUI::Gui* myGUI = new MyGUI::Gui( );
		return new GUI( myGUI, Management::Get( )->GetServiceManager( ) );
	}
}