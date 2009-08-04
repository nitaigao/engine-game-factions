#include "Win32PathInformation.h"

#include <Windows.h>
#include <shlobj.h>

#include <sstream>

#include "../Utility/StringUtils.h"
using namespace Utility;

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

namespace IO
{
	static const int TCHAR_MAX = 2048;
	static const std::string COMPANY_NAME = "Black Art Studios";
	static const std::string GAME_NAME = "Factions";

	void Win32PathInformation::Initialize( )
	{
		if( !exists( this->GetGlobalUserPath( ) ) )
		{
			create_directories( this->GetGlobalUserPath( ) );
		}

		if( !exists( this->GetGlobalScreenShotsPath( ) ) )
		{
			create_directories( this->GetGlobalScreenShotsPath( ) );
		}

		if( !exists( this->GetGlobalConfigPath( ) ) )
		{
			create_directories( this->GetGlobalConfigPath( ) );
		}
	}

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

	std::string Win32PathInformation::GetGlobalDevelopmentPath( ) const
	{
		return "../../../etc/data";
	}

	std::string Win32PathInformation::GetGlobalUserPath( ) const
	{
		TCHAR systemDirPath[ TCHAR_MAX ];
		SHGetFolderPath( 0, CSIDL_PERSONAL, 0, 0, systemDirPath );

		std::stringstream systemPath;
		systemPath << systemDirPath << "\\" << COMPANY_NAME << "\\" << GAME_NAME;

		return systemPath.str( );
	}

	std::string Win32PathInformation::GetGlobalScreenShotsPath() const
	{
		std::stringstream screenshotsPath;
		screenshotsPath << this->GetGlobalUserPath( ) << "\\" << "screenshots";
		return screenshotsPath.str( );
	}

	std::string Win32PathInformation::GetGlobalConfigPath() const
	{
		std::stringstream configPath;
		configPath << this->GetGlobalUserPath( ) << "\\" << "config";
		return configPath.str( );
	}
}