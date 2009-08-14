#include "World.h"

#include "../System/ISystem.hpp"
#include "../Management/Management.h"

#include "WorldEntity.h"
#include "WorldEntityFactory.h"
#include "EntityService.h"

#include "Serilaization/XMLSerializer.h"
using namespace Serialization;

namespace State
{
	World::~World( )
	{
		for ( ISystemScene::SystemSceneMap::reverse_iterator i = m_systemScenes.rbegin( ); i != m_systemScenes.rend( ); ++i )
		{
			delete ( *i ).second;
		}

		delete m_serializer;
		delete m_entityFactory;
		delete m_entityService;
	}

	World::World( )
	{
		m_serializer = new Serialization::XMLSerializer( this );
		m_entityFactory = new WorldEntityFactory( );
		m_entityService = new EntityService( this );
	}

	void World::Initialize( )
	{
		Management::Get( )->GetServiceManager( )->RegisterService( m_entityService );
	}
	
	IWorldEntity* World::CreateEntity( const std::string& name )
	{
		IWorldEntity* entity = m_entityFactory->CreateEntity( name );
		m_entities.insert( std::make_pair( name, entity ) );
		return entity;
	}

	IWorldEntity* World::CreateEntity( const std::string& name, const std::string& filePath )
	{
		IWorldEntity* entity = this->CreateEntity( name );
		m_serializer->DeSerializeEntity( entity, filePath );
		return entity;
	}

	void World::DestroyEntity( const std::string& name )
	{
		IWorldEntity* entity = ( *m_entities.find( name ) ).second;
		ISystemComponent::SystemComponentList components = entity->GetComponents( );

		for( ISystemComponent::SystemComponentList::iterator c = components.begin( ); c != components.end( ); ++c )
		{
			m_systemScenes[ ( *c )->GetAttributes( )[ System::Attributes::SystemType ].As< System::Types::Type >( ) ]->DestroyComponent( ( *c ) );
		}

		delete entity;

		m_entities.erase( name );
	}
	
	void World::Clear( )
	{
		IWorldEntity::WorldEntityMap entitiesToErase = m_entities;

		for ( IWorldEntity::WorldEntityMap::iterator e = entitiesToErase.begin( ); e != entitiesToErase.end( ); ++e )
		{
			this->DestroyEntity( ( *e ).first );
		}
	}

	void World::Destroy( )
	{
		this->Clear( );

		for ( ISystemScene::SystemSceneMap::reverse_iterator i = m_systemScenes.rbegin( ); i != m_systemScenes.rend( ); ++i )
		{
			( *i ).second->Destroy( );
		}
	}

	void World::Serialize( IO::IStream* stream )
	{
		stream->Write( m_entities.size( ) );

		for ( IWorldEntity::WorldEntityMap::iterator e = m_entities.begin( ); e != m_entities.end( ); ++e )
		{
			( *e ).second->Serialize( stream );
		}
	}

	void World::DeSerialize( IO::IStream* stream )
	{
		int entityCount = 0;
		stream->Read( entityCount );

		for( int i = 0; i < entityCount; i++ )
		{
			std::string entityName;
			stream->Read( entityName );

			int hasFilePath;
			stream->Read( hasFilePath );

			if ( m_entities.find( entityName ) != m_entities.end( ) )
			{
				m_entities[ entityName ]->DeSerialize( stream );
			}
			else
			{
				std::string filePath;
				stream->Read( filePath );

				IWorldEntity* entity = m_entityFactory->CreateEntity( entityName );
				m_serializer->DeSerializeEntity( entity, filePath );

				entity->DeSerialize( stream );
			}
		}
	}

	void World::Update( float deltaMilliseconds )
	{
		m_serializer->Update( deltaMilliseconds );
	}

	void World::LoadLevel( const std::string& levelpath )
	{
		m_serializer->DeSerializeLevel( levelpath );
	}

	/*AnyType::AnyTypeMap XMLSerializer::Message( const System::Message& message, AnyType::AnyTypeMap parameters )
	{
		/*if ( message == System::Messages::Entity::CreateEntity )
		{
		this->LoadEntity( parameters[ System::Attributes::Name ].As< std::string >( ), parameters[ System::Attributes::FilePath ].As< std::string >( ) );
		}

		if ( message == System::Messages::Entity::DestroyEntity )
		{
		m_world->DestroyEntity( parameters[ System::Attributes::Name ].As< std::string >( ) );
		}

		if( message == System::Messages::Entity::SerializeWorld )
		{
			m_world->Serialize( parameters[ System::Parameters::IO::Stream ].As< IStream* >( ) );
		}

		if( message == System::Messages::Entity::DeserializeWorld )
		{
			//m_world->Serialize( parameters[ System::Parameters::IO::Stream ].As< IStream* >( ) );
		}

		return AnyType::AnyTypeMap( );
	}*/
}