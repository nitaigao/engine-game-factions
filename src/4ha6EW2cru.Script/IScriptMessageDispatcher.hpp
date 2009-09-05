/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IScriptMessageDispatcher.hpp
*  @date   2009/09/04
*/
#pragma once
#ifndef ISCRIPTMESSAGEDISPATCHER_HPP
#define ISCRIPTMESSAGEDISPATCHER_HPP

#include "IScriptFunctionHandler.hpp"

#include "System/SystemType.hpp"
#include "System/AnyType.hpp"

#include "Export.hpp"

namespace Script
{
	/*! 
	 *  Dispatched component messages to script handlers
	 */
	class GAMEAPI IScriptMessageDispatcher
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~IScriptMessageDispatcher( ) { };


		/*! Dispatches a message to the listening Handlers
		 *
		 * @param[in] const System::MessageType & message
		 * @param[in] AnyType::AnyTypeMap & parameters
		 * @return ( void )
		 */
		virtual void DisptchMessage( const System::MessageType& message, AnyType::AnyTypeMap& parameters ) = 0;


		/*! Adds a Message handler ready for Message dispatch
		*
		* @param[in] const System::MessageType & message
		* @param[in] IScriptFunctionHandler * functionHandler
		* @return ( void )
		*/
		virtual void AddMessageHandler( const System::MessageType& message, luabind::object delegateFunction ) = 0;


		/*! Returns whether or not the handler has been added for the message
		 *
		 * @param[in] const System::MessageType & message
		 * @param[in] IScriptFunctionHandler * functionHandler
		 * @return ( bool )
		 */
		virtual bool HasHandler( const System::MessageType& message, luabind::object delegateFunction ) = 0;


		/*! Removes the message handler from the handler list
		*
		* @param[in] const System::MessageType & message
		* @param[in] IScriptFunctionHandler * functionHandler
		* @return ( void )
		*/
		virtual void RemoveHandler( const System::MessageType& message, luabind::object delegateFunction ) = 0;


		/*! Updates the Dispatcher
		 *
		 * @param[in] float
		 * @return ( void )
		 */
		virtual void Update( float ) = 0;
		
	};
};

#endif