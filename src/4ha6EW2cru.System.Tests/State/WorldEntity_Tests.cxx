#include <gtest/gtest.h>
using namespace testing;

#include "State/WorldEntity.h"
using namespace State;

#include "../Mocks/MockStream.h"

class WorldEntity_Tests : public TestHarness< WorldEntity >
{

protected:

	std::string m_entityName;

	void EstablishContext( )
	{
		m_entityName = "test";
	}


	void DestroyContext( )
	{

	}

	WorldEntity* CreateSubject( )
	{
		return new WorldEntity( m_entityName );
	}
};

TEST_F( WorldEntity_Tests, should_serialize_an_entity_with_a_name )
{
	MockStream stream;
	EXPECT_CALL( stream, Write( m_entityName ) );

	m_subject->Serialize( &stream );
}

TEST_F( WorldEntity_Tests, should_serialize_an_entity_with_a_type_attribute )
{
	std::string type = "test";

	MockStream stream;
	EXPECT_CALL( stream, Write( A< const std::string& >( ) ) )
		.Times( 2 );
	EXPECT_CALL( stream, Write( 1 ) ); 

	m_subject->SetAttribute( System::Attributes::EntityType, type );
	m_subject->Serialize( &stream );
}

TEST_F( WorldEntity_Tests, should_serialize_sub_components )
{
	//TODO: start here.
}
