#include "ProgramOptions.h"

namespace Platform
{
	bool ProgramOptions::HasOption( const std::string& optionName ) const
	{
		return true;
	}

	std::string ProgramOptions::GetOption( const std::string& optionName ) const
	{
		return "Hello";
	}
}