#include "Logger.h"

#include "../Exceptions/UnInitializedException.hpp"
#include "../Exceptions/AlreadyInitializedException.hpp"
#include "../Exceptions/NullReferenceException.hpp"

#include "../Events/EventData.hpp"
#include "../Events/Event.h"
using namespace Events;

#include "../Management/Management.h"

namespace Logging
{
	Logger* g_logger = 0;

	void Logger::Initialize( )
	{
		g_logger = new Logger( );
	}

	void Logger::Initialize( Logger* logger )
	{
		g_logger = logger;
	}

	void Logger::Release( )
	{
		delete g_logger;
		g_logger = 0;
	}

	Logger* Logger::Get( )
	{
		return g_logger;
	}

	void Logger::LogMessage( const std::string& level, const std::string& message )
	{
		if ( 0 == message.c_str( ) )
		{
			NullReferenceException e( "Logger::LogMessage - Attempted to Log a NULL message" );
			throw e;
		}

		std::stringstream outputMessage;
		outputMessage << level << ": " << message << "\n";

		if ( Management::IsInitialized( ) )
		{
			if( level != "DEBUG" && level != "NET" )
			{
				IEventData* eventData = new MessageLoggedEventData( outputMessage.str( ) );
				Management::Get( )->GetEventManager( )->QueueEvent( new Event( EventTypes::LOG_MESSAGE_APPENDED, eventData ) );
			}

			Management::Get( )->GetPlatformManager( )->OutputDebugMessage( outputMessage.str( ) );
			Management::Get( )->GetPlatformManager( )->OutputToConsole( outputMessage.str( ) );
		}
	}
}