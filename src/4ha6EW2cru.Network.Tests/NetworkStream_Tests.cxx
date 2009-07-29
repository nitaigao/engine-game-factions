#include <gtest/gtest.h>
using namespace testing;

#include "NetworkStream.h"
using namespace Network;

#include "Maths/MathVector3.hpp"
using namespace Maths;

TEST( NetworkStream_Tests, writes_and_read_a_string )
{
	NetworkStream netStream;

	std::string helloWorld = "hello world";

	netStream.Write( helloWorld );

	netStream.SetReadPosition( 0 );

	std::string returnValue;

	netStream.Read( returnValue );

	EXPECT_EQ( helloWorld, returnValue );
}

TEST( NetworkStream_Tests, writes_and_read_multiple_strings )
{
	NetworkStream netStream;
	
	std::string firstString = "12345";
	std::string secondString = "0987642";

	netStream.Write( firstString );
	netStream.Write( secondString );

	netStream.SetReadPosition( 0 );

	std::string firstStringResult;
	std::string secondStringResult;

	netStream.Read( firstStringResult );
	netStream.Read( secondStringResult );

	EXPECT_EQ( firstString, firstStringResult );
	EXPECT_EQ( secondString, secondStringResult );
}

TEST( NetworkStream_Tests, should_write_vector )
{
	NetworkStream netStream;

	MathVector3 position( 1, 2, 3 );

	netStream.Write( position );

	EXPECT_TRUE( netStream.GetLength( ) > 0 );
}

TEST( NetworkStream_Tests, should_write_and_read_vector )
{
	NetworkStream netStream;

	MathVector3 position( 1, 2, 3 );

	netStream.Write( position );
	netStream.SetReadPosition( 0 );

	MathVector3 result;

	netStream.Read( result );

	EXPECT_EQ( position, result );
}

TEST( NetworkStream_Tests, should_write_a_float )
{
	NetworkStream netStream;

	netStream.Write( 1.0f );

	EXPECT_TRUE( netStream.GetLength( ) > 0 );
}

TEST( NetworkStream_Tests, should_write_and_read_a_float )
{
	NetworkStream netStream;

	float expected = 1.0f;

	netStream.Write( expected );

	netStream.SetReadPosition( 0 );

	float result;

	netStream.Read( result );

	EXPECT_EQ( expected, result );
}

TEST( NetworkStream_Tests, should_write_and_read_multiple_floats )
{
	NetworkStream netStream;

	float expected1 = 1.0f;
	float expected2 = 99.555f;

	netStream.Write( expected1 );
	netStream.Write( expected2 );

	netStream.SetReadPosition( 0 );

	float result1, result2;

	netStream.Read( result1 );
	netStream.Read( result2 );

	EXPECT_EQ( expected1, result1 );
	EXPECT_EQ( expected2, result2 );
}

TEST( NetworkStream_Tests, should_write_and_read_a_zero_float )
{
	NetworkStream netStream;

	float expected = 0.0f;

	netStream.Write( expected );

	netStream.SetReadPosition( 0 );

	float result;

	netStream.Read( result );

	EXPECT_EQ( expected, result );
}

TEST( NetworkStream_Tests, should_write_and_read_a_zero_in_the_middle_of_the_stream )
{
	NetworkStream netStream;

	float expected = 0.0f;

	std::string expected1( "hello World" );
	float expected2 = 0.0f;
	std::string expected3 = "blah blah blahhhhhh";

	netStream.Write( expected1 );
	netStream.Write( expected2 );
	netStream.Write( expected3 );

	netStream.SetReadPosition( 0 );

	std::string result1;
	float result2;
	std::string result3;

	netStream.Read( result1 );
	netStream.Read( result2 );
	netStream.Read( result3 );

	EXPECT_EQ( expected1, result1 );
	EXPECT_EQ( expected2, result2 );
	EXPECT_EQ( expected3, result3 );
}