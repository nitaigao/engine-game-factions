#include <gtest/gtest.h>
using namespace testing;

#include "Maths/MathVector3.hpp"
using namespace Maths;

TEST( MathVector3_Tests, should_interpolate_by_the_amount_specified )
{
	MathVector3 subject( 0.0f, 1.0f, 0.0f );
	MathVector3 input( 0.0f, 0.0f, 0.0f );
	MathVector3 expected( 0.0f, 0.9f, 0.0f );

	MathVector3 result = subject.Interpolate( input, 0.1f );

	EXPECT_EQ( result, expected );
}