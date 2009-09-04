/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   EventType.hpp
*  @date   2009/04/25
*/
#pragma once
#ifndef EVENTTYPE_H
#define EVENTTYPE_H

#include <string>

namespace Events
{
	typedef std::string EventType;

	namespace EventTypes
	{
		static const EventType ALL_EVENTS					=	"ALL_EVENTS";
		static const EventType TEST_EVENT					=	"TEST_EVENT";
		static const EventType GAME_INITIALIZED				=	"GAME_INITIALIZED";
		static const EventType GAME_LEVEL_CHANGED			=	"GAME_LEVEL_CHANGED";
		static const EventType GAME_QUIT					=	"GAME_QUIT";
		static const EventType GAME_ENDED					=	"GAME_ENDED";
		static const EventType INPUT_KEY_UP					=	"INPUT_KEY_UP";
		static const EventType INPUT_KEY_DOWN				=	"INPUT_KEY_DOWN";
		static const EventType INPUT_MOUSE_PRESSED			=	"INPUT_MOUSE_PRESSED";
		static const EventType INPUT_MOUSE_RELEASED			=	"INPUT_MOUSE_RELEASED";
		static const EventType INPUT_MOUSE_MOVED			=	"INPUT_MOUSE_MOVED";
		static const EventType GRAPHICS_SETTINGS_CHANGED	=	"GRAPHICS_SETTINGS_CHANGED";
		static const EventType UI_EVENT						=	"UI_EVENT";
		static const EventType LOG_MESSAGE_APPENDED			=	"LOG_MESSAGE_APPENDED";
		static const EventType SCRIPT_COMMAND_EXECUTED		=	"SCRIPT_COMMAND_EXECUTED";
		static const EventType EVENTTYPE_MAX				=	"EVENTTYPE_MAX";
	}
};

#endif

