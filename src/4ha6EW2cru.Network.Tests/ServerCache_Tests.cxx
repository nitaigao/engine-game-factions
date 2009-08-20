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

	m_subject->Add( address, 0 );

	EXPECT_TRUE( m_subject->Exists( address ) );
}

TEST_F( ServerCache_Tests, should_find_after_adding )
{
	ServerAdvertisement* ad = new ServerAdvertisement( "test", "", 0, 0, 0, "", 0 );

	m_subject->Add( "test", ad );

	IServerAdvertisement* result = m_subject->Find( 0 );

	EXPECT_EQ( ad, result );

	delete ad;
}

TEST_F( ServerCache_Tests, should_have_correct_count_after_adding )
{
	ServerAdvertisement* ad = new ServerAdvertisement( "test", "", 0, 0, 0, "", 0 );

	m_subject->Add( "test", ad );

	int result = m_subject->GetCount( );

	EXPECT_EQ( 1, result );

	delete ad;
}

TEST_F( ServerCache_Tests, should_clear_the_cache )
{
	ServerAdvertisement* ad = new ServerAdvertisement( "test", "", 0, 0, 0, "", 0 );

	m_subject->Add( "test", ad );

	m_subject->Clear( );
	int result = m_subject->GetCount( );

	EXPECT_EQ( 0, result );
}