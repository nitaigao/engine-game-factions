#include <gtest/gtest.h>
using namespace testing;

#include "GeometrySystemComponent.h"
using namespace Geometry;

#include "Maths/MathVector3.hpp"
#include "Maths/MathQuaternion.hpp"
using namespace Maths;

#include "Mocks/MockStream.h"

class GeometrySystemComponent_Tests : public TestHarness< GeometrySystemComponent >
{

protected:

	std::string m_name;

	void EstablishContext( )
	{
		m_name = "test";
	}


	void DestroyContext( )
	{

	}

	GeometrySystemComponent* CreateSubject( )
	{
		return new GeometrySystemComponent( m_name );
	}
};

TEST_F( GeometrySystemComponent_Tests, should_serialize_component )
{
	MockStream stream;

	MathVector3 position = MathVector3::Forward( );
	MathQuaternion orientation = MathQuaternion::Identity( );

	m_subject->SetAttribute( System::Attributes::Position, position );
	m_subject->SetAttribute( System::Attributes::Orientation, orientation );
	m_subject->SetAttribute( System::Attributes::SystemType, System::Types::GEOMETRY );

	EXPECT_CALL( stream, Write( ( int ) System::Types::GEOMETRY ) );
	EXPECT_CALL( stream, Write( position ) );
	EXPECT_CALL( stream, Write( orientation ) );

	m_subject->Serialize( &stream );
}

void ReturnVector( MathVector3& data ) { data = MathVector3::Forward( ); };
void ReturnQuaternion( MathQuaternion& data ) { data = MathQuaternion::Identity( ); };

TEST_F( GeometrySystemComponent_Tests, should_deserialize_component )
{
	MockStream stream;

	EXPECT_CALL( stream, Read( A< MathVector3& >( ) ) ).WillOnce( Invoke( ReturnVector ) );
	EXPECT_CALL( stream, Read( A< MathQuaternion& >( ) ) ).WillOnce( Invoke( ReturnQuaternion ) );

	m_subject->DeSerialize( &stream );
}