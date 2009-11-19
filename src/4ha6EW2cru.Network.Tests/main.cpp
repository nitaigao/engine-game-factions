#include <gtest/gtest.h>

#include "TestEnvironment.hpp"

#ifdef _DEBUG
#	define _CRTDBG_MAP_ALLOC 
#	define _CRTDBG_MAP_ALLOC_NEW 
#	define new new ( _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif


int main( int argc, char **argv ) 
{
#ifdef _DEBUG
	//_crtBreakAlloc = 7230;
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 
#endif

	::testing::InitGoogleTest( &argc, argv );
	::testing::AddGlobalTestEnvironment( new Testing::Environment( ) );
	return RUN_ALL_TESTS( );
}