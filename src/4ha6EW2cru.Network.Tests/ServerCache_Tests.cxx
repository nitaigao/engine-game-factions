#include <gtest/gtest.h>
using namespace testing;

#include "ServerCache.h"
#include "ServerAdvertisement.hpp"
using namespace Network;

class ServerCache_Tests : public TestHarness< ServerCache >
{
	ServerCache* CreateSubject( )
	{
		return new ServerCache( );
	}
};

TEST_F( ServerCache_Tests, should_exist_after_adding )
{
	std::string address = "test";

	m_subject->Add( "servername", "map", 10, 1, 0, address, 8989 );

	EXPECT_TRUE( m_subject->Exists( address ) );
}

TEST_F( ServerCache_Tests, should_find_after_adding )
{
	std::string serverName = "serverName";
	m_subject->Add( serverName, "map", 10, 1, 0, "127.0.0.1", 8989 );

	IServerAdvertisement* result = m_subject->Find( 0 );

	EXPECT_EQ( serverName, result->GetServerName( ) );
}

TEST_F( ServerCache_Tests, should_have_correct_count_after_adding )
{
	m_subject->Add( "servername", "map", 10, 1, 0, "127.0.0.1", 8989 );

	int result = m_subject->GetCount( );

	EXPECT_EQ( 1, result );
}

TEST_F( ServerCache_Tests, should_clear_the_cache )
{
	m_subject->Add( "servername", "map", 10, 1, 0, "127.0.0.1", 8989 );

	m_subject->Clear( );
	int result = m_subject->GetCount( );

	EXPECT_EQ( 0, result );
}