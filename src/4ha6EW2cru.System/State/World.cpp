#include "World.h"

#include "../System/ISystem.hpp"
#include "../Management/Management.h"

#include "WorldEntity.h"

namespace State
{
	World::~World( )
	{
		for ( ISystemScene::SystemSceneMap::reverse_iterator i = m_systemScenes.rbegin( ); i != m_systemScenes.rend( ); ++i )
		{
			delete ( *i ).second;
		}
	}
	
	IWorldEntity* World::CreateEntity( const std::string& name )
	{
		IWorldEntity* entity = new WorldEntity( name );
		m_entities.insert( std::make_pair( name, entity ) );
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
		for ( IWorldEntity::WorldEntityMap::iterator e = m_entities.begin( ); e != m_entities.end( ); ++e )
		{
			( *e ).second->Serialize( stream );
		}
	}
}