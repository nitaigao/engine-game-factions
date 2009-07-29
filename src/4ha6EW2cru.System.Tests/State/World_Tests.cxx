#include <gtest/gtest.h>
using namespace testing;

#include "State/World.h"
using namespace State;

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