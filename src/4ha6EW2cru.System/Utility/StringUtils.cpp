#include "StringUtils.h"

#include <sstream>

namespace Utility
{
	std::string StringUtils::Replace( const std::string& input, const std::string& oldString, const std::string& newString )
	{
		std::string result = input;

		for( int index = result.find( oldString ); index != std::string::npos; index = result.find( oldString ) )
		{
			result.replace( index, newString.length( ), newString.c_str( ) );
		}

		return result;
	}

	std::string StringUtils::ToString( const int& input )
	{
		std::stringstream result;
		result << input;
		return result.str( );
	}
}