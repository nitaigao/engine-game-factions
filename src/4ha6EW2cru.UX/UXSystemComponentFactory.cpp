#include "precompiled.h"

#include "UXSystemComponentFactory.h"

#include "LuaState.h"
using namespace Script;

#include "UXSystemComponent.h"
#include "UXFacadeManager.h"

#include "ScriptMessageDispatcher.h"
#include "ScriptEventDispatcher.h"
#include "ScriptUpdateDispatcher.h"

namespace UX
{
	UXSystemComponentFactory::~UXSystemComponentFactory()
	{
		delete m_facadeFactory;
	}

	IUXSystemComponent* UXSystemComponentFactory::CreateComponent( const std::string& name )
	{
		std::stringstream layoutPath;
		layoutPath << "/data/interface/components/" << name << ".layout";
		m_gui->LoadLayout( layoutPath.str( ) );

		ILuaState* childState = m_masterState->CreateChild( );
		IScriptMessageDispatcher* messageDispatcher = new ScriptMessageDispatcher( );
		IScriptEventDispatcher* eventDispatcher = new ScriptEventDispatcher( m_eventManager );
		IScriptUpdateDispatcher* updateDispatcher = new ScriptUpdateDispatcher( );
		IScriptFacadeManager* facadeManager = new UXFacadeManager( m_facadeFactory, childState );

		UXSystemComponent* component = new UXSystemComponent( childState, facadeManager, messageDispatcher, eventDispatcher, updateDispatcher );
		component->SetAttribute( System::Attributes::Name, name );
		component->SetAttribute( System::Attributes::SystemType, System::Types::UX );

		if ( typeid( *childState ) == typeid( LuaState ) ) 
		{
			static_cast< LuaState* >( childState )->SetGlobal( "script", component );
		}

		std::stringstream scriptPath;
		scriptPath << "/data/interface/components/" << name << ".lua";
		childState->LoadScript( scriptPath.str( ) );

		return component;
	}
}

//IScriptComponent* component = new ScriptComponent( childState, m_eventManager, new ScriptFacadeManager( m_facadeFactory, childState ) );