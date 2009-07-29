#include <gtest/gtest.h>
using namespace testing;

#include "IO/MemoryStream.h"
using namespace IO;

TEST(  MemoryStream_Tests, should_advance_the_position_on_write )
{
	MemoryStream netStream;

	std::string helloWorld = "hello world";

	netStream.Write( ( void* ) helloWorld.c_str( ), helloWorld.length( ) );

	EXPECT_EQ( helloWorld.length( ), netStream.GetWritePosition( ) );
}

TEST( MemoryStream_Tests, should_write_to_internal_memory )
{
	MemoryStream netStream;

	std::string helloWorld = "hello world";

	netStream.Write( ( void* ) helloWorld.c_str( ), helloWorld.length( ));

	char* data = new char[ helloWorld.length( ) ];

	netStream.Read( ( void* ) data, helloWorld.length( ), 0 );

	EXPECT_EQ( helloWorld.c_str( )[ 0 ], data[ 0 ] );
	EXPECT_EQ( helloWorld.c_str( )[ helloWorld.length( ) - 1 ], data[ helloWorld.length( ) - 1 ] );

	delete[ ] data;
}

TEST( MemoryStream_Tests, should_repeatedly_write_to_memory )
{
	MemoryStream netStream;

	std::string helloWorld = "hello world";

	int count = rand( ) % 100;

	for ( int i = 0; i < count; i++ )
	{
		netStream.Write( ( void* ) helloWorld.c_str( ), helloWorld.length( ) );
	}

	for ( int i = 0; i < count; i++ )
	{
		char* data = new char[ helloWorld.length( ) ];

		netStream.Read( ( void* ) data, helloWorld.length( ), i * helloWorld.length( ) );

		EXPECT_EQ( helloWorld.c_str( )[ 0 ], data[ 0 ] );
		EXPECT_EQ( helloWorld.c_str( )[ helloWorld.length( ) - 1 ], data[ helloWorld.length( ) - 1 ] );

		delete[ ] data;
	}
}

TEST( MemoryStream_Tests, returns_correct_length_after_writing_data )
{
	MemoryStream netStream;

	std::string helloWorld = "hello world";

	netStream.Write( ( void* )helloWorld.c_str( ), helloWorld.length( ) );

	EXPECT_EQ( helloWorld.length( ), netStream.GetLength( ) );
}

TEST( MemoryStream_Tests, should_read_one_chunk_after_another )
{
	std::string firstChunk = "first";
	std::string secondChunk = "second";

	MemoryStream stream;
	stream.Write( ( void* )firstChunk.c_str( ), firstChunk.length( ) );
	stream.Write( ( void* )secondChunk.c_str( ), secondChunk.length( ) );

	char* firstChunkResult = new char[ firstChunk.length( ) + 1 ];
	char* secondChunkResult = new char[ secondChunk.length( ) + 1 ];

	stream.Read( firstChunkResult, firstChunk.length( ), 0 );
	stream.Read( secondChunkResult, secondChunk.length( ), firstChunk.length( ) );

	firstChunkResult[ firstChunk.length( ) ] = '\0';
	secondChunkResult[ secondChunk.length( ) ] = '\0';

	EXPECT_EQ( firstChunk, std::string( firstChunkResult ) );
	EXPECT_EQ( secondChunk, std::string( secondChunkResult ) );

	delete[ ] firstChunkResult;
	delete[ ] secondChunkResult;
}


TEST( MemoryStream_Tests, should_understand_that_it_is_empty )
{
	MemoryStream emptyStream;

	EXPECT_TRUE( emptyStream.IsEmpty( ) );
}

TEST( MemoryStream_Tests, should_understand_that_it_is_not_empty )
{
	std::string firstChunk = "first";

	MemoryStream dataStream;
	dataStream.Write( ( void* )firstChunk.c_str( ), firstChunk.length( ) );

	EXPECT_FALSE( dataStream.IsEmpty( ) );
}

TEST( MemoryStream_Tests, should_transfer_to_another_stream )
{
	std::string expected = "first";

	MemoryStream stream;
	stream.Write( ( void* ) expected.c_str( ), expected.length( ) );

	char* newData = new char[ stream.GetLength( ) ];
	stream.CopyData( newData );

	MemoryStream newStream;
	newStream.Write( newData, stream.GetLength( ) );

	EXPECT_EQ( stream.GetLength( ), newStream.GetLength( ) );

	delete[ ] newData;
}

TEST( MemoryStream_Tests, should_copy_data_from_inside_the_stream )
{
	std::string expected = "first";

	MemoryStream stream;
	stream.Write( ( void* )expected.c_str( ), expected.length( ) );

	char* newData = new char[ stream.GetLength( ) ];
	stream.CopyData( newData );

	EXPECT_TRUE( strlen( newData ) > 0 );

	delete[ ] newData;
}