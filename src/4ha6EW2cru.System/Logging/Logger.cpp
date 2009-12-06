#include "Logger.h"

#include "../Exceptions/UnInitializedException.hpp"
#include "../Exceptions/AlreadyInitializedException.hpp"
#include "../Exceptions/NullReferenceException.hpp"

#include "../Events/EventData.hpp"
#include "../Events/Event.h"
using namespace Events;

namespace Logging
{
	Logger* g_logger = 0;

	void Logger::Initialize( Platform::IPlatformManager* platformManager )
	{
		if ( g_logger == 0 )
		{
			g_logger = new Logger( platformManager );
		}
	}

	void Logger::Initialize( Logger* logger )
	{
		//g_logger = logger;
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

#ifndef _DEBUG

			if( level != "DEBUG" && level != "NET" )
			{
				IEventData* eventData = new UIEventData( EventTypes::LOG_MESSAGE_APPENDED, outputMessage.str( ), "" );
				Management::Get( )->GetEventManager( )->QueueEvent( new Event( EventTypes::LOG_MESSAGE_APPENDED, eventData ) );
			}
#endif
			m_platformManager->OutputDebugMessage( outputMessage.str( ) );
			m_platformManager->OutputToConsole( outputMessage.str( ) );
	}
}