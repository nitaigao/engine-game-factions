#include <gtest/gtest.h>
using namespace testing;

#include "NetworkSystemScene.h"
using namespace Network;

#include "Mocks/MockNetworkSystemProvider.hpp"
#include "Mocks/MockNetworkSystemComponentFactory.hpp"
#include "Mocks/MockNetworkSystemComponent.hpp"

TEST( NetworkSystemScene, should_update_providers )
{
	float delta = 99;

	MockNetworkSystemProvider* provider = new MockNetworkSystemProvider( );
	EXPECT_CALL( *provider, Update( delta ) ); 

	NetworkSystemScene scene;
	scene.AddNetworkProvider( provider );
	scene.Update( delta );
}


TEST( NetworkSystemScene, should_add_providers_to_a_new_component )
{
	MockNetworkSystemProvider* provider = new MockNetworkSystemProvider( );
	MockNetworkSystemComponentFactory* factory = new MockNetworkSystemComponentFactory( );
	MockNetworkSystemComponent* component = new MockNetworkSystemComponent( );

	std::string name = "test";

	EXPECT_CALL( *factory, Create( name ) )
		.WillOnce( Return( component ) );

	EXPECT_CALL( *component, AddProvider( provider ) );
 
	NetworkSystemScene scene( factory );
	scene.AddNetworkProvider( provider );
	scene.CreateComponent( name, "default" );

	delete component;
}

TEST( NetworkSystemScene, should_release_all_providers )
{
	MockNetworkSystemProvider* provider = new MockNetworkSystemProvider( );
	EXPECT_CALL( *provider, Destroy( ) ); 

	NetworkSystemScene scene;
	scene.AddNetworkProvider( provider );
	scene.Destroy( );
}