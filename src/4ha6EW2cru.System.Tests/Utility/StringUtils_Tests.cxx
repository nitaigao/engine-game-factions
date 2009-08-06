#include <gtest/gtest.h>
using namespace testing;

#include "Utility/StringUtils.h"
using namespace Utility;

TEST( StringUtils_Tests, should_replace_characters_in_a_string )
{
	std::string input = "C:/Test/";
	std::string result = StringUtils::Replace( input, "/", "\\" );

	EXPECT_TRUE( result.find( "/" ) == std::string::npos && !result.empty( ) );
}

TEST( StringUtils_Tests, should_not_replace_characters_in_a_string )
{
	std::string input = "C:/Test/";
	std::string result = StringUtils::Replace( input, "&", "\\" );

	EXPECT_TRUE( result.find( "/" ) == input.find( "/" ) && !result.empty( ) );
}

TEST( StringVector_Tests, should_convert_int_to_string )
{
	int input = 10;

	std::string actual = StringUtils::ToString( input );

	std::stringstream expected;
	expected << input;

	EXPECT_EQ( expected.str( ), actual );
}