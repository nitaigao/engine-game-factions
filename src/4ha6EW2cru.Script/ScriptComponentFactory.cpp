#include "ScriptComponentFactory.h"

#include "ScriptComponent.h"
#include "ScriptFacadeManager.h"
#include "ScriptMessageDispatcher.h"
#include "ScriptEventDispatcher.h"
#include "ScriptUpdateDispatcher.h"
#include "LuaState.h"

namespace Script
{
	ScriptComponentFactory::~ScriptComponentFactory()
	{
		delete m_facadeFactory;
	}

	IScriptComponent* ScriptComponentFactory::CreateComponent( const std::string& name, const std::string& type )
	{
 		ILuaState* childState = m_masterState->CreateChild( );
		IScriptMessageDispatcher* messageDispatcher = new ScriptMessageDispatcher( );
		IScriptEventDispatcher* eventDispatcher = new ScriptEventDispatcher( m_eventManager );
		IScriptUpdateDispatcher* updateDispatcher = new ScriptUpdateDispatcher( );
		IScriptFacadeManager* facadeManager = new ScriptFacadeManager( m_facadeFactory, childState );

		IScriptComponent* component = new ScriptComponent( childState, facadeManager, messageDispatcher, eventDispatcher, updateDispatcher );

		component->SetAttribute( System::Attributes::Name, name );
		component->SetAttribute( System::Attributes::SystemType, System::Types::SCRIPT );

		if ( typeid( *childState ) == typeid( LuaState ) ) 
		{
			static_cast< LuaState* >( childState )->SetGlobal( "script", static_cast< ScriptComponent* >( component ) );
		}

		return component;
	}
}