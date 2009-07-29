/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   EventData.hpp
*  @date   2009/04/25
*/
#pragma once
#ifndef EVENTDATA_H
#define EVENTDATA_H

#include "IEventData.hpp"

namespace Events
{
	class ScriptCommandEventData : public IEventData
	{

	public:

		/*! Default Destructor
		*
		*  @return ()
		*/
		~ScriptCommandEventData( ){ };


		/*! Default Constructor
		 *
		 *  @param[in] const std::string command
		 *  @return ()
		 */
		explicit ScriptCommandEventData( const std::string& command )
			: m_command( command )
		{

		}


		/*! Returns the command that has been executed
		 *
		 *  @return (std::string)
		 */
		inline std::string GetCommand( ) { return m_command; };

	private:

		std::string m_command;

		ScriptCommandEventData( ) { };
		ScriptCommandEventData( const ScriptCommandEventData & copy ) { };
		ScriptCommandEventData & operator = ( const ScriptCommandEventData & copy ) { return *this; };

	};

	class LevelChangedEventData : public IEventData
	{

	public:

		/*! Default Destructor
		*
		*  @return ()
		*/
		~LevelChangedEventData( ) { };


		/*! Default Constructor
		 *
		 *  @param[in] const std::string levelName
		 *  @return ()
		 */
		explicit LevelChangedEventData( const std::string& levelName )
			: m_levelName( levelName )
		{

		}

		
		/*! Returns the name of the level requested
		 *
		 *  @return (std::string)
		 */
		inline std::string GetLevelName( ) { return m_levelName; };

	private:

		std::string m_levelName;

		LevelChangedEventData( ) { };
		LevelChangedEventData( const LevelChangedEventData & copy ) { };
		LevelChangedEventData & operator = ( const LevelChangedEventData & copy ) { return *this; };

	};

	class MessageLoggedEventData : public IEventData
	{

	public:

		/*! Default Destructor
		*
		*  @return ()
		*/
		~MessageLoggedEventData( ) { };


		/*! Default Constructor
		 *
		 *  @param[in] const std::string message
		 *  @return ()
		 */
		explicit MessageLoggedEventData( const System::Message& message )
			: m_message( message )
		{

		}

		
		/*! Returns the message that has been logged
		 *
		 *  @return (std::string)
		 */
		inline std::string GetMessage( ) { return m_message; };

	private:

		std::string m_message;

		MessageLoggedEventData( ) { };
		MessageLoggedEventData( const MessageLoggedEventData & copy ) { };
		MessageLoggedEventData & operator = ( const MessageLoggedEventData & copy ) { return *this; };


	};
};

#endif
