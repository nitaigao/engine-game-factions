#include <gtest/gtest.h>
using namespace testing;

#include "IO/WIn32PathInformation.h"
using namespace IO;

TEST( WIn32PathInformation_Tests, should_return_the_game_data_directory )
{
	IPathInformation* pathInformation = new Win32PathInformation( );
	std::string dataPath = pathInformation->GetGlobalDataPath( );
	int dataPathLength = dataPath.length( );
	EXPECT_TRUE( dataPathLength > 3 );

	delete pathInformation;
}

TEST( Win32PathInformation_Tests, should_return_the_development_data_directory )
{
	IPathInformation* pathInformation = new Win32PathInformation( );
	std::string dataPath = pathInformation->GetGlobalDevelopmentPath( );
	int dataPathLength = dataPath.length( );
	EXPECT_TRUE( dataPathLength > 3 );

	delete pathInformation;
}

TEST( Win32PathInformation_Tests, should_return_the_local_data_directory_path )
{
	IPathInformation* pathInformation = new Win32PathInformation( );
	std::string dataPath = pathInformation->GetLocalDataPath( );
	int dataPathLength = dataPath.length( );
	EXPECT_TRUE( dataPathLength > 3 );

	delete pathInformation;
}

TEST( Win32PathInformation_Tests, should_return_the_local_config_directory_path )
{
	IPathInformation* pathInformation = new Win32PathInformation( );
	std::string dataPath = pathInformation->GetLocalConfigPath( );
	int dataPathLength = dataPath.length( );
	EXPECT_TRUE( dataPathLength > 3 );

	delete pathInformation;
}

TEST( Win32PathInformation_Tests, should_return_the_user_data_directory )
{
	IPathInformation* pathInformation = new Win32PathInformation( );
	std::string dataPath = pathInformation->GetGlobalUserPath( );
	int dataPathLength = dataPath.length( );
	EXPECT_TRUE( dataPathLength > 3 );

	delete pathInformation;
}

TEST( Win32PathInformation_Tests, should_return_the_user_screenshots_directory )
{
	IPathInformation* pathInformation = new Win32PathInformation( );
	std::string dataPath = pathInformation->GetGlobalScreenShotsPath( );
	int dataPathLength = dataPath.length( );
	EXPECT_TRUE( dataPathLength > 3 );

	delete pathInformation;
}

TEST( Win32PathInformation_Tests, should_return_the_user_config_directory )
{
	IPathInformation* pathInformation = new Win32PathInformation( );
	std::string dataPath = pathInformation->GetGlobalConfigPath( );
	int dataPathLength = dataPath.length( );
	EXPECT_TRUE( dataPathLength > 3 );

	delete pathInformation;
}