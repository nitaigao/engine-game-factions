#include "ScriptSystem.h"

using namespace Maths;

#include "ScriptSystemScene.h"
#include "ScriptComponent.h"
#include "IScriptFacadeManager.hpp"

#include "Management/Management.h"

#include <luabind/luabind.hpp>
#include <luabind/table_policy.hpp>
#include <luabind/operator.hpp>
using namespace luabind;

namespace Script
{
	ScriptSystem::~ScriptSystem( )
	{
		delete m_auxScene;
		m_auxScene = 0;
	}

	void ScriptSystem::Release( )
	{
		m_auxScene->Destroy( );
	}

	ISystemScene* ScriptSystem::CreateScene( )
	{
		return m_scene;
	}

	void ScriptSystem::Initialize( Configuration::IConfiguration* configuration )
	{
		m_configuration = configuration;

		m_serviceManager->RegisterService( this );
	}

	void ScriptSystem::Update( float deltaMilliseconds )
	{
		m_auxScene->Update( deltaMilliseconds );
		m_scene->Update( deltaMilliseconds );
	}

	AnyType::AnyTypeMap ScriptSystem::ProcessMessage( const System::MessageType& message, AnyType::AnyTypeMap parameters )
	{
		AnyType::AnyTypeMap results;

		if( message == System::Messages::PostInitialize )
		{
			m_auxScene->Initialize( );
			m_scene->Initialize( );
		}

		if( message == System::Messages::LoadScript )
		{
			ISystemComponent* component = m_auxScene->CreateComponent( parameters[ System::Attributes::Name ].As< std::string >( ), "default" );
			component->SetAttribute( System::Parameters::ScriptPath, parameters[ System::Parameters::ScriptPath ].As< std::string >( ) );
			component->Initialize( );
			results[ "component" ] = component;
		}

		if ( message == System::Messages::UnloadComponent )
		{
			m_auxScene->UnloadComponent( parameters[ System::Attributes::Name ].As< std::string >( ) );
		}

		/*from AI
		if ( message == "getMasterState" )
		{
			//results[ "masterState" ] = m_auxScene->GetState( );
		}*/

		if ( message == System::Messages::RegisterScriptFunctions )
		{
			scope luaScope = 
				(

				class_< ScriptComponent >( "ScriptComponent" )
					.def( "include", &ScriptComponent::IncludeScript )
					.def( "registerEventHandler", ( void ( ScriptComponent::* ) ( const std::string&, const luabind::object& ) ) &ScriptComponent::RegisterEventHandler )
					.def( "registerUpdateHandler", &ScriptComponent::RegisterUpdateHandler )
					.def( "unregisterUpdateHandler", &ScriptComponent::UnRegisterUpdateHandler )
					.def( "subscribeMessage", &ScriptComponent::SubscribeMessage )
					.def( "unsubscribeMessage", &ScriptComponent::UnSubscribeMessage )
					.def( "getName", &ScriptComponent::GetName )
					.def( "getLookAt", &ScriptComponent::GetLookAt )
					.def( "getPosition", &ScriptComponent::GetPosition )
					.def( "setPosition", &ScriptComponent::SetPosition ),
				

				class_< MathVector3 >( "Vector" )
					.def( constructor< float, float, float >( ) )
					.def( self + MathVector3( ) ),

				class_< MathQuaternion >( "Quaternion" )
					.def( constructor< float, float, float, float >( ) ),

				class_< AnyType::AnyTypeMap >( "AnyType" )
				);

			results[ System::TypeStrings::SCRIPT ] = luaScope;
		}

		return results;
	}
}