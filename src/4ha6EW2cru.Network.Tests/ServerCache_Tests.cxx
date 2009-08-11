#include <gtest/gtest.h>
using namespace testing;

#include "ServerCache.h"
#include "ServerAdvertisement.hpp"
using namespace Network;

TEST( ServerCache_Tests, should_exist_after_adding )
{
	std::string address = "test";

	ServerCache::Initialize( );
	ServerCache::Get( )->Add( address, 0 );

	EXPECT_TRUE( ServerCache::Get( )->Exists( address ) );

	ServerCache::Destroy( );
}

TEST( ServerCache_Tests, should_find_after_adding )
{
	ServerAdvertisement* ad = new ServerAdvertisement( "test", "", 0, 0, 0, "", 0 );

	ServerCache::Initialize( );
	ServerCache::Get( )->Add( "test", ad );

	IServerAdvertisement* result = ServerCache::Get( )->Find( 0 );

	EXPECT_EQ( ad, result );

	ServerCache::Destroy( );
}

TEST( ServerCache_Tests, should_have_correct_count_after_adding )
{
	ServerAdvertisement* ad = new ServerAdvertisement( "test", "", 0, 0, 0, "", 0 );

	ServerCache::Initialize( );
	ServerCache::Get( )->Add( "test", ad );

	int result = ServerCache::Get( )->GetCount( );

	EXPECT_EQ( 1, result );

	ServerCache::Destroy( );
}

TEST( ServerCache_Tests, should_clear_the_cache )
{
	ServerAdvertisement* ad = new ServerAdvertisement( "test", "", 0, 0, 0, "", 0 );

	ServerCache::Initialize( );
	ServerCache::Get( )->Add( "test", ad );

	ServerCache::Get( )->Clear( );
	int result = ServerCache::Get( )->GetCount( );

	EXPECT_EQ( 0, result );

	ServerCache::Destroy( );
}