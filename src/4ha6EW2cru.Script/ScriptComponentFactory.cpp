#include "ScriptComponentFactory.h"

#include "ScriptComponent.h"
#include "ScriptFacadeManager.h"
#include "ScriptMessageDispatcher.h"
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
		IScriptFacadeManager* facadeManager = new ScriptFacadeManager( m_facadeFactory, childState );

		IScriptComponent* component = new ScriptComponent( childState, m_eventManager, facadeManager, messageDispatcher );

		component->SetAttribute( System::Attributes::Name, name );
		component->SetAttribute( System::Attributes::SystemType, System::Types::SCRIPT );

		if ( typeid( *childState ) == typeid( LuaState ) ) 
		{
			static_cast< LuaState* >( childState )->SetGlobal( "script", static_cast< ScriptComponent* >( component ) );
		}

		return component;
	}
}