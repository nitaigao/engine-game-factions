#include <gtest/gtest.h>
using namespace testing;

#include "NetworkStream.h"
using namespace Network;

#include <BitStream.h>
using namespace RakNet;

TEST( NetworkStream_Tests, should_write_strings_to_the_underlying_bit_stream )
{
	BitStream underlyingStream;
	NetworkStream stream( &underlyingStream );

	std::string expected = "test";

	stream.Write( expected );

	RakString result;
	underlyingStream.Read( result );

	EXPECT_EQ( expected, result.C_String( ) );
}


TEST( NetworkStream_Tests, should_write_integers_to_the_underlying_bit_stream )
{
	BitStream underlyingStream;
	NetworkStream stream( &underlyingStream );

	int expected = 99;

	stream.Write( expected );

	int result;
	underlyingStream.Read( result );

	EXPECT_EQ( expected, result );
}

TEST( NetworkStream_Tests, should_read_strings_from_the_underlying_bit_stream )
{
	std::string expected = "hello";

	BitStream underlyingStream;
	underlyingStream.Write( RakString( expected ) );

	NetworkStream stream( &underlyingStream );
	std::string result;
	stream.Read( result );

	EXPECT_EQ( expected, result );
}

TEST( NetworkStream_Tests, should_read_integers_from_the_underlying_bit_stream )
{
	int expected = 99;

	BitStream underlyingStream;
	underlyingStream.Write( expected );

	NetworkStream stream( &underlyingStream );
	int result;
	stream.Read( result );

	EXPECT_EQ( expected, result );
}