#include <gtest/gtest.h>
using namespace testing;

#include <gmock/gmock.h>

#include "../Mocks/MockStream.h"

#include "State/WorldEntity.h"
using namespace State;

TEST( World_Tests, should_serialize_entity )
{
	std::string entityName = "test";

	int hasFile = 0;

	MockStream stream;
	EXPECT_CALL( stream, Write( entityName ) );
	EXPECT_CALL( stream, Write( hasFile ) );

	WorldEntity entity( entityName );
	entity.Serialize( &stream );
}