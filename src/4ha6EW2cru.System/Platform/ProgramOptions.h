/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ProgramOptions.h
*  @date   2009/11/24
*/
#pragma once
#ifndef PROGRAMOPTIONS_H
#define PROGRAMOPTIONS_H

#include "IProgramOptions.hpp"

namespace Platform
{
	/*! 
	 *  Stores options passed to the Game at the command line
	 */
	class ProgramOptions : public IProgramOptions
	{

		typedef std::map< std::string, std::string > ProgramOptionMap;

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~ProgramOptions( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		ProgramOptions( ) { };


		/*! Initializes the program options from the command line arguments
		*
		* @return ( void )
		*/
		void Initialize( );


		/*! Detects whether the given option was passed to the program command line
		*
		* @param[in] const std::string & optionName
		* @return ( bool )
		*/
		bool HasOption( const std::string& optionName ) const;


		/*! Returns an option specified on the command line
		*
		* @param[in] const std::string & optionName
		* @return ( std::string )
		*/
		std::string GetOption( const std::string& optionName ) const;

	private:

		ProgramOptions( const ProgramOptions & copy ) { };
		ProgramOptions & operator = ( const ProgramOptions & copy ) { return *this; };

		ProgramOptionMap m_programOptions;
		
	};
};

#endif