#include "ScriptComponentFactory.h"

#include "ScriptComponent.h"
#include "LuaState.h"

namespace Script
{
	IScriptComponent* ScriptComponentFactory::CreateComponent( const std::string& name, const std::string& type )
	{
		ILuaState* childState = m_masterState->CreateChild( );
		IScriptComponent* component = new ScriptComponent( childState, m_eventManager );

		component->SetAttribute( System::Attributes::Name, name );
		component->SetAttribute( System::Attributes::SystemType, System::Types::SCRIPT );

		// it seems this is the only way round to use this template function and mock the class at the same time for testing
		if ( typeid( childState ) == typeid( LuaState* ) ) 
		{
			static_cast< LuaState* >( childState )->SetGlobal( "script", static_cast< ScriptComponent* >( component ) );
		}

		return component;
	}
}