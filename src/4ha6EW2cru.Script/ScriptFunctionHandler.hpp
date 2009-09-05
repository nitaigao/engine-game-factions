/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ScriptFunctionHandler.hpp
*  @date   2009/04/28
*/
#pragma once
#ifndef SCRIPTGENERICHANDLER_HPP
#define SCRIPTGENERICHANDLER_HPP

#include "IScriptFunctionHandler.hpp"



namespace Script
{
	/*!
	 *  A Container for handling Updates or Events from the Game 
	 */
	class ScriptFunctionHandler : public IScriptFunctionHandler
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~ScriptFunctionHandler( ) { };

		/*! Default Constructor
		 *
		 *  @return ()
		 */
		ScriptFunctionHandler( const luabind::object& functionHandler )
			: m_functionHandler( functionHandler )
			, m_isMarkedForDeletion( false )
		{

		}


		/*! Marks the Handler for deletion on the next UX Update or Event Tick
		 *
		 *  @return (void)
		 */
		inline void MarkForDeletion( ) { m_isMarkedForDeletion = true; };


		/*! Returns whether or not the handler is marked for deletion on the next UX Update or Event Tick
		 *
		 *  @return (bool)
		 */
		inline bool IsMarkedForDeletion( ) const { return m_isMarkedForDeletion; };


		/*! Returns the LUA function
		*
		*  @return (luabind::object)
		*/
		inline luabind::object GetFunction( ) const { return m_functionHandler; };


		/*! Calls the Function Handler with the given parameters
		*
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		void CallFunction( AnyType::AnyTypeMap parameters )
		{
			luabind::call_function< void >( m_functionHandler, parameters );
		}


		void CallFunction( const System::MessageType& message, AnyType::AnyTypeMap& parameters )
		{
			luabind::call_function< void >( m_functionHandler, message, parameters );
		}


		bool operator == ( const ScriptFunctionHandler& input )
		{
			return input.m_functionHandler == m_functionHandler;
		}


	private:

		bool m_isMarkedForDeletion;
		luabind::object m_functionHandler;

		ScriptFunctionHandler( const ScriptFunctionHandler & copy ) { };
		ScriptFunctionHandler & operator = ( const ScriptFunctionHandler & copy ) { return *this; };

	};
};

#endif
