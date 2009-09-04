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
#include "../System/SystemType.hpp"

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

	class UIEventData : public IEventData
	{
	
	public:

		/*! Default Destructor
		*
		*  @return ()
		*/
		~UIEventData( ) { };


		/*! Default Constructor
		*
		*  @param[in] const std::string levelName
		*  @return ()
		*/
		UIEventData( const std::string& eventName )
			: m_eventName( eventName ) 
		{

		}

		/*! Default Constructor
		*
		*  @param[in] const std::string levelName
		*  @return ()
		*/
		UIEventData( const std::string& eventName, const std::string& parameter1 )
			: m_eventName( eventName ) 
			, m_parameter1( parameter1 )
		{

		}


		/*! Default Constructor
		*
		*  @param[in] const std::string levelName
		*  @return ()
		*/
		UIEventData( const std::string& eventName, int parameter1 )
			: m_eventName( eventName ) 
		{
			std::stringstream param1;
			param1 << parameter1;
			m_parameter1 = param1.str( );
		}


		/*! Default Constructor
		*
		*  @param[in] const std::string levelName
		*  @return ()
		*/
		UIEventData( const std::string& eventName, const std::string& parameter1, const std::string& parameter2 )
			: m_eventName( eventName ) 
			, m_parameter1( parameter1 )
			, m_parameter2( parameter2 )
		{

		}


		/*! Default Constructor
		*
		*  @param[in] const std::string levelName
		*  @return ()
		*/
		UIEventData( const std::string& eventName, int parameter1, int parameter2 )
			: m_eventName( eventName ) 
		{
			std::stringstream param1;
			param1 << parameter1;
			m_parameter1 = param1.str( );

			std::stringstream param2;
			param2 << parameter2;
			m_parameter2 = param2.str( );
		}


		/*! Default Constructor
		*
		*  @param[in] const std::string levelName
		*  @return ()
		*/
		UIEventData( const std::string& eventName, const std::string& parameter1, int parameter2 )
			: m_eventName( eventName ) 
			, m_parameter1( parameter1 )
		{
			std::stringstream param2;
			param2 << parameter2;
			m_parameter2 = param2.str( );
		}


		/*! Default Constructor
		*
		*  @param[in] const std::string levelName
		*  @return ()
		*/
		UIEventData( const std::string& eventName, int parameter1, const std::string& parameter2 )
			: m_eventName( eventName ) 
			, m_parameter2( parameter2 )
		{
			std::stringstream param1;
			param1 << parameter1;
			m_parameter1 = param1.str( );
		}


		/*! Returns the name of the Event
		 *
		 * @return ( std::string )
		 */
		inline std::string GetEventName( ) { return m_eventName; };


		/*! Returns parameter 1
		*
		*  @return (std::string)
		*/
		inline std::string GetParameter1( ) { return m_parameter1; };


		/*! Returns parameter 1
		*
		*  @return (std::string)
		*/
		inline std::string GetParameter2( ) { return m_parameter2; };


	private:

		std::string m_eventName;
		std::string m_parameter1;
		std::string m_parameter2;

		UIEventData( ) { };
		UIEventData( const UIEventData & copy ) { };
		UIEventData & operator = ( const UIEventData & copy ) { return *this; };
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
		explicit MessageLoggedEventData( const System::MessageType& message )
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

