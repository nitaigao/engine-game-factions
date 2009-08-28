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
				class_< ScriptConfiguration >( "Config" )
					.def( constructor< Configuration::IConfiguration* >( ) )
						.property( "isFullScreen", &ScriptConfiguration::IsFullScreen, &ScriptConfiguration::SetFullScreen )
						.property( "displayWidth", &ScriptConfiguration::GetDisplayWidth, &ScriptConfiguration::SetDisplayWidth )
						.property( "displayHeight", &ScriptConfiguration::GetDisplayHeight, &ScriptConfiguration::SetDisplayHeight )
						.property( "isConsole", &ScriptConfiguration::IsConsole, &ScriptConfiguration::SetConsole )
						.property( "isInvertY", &ScriptConfiguration::IsInvertY, &ScriptConfiguration::SetInvertY )
						.property( "isSmoothMouse", &ScriptConfiguration::IsSmoothMouse, &ScriptConfiguration::SetSmoothMouse )
						.property( "mouseSmoothAmount", &ScriptConfiguration::GetMouseSmoothAmount, &ScriptConfiguration::SetMouseSmoothAmount )
						.property( "sfxVolume", &ScriptConfiguration::GetSFXVolume, &ScriptConfiguration::SetSFXVolume )
						.property( "musicVolume", &ScriptConfiguration::GetMusicVolume, &ScriptConfiguration::SetMusicVolume ),

				class_< ScriptComponent >( "ScriptComponent" )
					.def( constructor< ILuaState*, Events::IEventManager*, IScriptFacadeManager* >( ) )
					.def( "include", &ScriptComponent::IncludeScript )
					.def( "registerEventHandler", &ScriptComponent::RegisterEvent )
					.def( "registerUpdateHandler", &ScriptComponent::RegisterUpdate )
					.def( "unregisterEventHandler", &ScriptComponent::UnRegisterEvent )
					.def( "unregisterUpdateHandler", &ScriptComponent::UnRegisterUpdate )
					.def( "getName", &ScriptComponent::GetName )
					.def( "getLookAt", &ScriptComponent::GetLookAt )
					.def( "getPosition", &ScriptComponent::GetPosition )
					.def( "executeString", &ScriptComponent::ExecuteString )
					.def( "broadcastEvent", ( void ( ScriptComponent::* ) ( const std::string& ) ) &ScriptComponent::BroadcastEvent )
					.def( "broadcastEvent", ( void ( ScriptComponent::* ) ( const std::string&, const std::string& ) ) &ScriptComponent::BroadcastEvent )
					.def( "broadcastEvent", ( void ( ScriptComponent::* ) ( const std::string&, int ) ) &ScriptComponent::BroadcastEvent )
					.def( "broadcastEvent", ( void ( ScriptComponent::* ) ( const std::string&, const std::string&, const std::string& ) ) &ScriptComponent::BroadcastEvent )
					.def( "broadcastEvent", ( void ( ScriptComponent::* ) ( const std::string&, const std::string&, int ) ) &ScriptComponent::BroadcastEvent )
					.def( "broadcastEvent", ( void ( ScriptComponent::* ) ( const std::string&, int, int ) ) &ScriptComponent::BroadcastEvent )
					.def( "broadcastEvent", ( void ( ScriptComponent::* ) ( const std::string&, int, const std::string& ) ) &ScriptComponent::BroadcastEvent ),

				class_< MathVector3 >( "Vector" )
					.def( constructor< float, float, float >( ) )
					.def( self + MathVector3( ) ),

				class_< MathQuaternion >( "Quaternion" )
					.def( constructor< float, float, float, float >( ) )
				);

			results[ System::TypeStrings::SCRIPT ] = luaScope;
		}

		return results;
	}
}