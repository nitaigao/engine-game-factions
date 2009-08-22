#include <gtest/gtest.h>
using namespace testing;

#include "State/EntityService.h"
using namespace State;

#include "../Mocks/MockWorld.hpp"
#include "../Mocks/MockStream.h"

#include "IO/IStream.hpp"
using namespace IO;

TEST( EntityService_Tests, should_deserialize_when_messaged )
{
	MockStream stream;
	MockWorld world;

	EXPECT_CALL( world, DeSerialize( &stream ) );

	EntityService service( &world );

	AnyType::AnyTypeMap parameters;
	parameters[ System::Parameters::IO::Stream ] = static_cast< IO::IStream* >( &stream );

	service.ProcessMessage( System::Messages::Entity::DeSerializeWorld, parameters );
}

TEST( EntityService_Tests, should_serialize_when_messaged )
{
	MockStream stream;
	MockWorld world;

	EXPECT_CALL( world, Serialize( &stream ) );

	EntityService service( &world );

	AnyType::AnyTypeMap parameters;
	parameters[ System::Parameters::IO::Stream ] = static_cast< IO::IStream* >( &stream );

	service.ProcessMessage( System::Messages::Entity::SerializeWorld, parameters );
}

TEST( EntityService_Tests, should_create_entity_when_messaged )
{
	MockStream stream;
	MockWorld world;

	EXPECT_CALL( world, CreateEntity( A< const std::string& >( ), A< const std::string& >( ), A< const std::string& >( ) ) );

	EntityService service( &world );

	AnyType::AnyTypeMap parameters;
	parameters[ System::Attributes::Name ] = "testName";
	parameters[ System::Attributes::EntityType ] = "testType";
	parameters[ System::Attributes::FilePath ] = "testPath";

	service.ProcessMessage( System::Messages::Entity::CreateEntity, parameters );
}

TEST( EntityService_Tests, should_destroy_entity_when_messaged )
{
	MockStream stream;
	MockWorld world;

	EXPECT_CALL( world, DestroyEntity( A< const std::string& >( ) ) );

	EntityService service( &world );

	AnyType::AnyTypeMap parameters;
	parameters[ System::Attributes::Name ] = "testName";

	service.ProcessMessage( System::Messages::Entity::DestroyEntity, parameters );
}