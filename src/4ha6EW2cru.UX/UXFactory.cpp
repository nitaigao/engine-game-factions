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

namespace UX
{
	IUXSystem* UXFactory::CreateUXSystem( )
	{
		ILuaState* masterState = new LuaState( m_resourceCache );
		IGUI* gui = this->CreateUXGUI( );
		IScriptFacadeFactory* scriptFacadeFactory = new ScriptFacadeFactory( m_serviceManager, m_eventManager, m_platformManager, m_instrumentation, m_resourceCache );

		IUXSystemComponentFactory* factory = new UXSystemComponentFactory( masterState, gui, m_eventManager, scriptFacadeFactory );
		IUXSystemScene* scene = new UXSystemScene( gui, m_serviceManager, masterState, factory, m_configuration, m_eventManager );

		return new UXSystem( gui, scene, m_eventManager, m_serviceManager );
	}

	IGUI* UXFactory::CreateUXGUI()
	{
		MyGUI::Gui* myGUI = new MyGUI::Gui( );
		return new GUI( myGUI, m_serviceManager );
	}
}