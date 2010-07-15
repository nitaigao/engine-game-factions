#include "precompiled.h"
#include "OSXPathInformation.h"

#include <sstream>

#include "../Utility/StringUtils.h"
using namespace Utility;

namespace IO
{

	void OSXPathInformation::Initialize( )
	{
		
	}

	std::string OSXPathInformation::GetGlobalDataPath( ) const
	{
		return "";
	}

	std::string OSXPathInformation::GetGlobalDevelopmentPath( ) const
	{
		return "";
	}

	std::string OSXPathInformation::GetGlobalUserPath( ) const
	{
    return "";
	}

	std::string OSXPathInformation::GetGlobalScreenShotsPath() const
	{
    return "";
  }

	std::string OSXPathInformation::GetGlobalConfigPath() const
	{
    return "~/Desktop/config.ini";
	}
}