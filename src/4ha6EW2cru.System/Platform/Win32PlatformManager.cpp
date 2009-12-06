#include "Win32PlatformManager.h"

#include "../Events/Event.h"
#include "../Management/Management.h"

#include <windows.h>

#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

#include <Rpc.h>
#include <shellapi.h>

#include <boost/program_options.hpp>
using namespace boost::program_options;

#include "../Logging/Logger.h"
using namespace Logging;

#include "../IO/Win32PathInformation.h"
using namespace IO;

LRESULT CALLBACK WindowProcedure( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{

	case WM_DESTROY:

		PostQuitMessage( 0 );
		return 0;

	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}

namespace Platform
{
	Win32PlatformManager::~Win32PlatformManager()
	{
		if ( 0 != m_pathInformation )
		{
			delete m_pathInformation;
			m_pathInformation = 0;
		}
	}

	Win32PlatformManager::Win32PlatformManager()
	{
		m_hWnd = 0;
		m_pathInformation = new Win32PathInformation( );
	}

	void Win32PlatformManager::Initialize()
	{
		m_pathInformation->Initialize( );
	}

	void Win32PlatformManager::CreateInteractiveWindow( const std::string& title, int width, int height, bool fullScreen )
	{
		WNDCLASSEX wnd;

		wnd.cbSize = sizeof( WNDCLASSEX );
		wnd.style = CS_HREDRAW | CS_VREDRAW;

		wnd.lpfnWndProc = WindowProcedure;
		wnd.cbClsExtra = 0;
		wnd.cbWndExtra = 0;
		wnd.hInstance = GetModuleHandle( NULL );
		wnd.hIcon = NULL;
		wnd.hCursor = NULL;
		wnd.hbrBackground = GetSysColorBrush( COLOR_BTNFACE );
		wnd.lpszMenuName = NULL;
		wnd.lpszClassName = "WindowClassName";
		wnd.hIconSm = LoadIcon( NULL,IDI_APPLICATION );

		RegisterClassEx(&wnd);

		int screenWidth = GetSystemMetrics( SM_CXSCREEN ) ;
		int screenHeight = GetSystemMetrics( SM_CYSCREEN ) ;

		m_hWnd = ( size_t ) CreateWindowExA( WS_EX_CONTROLPARENT, "WindowClassName", title.c_str( ),
			( fullScreen ) ? WS_POPUP | WS_EX_TOPMOST : WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
			( screenWidth - width ) / 2,  ( screenHeight - height ) / 2, width, height, NULL, NULL, GetModuleHandle( NULL ), NULL );
	}

	static const WORD MAX_CONSOLE_LINES = 500;

	void Win32PlatformManager::CreateConsoleWindow( )
	{
		AllocConsole( );

		long lStdHandle = ( long )GetStdHandle( STD_OUTPUT_HANDLE );
		int hConHandle = _open_osfhandle( lStdHandle, _O_TEXT );
	}

	void Win32PlatformManager::OutputToConsole( const std::string& message )
	{
		std::streambuf* existingBuffer = std::cout.rdbuf( );
		std::ofstream newBuffer( "CONOUT$" );

		std::cout.rdbuf( newBuffer.rdbuf( ) );
		std::cout.sync_with_stdio( );

		std::cout << message.c_str( );

		std::cout.rdbuf( existingBuffer );
	}

	void Win32PlatformManager::Update( float deltaMilliseconds )
	{
		MSG msg;

		while ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			if ( msg.message == WM_QUIT )
			{
				Management::Get( )->GetEventManager( )->QueueEvent( new Events::Event( Events::EventTypes::GAME_QUIT ) );
			}

			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}

	void Win32PlatformManager::CloseWindow( )
	{
		DestroyWindow( ( HWND ) m_hWnd );
	}

	size_t Win32PlatformManager::GetWindowId( ) const
	{
		if ( m_hWnd == 0 )
		{
			return ( size_t ) GetConsoleWindow( );
		}

		return m_hWnd; 
	}

	void Win32PlatformManager::OutputDebugMessage( const std::string& message )
	{
		OutputDebugString( message.c_str( ) );
	}

	AnyType::AnyTypeMap Win32PlatformManager::GetProgramOptions( ) const
	{
		/*int argc = 0;
		LPWSTR* args = CommandLineToArgvW( GetCommandLineW( ), &argc );

		char** argv = new char*[ argc ];

		for ( int i = 0; i < argc; i++ )
		{
			argv[ i ] = new char[ 20480 ];
			WideCharToMultiByte( CP_UTF8, 0, args[ i ], -1, ( LPSTR ) argv[ i ], 20480, 0, 0 );
		}

		CmdLine cmd( "Command Line Options" );

		ValueArg< std::string > levelNameArg( "l", System::Options::LevelName.c_str( ), "The Level to Load", false, "", "string" );
		cmd.add( levelNameArg );

		SwitchArg dedicatedServerArg( "d", System::Options::DedicatedServer.c_str( ), "Run as a Dedicated Server", false );
		cmd.add( dedicatedServerArg );

		cmd.parse( argc, argv );

		AnyType::AnyTypeMap programOptions;

		if ( !levelNameArg.getValue( ).empty( ) )
		{
			programOptions[ System::Options::LevelName.c_str( ) ] = levelNameArg.getValue( );
		}

		if ( dedicatedServerArg.getValue( ) )
		{
			programOptions[ System::Options::DedicatedServer.c_str( ) ] = dedicatedServerArg.getValue( );
		}

		for ( int i = 0; i < argc; i++ )
		{
			delete[ ] argv[ i ];
		}

		delete[ ] argv;

		return programOptions;*/
		return AnyType::AnyTypeMap( );
	}

	std::string Win32PlatformManager::GenUUID() const
	{
		UUID uuid;

		ZeroMemory( &uuid, sizeof( UUID ) );

		UuidCreate( &uuid );

		RPC_CSTR uuidChar;
		UuidToString( &uuid, &uuidChar );

		std::stringstream uuidString;
		uuidString << uuidChar;

		return uuidString.str( );
	}
}