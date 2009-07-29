#include "XMLSerializer.h"

using namespace State;

#include "../../Logging/Logger.h"
using namespace Logging;

#include "../../IO/IResource.hpp"
using namespace Resources;

#include "../../System/SystemTypeMapper.hpp"
#include "../../Management/Management.h"

#include "../../Events/ScriptEvent.hpp"
using namespace Events;

#include "ComponentSerializerFactory.h"
#include "AIComponentSerializer.h"
#include "GeometryComponentSerializer.h"
#include "GraphicsComponentSerializer.h"
#include "InputComponentSerializer.h"
#include "PhysicsComponentSerializer.h"
#include "ScriptComponentSerializer.h"
#include "..\IWorldEntity.hpp"

using namespace ticpp;

namespace Serialization
{
	
	void XMLSerializer::Load( const std::string& levelPath )
	{
		Management::Get( )->GetServiceManager( )->RegisterService( this );

		if ( !Management::Get( )->GetFileManager( )->FileExists( levelPath ) )
		{
			std::stringstream logMessage;
			logMessage << "Unable to locate level file at path: " << levelPath;
			Logger::Get( )->Warn( logMessage.str( ) );
			return;
		}

		m_loadProgress = 0;
		m_loadTotal = 0;
	
		Management::Get( )->GetEventManager( )->QueueEvent( new ScriptEvent( "WORLD_LOADING_STARTED", levelPath ) );
	
		IResource* resource = Management::Get( )->GetResourceManager( )->GetResource( levelPath );
		Document levelFile( resource->GetFileBuffer()->fileBytes );

		this->LoadElement( levelFile.FirstChildElement( ) );
	}

	void XMLSerializer::LoadElement( ticpp::Element* element )
	{
		for( Iterator< Element > child = element->FirstChildElement( false ); child != child.end( ); child++ )
		{
			std::string elementName;
			( *child ).GetValue( &elementName );

			if ( elementName == "color" || elementName == "entity" )
			{
				m_loadQueueEl.push( ( *child ).ClonePtr( ) );
				m_loadTotal++;
			}

			this->LoadElement( &( *child ) );
		}
	}

	void XMLSerializer::DeserializeElement( ticpp::Element* element )
	{
		std::string elementName;
		element->GetValue( &elementName );

		if ( elementName == "entity" )
		{
			this->LoadEntity( element );
		}
		else if ( elementName == "color" )
		{
			this->LoadColor( element );
		}
		/*else if( elementName == "fog" )
		{
			this->LoadFog( element );
		}
		else if ( elementName == "skybox" )
		{
			this->LoadSkyBox( element );
		}*/
	}
	
	/*void XMLSerializer::LoadLink( const YAML::Node& node )
	{ 
		std::string subjectName, subjectSystem, observerName, observerSystem;
	
		node[ "subjectName" ] >> subjectName;
		node[ "subjectSystem" ] >> subjectSystem;
		node[ "observerName" ] >> observerName;
		node[ "observerSystem" ] >> observerSystem;
	
		System::Types::Type subjectSystemType = System::SystemTypeMapper::StringToType( subjectSystem );
		System::Types::Type observerSystemType = System::SystemTypeMapper::StringToType( observerSystem );

		if ( 
			Management::Get( )->GetSystemManager( )->HasSystem( subjectSystemType ) && 
			Management::Get( )->GetSystemManager( )->HasSystem( observerSystemType ) 
			)
		{
			IWorldEntity* subject = m_world->FindEntity( subjectName );
			IWorldEntity* observer = m_world->FindEntity( observerName );

			subject->AddObserver( System::Messages::SetPlayerPosition, observer );
		}
	}*/
	
	/*void XMLSerializer::LoadSkyBox( const YAML::Node& node )
	{
		if ( Management::Get( )->GetSystemManager( )->HasSystem( System::Types::RENDER ) )
		{
			std::string materialName;
			node[ "material" ] >> materialName;

			float distance;
			node[ "distance" ] >> distance;

			AnyType::AnyTypeMap parameters;
			parameters[ "material" ] = materialName;
			parameters[ "distance" ] = distance;
		
			ISystem* renderer = Management::Get( )->GetSystemManager( )->GetSystem( System::Types::RENDER );
			renderer->SetAttribute( "skyBox", parameters );
		}
	}*/

	/*void XMLSerializer::LoadFog( const YAML::Node& node )
	{
		if ( Management::Get( )->GetSystemManager( )->HasSystem( System::Types::RENDER ) )
		{
			float linearEnd, linearStart;
			node[ "linearEnd" ] >> linearEnd;
			node[ "linearStart" ] >> linearStart;

			float r, g, b;
			node[ "r" ] >> r;
			node[ "g" ] >> g;
			node[ "b" ] >> b;

			AnyType::AnyTypeMap parameters;
			parameters[ "linearEnd" ] = linearEnd;
			parameters[ "linearStart" ] = linearStart;
			parameters[ "color" ] = Renderer::Color( r, g, b );

			ISystem* renderer = Management::Get( )->GetSystemManager( )->GetSystem( System::Types::RENDER );
			renderer->SetAttribute( "fog", parameters );
		}
	}*/
	
	void XMLSerializer::LoadColor( ticpp::Element* element )
	{
		if ( Management::Get( )->GetSystemManager( )->HasSystem( System::Types::RENDER ) )
		{
			std::string key;

			float red = 0;
			float green = 0;
			float blue = 0;

			element->GetAttribute( "type", &key );
			element->GetAttribute( "r", &red );
			element->GetAttribute( "g", &green );
			element->GetAttribute( "b", &blue );

			AnyType::AnyTypeMap parameters;
			parameters[ "r" ] = red;
			parameters[ "g" ] = green;
			parameters[ "b" ] = blue;

			ISystem* graphicsSystem = Management::Get( )->GetSystemManager( )->GetSystem( System::Types::RENDER );

			graphicsSystem->SetAttribute( key, parameters );
		}
	}

	void XMLSerializer::ImportEntity( const std::string& src, NodePtrMap& components )
	{
		IResource* resource = Management::Get( )->GetResourceManager( )->GetResource( src );
		Document externalFile( resource->GetFileBuffer( )->fileBytes );

		for( Iterator< Element > child = externalFile.FirstChildElement( false ); child != child.end( ); child++ )
		{
			this->LoadEntityComponents( &*child, components );
		}
	}

	IWorldEntity* XMLSerializer::CreateEntity( const std::string& name, NodePtrMap& components )
	{
		IWorldEntity* entity = m_world->CreateEntity( name );

		for( NodePtrMap::iterator i = components.begin( ); i != components.end( ); ++i )
		{
			if ( Management::Get( )->GetSystemManager( )->HasSystem( ( *i ).first ) ) 
			{
				IComponentSerializer* serializer = ComponentSerializerFactory::Create( ( *i ).first );
				ISystemComponent* component = serializer->DeSerialize( name, ( *i ).second->ToElement( ), m_world->GetSystemScenes( ) );
				entity->AddComponent( component );

				delete serializer;
			}

			delete ( *i ).second;
		}

		return entity;
	}
	
	void XMLSerializer::LoadEntity( ticpp::Element* element )
	{ 	
		std::string src;
		element->GetAttribute( "src", &src, false );

		NodePtrMap components;

		if ( !src.empty( ) )
		{
			this->ImportEntity( src, components );
		}

		this->LoadEntityComponents( element, components );

		std::string name;
		element->GetAttribute( "name", &name );

		IWorldEntity* entity = this->CreateEntity( name, components );
		entity->Initialize( );
	}

	void XMLSerializer::LoadEntity( const std::string& name, const std::string& entityFilePath )
	{
		NodePtrMap components;

		this->ImportEntity( entityFilePath, components );
		IWorldEntity* entity = this->CreateEntity( name, components );

		entity->SetAttribute( System::Attributes::FilePath, entityFilePath );
		entity->Initialize( );
	}

	void XMLSerializer::LoadEntityComponents( ticpp::Element* element, NodePtrMap& components )
	{
		for( Iterator< Element > child = element->FirstChildElement( false ); child != child.end( ); child++ )
		{
			std::string elementName;
			child->GetValue( &elementName );

			if ( elementName == "components" )
			{
				for( Iterator< Element > component = ( *child ).FirstChildElement( false ); component != component.end( ); component++ )
				{
					std::string system;
					( *component ).GetAttribute( "system", &system );

					System::Types::Type systemType = System::SystemTypeMapper::StringToType( system );

					if ( components.find( systemType ) != components.end( ) )
					{
						delete components[ systemType ];
					}

					components[ systemType ] = ( *component ).ClonePtr( );
				}
			}
		}
	}
	
	void XMLSerializer::Update( const float& deltaMilliseconds )
	{
		if ( !m_loadQueueEl.empty( ) )
		{
			this->DeserializeElement( m_loadQueueEl.front( )->ToElement( ) );

			delete m_loadQueueEl.front( );

			m_loadQueueEl.pop( );

			float progressPercent = ( ( float ) ++m_loadProgress / ( float ) m_loadTotal ) * 100.0f;
			Management::Get( )->GetEventManager( )->QueueEvent( new ScriptEvent( "WORLD_LOADING_PROGRESS", static_cast< int >( progressPercent ) ) );

			if ( m_loadQueueEl.empty( ) )
			{
				m_loadProgress = m_loadTotal;
				Management::Get( )->GetEventManager( )->QueueEvent( new ScriptEvent( "WORLD_LOADING_FINISHED" ) );

				Management::Get( )->GetServiceManager( )->MessageAll( System::Messages::Network::Client::LevelLoaded, AnyType::AnyTypeMap( ) );
			}
		}
	}

	XMLSerializer::~XMLSerializer()
	{
		while( m_loadQueueEl.size( ) > 0 )
		{
			delete m_loadQueueEl.front( );
			m_loadQueueEl.pop( );
		}
	}

	AnyType::AnyTypeMap XMLSerializer::Message( const System::Message& message, AnyType::AnyTypeMap parameters )
	{
		if ( message == System::Messages::Entity::CreateEntity )
		{
			this->LoadEntity( parameters[ System::Attributes::Name ].As< std::string >( ), parameters[ System::Attributes::FilePath ].As< std::string >( ) );
		}

		if ( message == System::Messages::Entity::DestroyEntity )
		{
			m_world->DestroyEntity( parameters[ System::Attributes::Name ].As< std::string >( ) );
		}

		if ( message == System::Messages::Entity::SerializeWorld )
		{
			m_world->Serialize( parameters[ System::Parameters::IO::Stream ].As< IO::IStream* >( ) );
		}

		return AnyType::AnyTypeMap( );
	}
}