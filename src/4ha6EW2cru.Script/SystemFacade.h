/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   SystemFacade.h
*  @date   2009/08/27
*/
#pragma once
#ifndef SYSTEMFACADE_H
#define SYSTEMFACADE_H

#include <luabind/luabind.hpp>
#include "IScriptFacade.hpp"

namespace Script
{
	/*! 
	 *  A Facade for interacting with System Functions
	 */
	class SystemFacade : public IScriptFacade
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~SystemFacade( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		SystemFacade( ) { };


		/*! Returns the Script functions
		*
		* @return ( luabind::scope )
		*/
		static luabind::scope RegisterFunctions( );


		/*!  Prints the specified message to the console
		*
		*  @param[in] const std::string & message
		*  @return (void)
		*/
		void Print( const std::string& message );


		/*! Quits the game
		*
		*  @return (void)
		*/
		void Quit( );


		/*! Loads the specified level
		*
		*  @param[in] const std::string & levelName
		*  @return (void)
		*/
		void LoadLevel( const std::string& levelName );


		/*! Ends the current Game
		*
		*  @return (void)
		*/
		void EndGame( );

	private:

		SystemFacade( const SystemFacade & copy ) { };
		SystemFacade & operator = ( const SystemFacade & copy ) { return *this; };
		
	};
};

#endif