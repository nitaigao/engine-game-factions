#include <gtest/gtest.h>
using namespace testing;

#include "State/World.h"
using namespace State;

#include "../Mocks/MockSystemScene.hpp"
#include "../Mocks/MockStream.h"
#include "../Mocks/MockSerializer.hpp"
#include "../Mocks/MockEntity.hpp"
#include "../Mocks/MockEntityFactory.hpp"
#include "../Mocks/MockEntityService.hpp"
#include "../Mocks/MockServiceManager.hpp"

class World_Tests : public TestHarness< World >
{

protected:

	MockSerializer* m_serializer;
	MockEntityFactory* m_entityFactory;
	MockServiceManager* m_serviceManager;

	void EstablishContext( )
	{
		m_serializer = new MockSerializer( );
		m_entityFactory = new MockEntityFactory( );
		m_serviceManager = new MockServiceManager( );
	}


	void DestroyContext( )
	{
		delete m_serviceManager;
	}

	World* CreateSubject( )
	{
		return new World( m_serializer, m_entityFactory, m_serviceManager );
	}
};


TEST_F( World_Tests, should_create_entity )
{
	IWorldEntity* entity = m_subject->CreateEntity( "nick" );

	delete entity;
}

TEST_F( World_Tests, should_create_and_destroy_an_entity )
{
	std::string entityName = "nick";

	MockEntity* entity = new MockEntity( );

	EXPECT_CALL( *m_entityFactory, CreateEntity( entityName ) ).WillOnce( Return( entity ) );
	EXPECT_CALL( *entity, GetComponents( ) ).WillOnce( Return( ISystemComponent::SystemComponentList( ) ) );

	m_subject->CreateEntity( entityName );
	m_subject->DestroyEntity( entityName );
}


TEST_F( World_Tests, should_clear_world )
{
	int count = rand( ) % 100;

	for( int i = 0; i < count; i++ )
	{
		std::stringstream name;
		name << i;

		MockEntity* entity = new MockEntity( );

		EXPECT_CALL( *entity, GetComponents( ) ).WillRepeatedly( Return( ISystemComponent::SystemComponentList( ) ) );
		EXPECT_CALL( *m_entityFactory, CreateEntity( name.str( ) ) ).WillOnce( Return( entity ) );

		m_subject->CreateEntity( name.str( ) );
	}

	m_subject->Clear( );
}

TEST_F( World_Tests, should_serialize_world_with_count_of_entities_at_the_front )
{
	int entityCount = rand( ) % 100;

	MockStream stream;

	EXPECT_CALL( stream, Write( entityCount ) );

	int hasFile = 0;

	for( int i = 0; i < entityCount; i++ )
	{
		std::stringstream entityName;
		entityName << "test_" << i;

		MockEntity* entity = new MockEntity( );

		EXPECT_CALL( *entity, GetComponents( ) ).WillRepeatedly( Return( ISystemComponent::SystemComponentList( ) ) );
		EXPECT_CALL( *m_entityFactory, CreateEntity( entityName.str( ) ) ).WillOnce( Return( entity ) );
		EXPECT_CALL( *entity, Serialize( &stream ) );

		m_subject->CreateEntity( entityName.str( ) );
	}

	m_subject->Serialize( &stream );

	for( int i = 0; i < entityCount; i++ )
	{
		std::stringstream entityName;
		entityName << "test_" << i;

		m_subject->DestroyEntity( entityName.str( ) );
	}
}

TEST_F( World_Tests, should_look_at_entity_count_on_deserialize )
{
	MockStream stream;

	int entityCount = 0;

	EXPECT_CALL( stream, Read( entityCount ) );

	m_subject->DeSerialize( &stream );
}

void EntityCount( int& data ) { data = 1; };
void EntityName( std::string& data ) { data = "test"; }
void HasFileNameTrue( int& data ) { data = 1; };
void HasFileNameFalse( int& data ) { data = 0; };
void EntityType( std::string& data ) { data = "marine"; };

TEST_F( World_Tests, should_deserialize_existing_entity )
{
	MockStream stream;
	MockEntity mockEntity;;
	EXPECT_CALL( mockEntity, DeSerialize( &stream ) );

	EXPECT_CALL( *m_entityFactory, CreateEntity( A< const std::string& >( ) ) ).WillOnce( Return( &mockEntity ) );

	m_subject->CreateEntity( "test" );

	Sequence sequence;

	EXPECT_CALL( stream, Read( An< int& >( ) ) ).InSequence( sequence ).WillOnce( Invoke( EntityCount ) );
	EXPECT_CALL( stream, Read( An< std::string& >( ) ) ).InSequence( sequence ).WillOnce( Invoke( EntityName ) );
	EXPECT_CALL( stream, Read( An< int& >( ) ) ).InSequence( sequence ).WillOnce( Invoke( HasFileNameFalse ) );
	EXPECT_CALL( stream, Read( An< std::string& >( ) ) ).InSequence( sequence ).WillOnce( Invoke( EntityType ) );

	m_subject->DeSerialize( &stream );
}

TEST_F( World_Tests, should_deserialize_a_non_existing_entity )
{
	MockStream stream;
	MockEntity mockEntity;;
	EXPECT_CALL( mockEntity, DeSerialize( &stream ) );

	EXPECT_CALL( *m_entityFactory, CreateEntity( A< const std::string& >( ) ) ).WillOnce( Return( &mockEntity ) );

	m_subject->CreateEntity( "test" );

	Sequence sequence;

	EXPECT_CALL( stream, Read( An< int& >( ) ) ).InSequence( sequence ).WillOnce( Invoke( EntityCount ) );
	EXPECT_CALL( stream, Read( An< std::string& >( ) ) ).InSequence( sequence ).WillOnce( Invoke( EntityName ) );
	EXPECT_CALL( stream, Read( An< int& >( ) ) ).InSequence( sequence ).WillOnce( Invoke( HasFileNameTrue ) );
	EXPECT_CALL( stream, Read( An< std::string& >( ) ) ).InSequence( sequence ).WillOnce( Invoke( EntityType ) );

	m_subject->DeSerialize( &stream );
}

TEST_F( World_Tests, should_create_entities )
{
	MockEntity* mockEntity = new MockEntity( );
	
	EXPECT_CALL( *m_entityFactory, CreateEntity( A< const std::string& >( ) ) )
		.WillOnce( Return( mockEntity ) );

	IWorldEntity* entity = m_subject->CreateEntity( "test" );

	EXPECT_EQ( mockEntity, entity );

	delete mockEntity;
}


TEST_F( World_Tests, should_load_a_level_from_the_serializer )
{
	std::string levelPath = "levelPath";

	EXPECT_CALL( *m_serializer, DeSerializeLevel( m_subject, levelPath ) );

	m_subject->LoadLevel( levelPath );
}

TEST_F( World_Tests, should_create_an_entity_from_file )
{
	MockEntity entity;

	std::string filePath = "filePath";
	std::string name = "name";

	EXPECT_CALL( *m_entityFactory, CreateEntity( name ) ).WillOnce( Return( &entity ) );
	EXPECT_CALL( *m_serializer, DeSerializeEntity( An< IWorldEntity* >( ), filePath ) );

	m_subject->CreateEntity( name, filePath, "type" );
}
