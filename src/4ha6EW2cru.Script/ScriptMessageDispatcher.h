/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ScriptMessageDispatcher.h
*  @date   2009/09/04
*/
#pragma once
#ifndef SCRIPTMESSAGEDISPATCHER_H
#define SCRIPTMESSAGEDISPATCHER_H

#include "IScriptMessageDispatcher.hpp"

namespace Script
{
	/*! 
	 *  Dispatched component messages to script handlers
	 */
	class GAMEAPI ScriptMessageDispatcher : public IScriptMessageDispatcher
	{

		typedef std::multimap< System::MessageType, IScriptFunctionHandler* > DelegateFunctionMap;

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~ScriptMessageDispatcher( );


		/*! Default Constructor
		*
		* @return (  )
		*/
		ScriptMessageDispatcher( ) { };


		/*! Dispatches a message to the listening Handlers
		*
		* @param[in] const System::MessageType & message
		* @param[in] AnyType::AnyTypeMap & parameters
		* @return ( void )
		*/
		void DisptchMessage( const System::MessageType& message, AnyType::AnyTypeMap& parameters );


		/*! Adds a Message handler ready for Message dispatch
		 *
		 * @param[in] const System::MessageType & message
		 * @param[in] IScriptFunctionHandler * functionHandler
		 * @return ( void )
		 */
		void AddMessageHandler( const System::MessageType& message, luabind::object delegateFunction );


		/*! Returns whether or not the handler has been added for the message
		*
		* @param[in] const System::MessageType & message
		* @param[in] IScriptFunctionHandler * functionHandler
		* @return ( bool )
		*/
		bool HasHandler( const System::MessageType& message, luabind::object delegateFunction );


		/*! Removes the message handler from the handler list
		*
		* @param[in] const System::MessageType & message
		* @param[in] IScriptFunctionHandler * functionHandler
		* @return ( void )
		*/
		void RemoveHandler( const System::MessageType& message, luabind::object delegateFunction );


		/*! Updates the Dispatcher
		*
		* @param[in] float
		* @return ( void )
		*/
		void Update( float deltaMilliseconds );

	private:

		ScriptMessageDispatcher( const ScriptMessageDispatcher & copy ) { };
		ScriptMessageDispatcher & operator = ( const ScriptMessageDispatcher & copy ) { return *this; };

		DelegateFunctionMap m_handlers;
		
	};
};

#endif