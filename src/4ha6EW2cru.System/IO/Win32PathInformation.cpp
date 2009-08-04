#include "Win32PathInformation.h"

#include <Windows.h>

#include <sstream>

#include "../Utility/StringUtils.h"
using namespace Utility;


namespace IO
{
	static const int TCHAR_MAX = 2048;

	std::string Win32PathInformation::GetGlobalDataPath( ) const
	{
		TCHAR modulePath[ TCHAR_MAX ];
		GetModuleFileName( 0, modulePath, TCHAR_MAX );

		std::stringstream exePath;
		exePath << modulePath;

		std::string binName = "bin";

		int binIndex = exePath.str( ).rfind( binName.c_str( ) );
		

		std::string folderPath = exePath.str( ).substr( 0, binIndex );

		std::stringstream dataPath;
		dataPath << folderPath << "data";

		return dataPath.str( );
	}

	std::string Win32PathInformation::GetLocalDataPath() const
	{
		return "/data";
	}

	std::string Win32PathInformation::GetGlobalDevelopmentPath( ) const
	{
		return "../../../etc/data";
	}
}