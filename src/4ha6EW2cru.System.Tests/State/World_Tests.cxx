#include <gtest/gtest.h>
using namespace testing;

#include <gmock/gmock.h>

#include "State/World.h"
using namespace State;

#include "../Mocks/MockSystemScene.hpp"
#include "../Mocks/MockStream.h"
using ::testing::Return;

#include "../Mocks/MockSerializer.hpp"
#include "../Mocks/MockEntity.hpp"
#include "../Mocks/MockEntityFactory.hpp"

TEST( World_Tests, should_create_entity )
{
	World world;
	IWorldEntity* entity = world.CreateEntity( "nick" );

	delete entity;
}

TEST( World_Tests, should_create_and_destroy_an_entity )
{
	std::string entityName = "nick";

	World world;
	world.CreateEntity( entityName );
	world.DestroyEntity( entityName );
}


TEST( World_Tests, should_clear_world )
{
	World world;

	int count = rand( ) % 100;

	for( int i = 0; i < count; i++ )
	{
		std::stringstream name;
		name << i;

		world.CreateEntity( name.str( ) );
	}

	world.Clear( );
}

TEST( World_Tests, should_serialize_world_with_count_of_entities_at_the_front )
{
	int entityCount = rand( ) % 100;

	World world;
	MockStream stream;

	EXPECT_CALL( stream, Write( entityCount ) );

	int hasFile = 0;

	for( int i = 0; i < entityCount; i++ )
	{
		std::stringstream entityName;
		entityName << "test_" << i;

		EXPECT_CALL( stream, Write( entityName.str( ) ) );

		IWorldEntity* entity = world.CreateEntity( entityName.str( ) );
	}

	EXPECT_CALL( stream, Write( hasFile ) )
		.Times( entityCount );

	world.Serialize( &stream );

	for( int i = 0; i < entityCount; i++ )
	{
		std::stringstream entityName;
		entityName << "test_" << i;

		world.DestroyEntity( entityName.str( ) );
	}
}

TEST( World_Tests, should_look_at_entity_count_on_deserialize )
{
	World world;
	MockStream stream;

	int entityCount = 0;

	EXPECT_CALL( stream, Read( entityCount ) );

	world.DeSerialize( &stream );
}


void EntityCount( int& data )
{
	data = 1;
}

void EntityName( std::string& data )
{
	data = "test";
}

TEST( World_Tests, should_deserialize_existing_entity )
{
	MockEntity* mockEntity = new MockEntity( );
	MockEntityFactory* entityFactory = new MockEntityFactory( );
	MockSerializer* serializer = new MockSerializer( );
	
	World world( serializer, entityFactory );

	EXPECT_CALL( *entityFactory, CreateEntity( A< const std::string& >( ) ) )
		.WillOnce( Return( mockEntity ) );

	IWorldEntity* entity = world.CreateEntity( "test" );

	MockStream stream;

	EXPECT_CALL( *mockEntity, DeSerialize( &stream ) );

	EXPECT_CALL( stream, Read( An< int& >( ) ) )
		.WillOnce( Invoke( EntityCount ) );

	std::string entityName;

	EXPECT_CALL( stream, Read( A< std::string& >( ) ) )
		.WillRepeatedly( Invoke( EntityName ) );

	world.DeSerialize( &stream );
	
	delete mockEntity;
}

TEST( World_Tests, should_deserialize_a_non_existing_entity )
{
	MockEntity* mockEntity = new MockEntity( );
	MockEntityFactory* entityFactory = new MockEntityFactory( );

	EXPECT_CALL( *entityFactory, CreateEntity( A< const std::string& >( ) ) )
		.WillOnce( Return( mockEntity ) );

	MockSerializer* serializer = new MockSerializer( );

	EXPECT_CALL( *serializer, DeSerializeEntity( An< IWorldEntity* >( ), A< const std::string& >( ) ) );

	World world( serializer, entityFactory );

	MockStream stream;

	EXPECT_CALL( *mockEntity, DeSerialize( &stream ) );

	EXPECT_CALL( stream, Read( An< int& >( ) ) )
		.WillOnce( Invoke( EntityCount ) );

	std::string entityName;

	EXPECT_CALL( stream, Read( A< std::string& >( ) ) )
		.WillRepeatedly( Invoke( EntityName ) );

	world.DeSerialize( &stream );

	delete mockEntity;
}

TEST( World_Tests, should_create_entities )
{
	MockEntity* mockEntity = new MockEntity( );
	MockEntityFactory* entityFactory = new MockEntityFactory( );

	EXPECT_CALL( *entityFactory, CreateEntity( A< const std::string& >( ) ) )
		.WillOnce( Return( mockEntity ) );

	World world( 0, entityFactory );
	IWorldEntity* entity = world.CreateEntity( "test" );

	EXPECT_EQ( mockEntity, entity );

	delete mockEntity;
}


TEST( World_Tests, should_load_a_level_from_the_serializer )
{
	MockSerializer* serializer = new MockSerializer( );

	std::string levelPath = "levelPath";

	EXPECT_CALL( *serializer, DeSerializeLevel( levelPath ) );

	World world( serializer, 0 );
	world.LoadLevel( levelPath );
}