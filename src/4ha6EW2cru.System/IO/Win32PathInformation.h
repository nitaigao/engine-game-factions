/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   Win32PathInformation.h
*  @date   2009/07/31
*/
#pragma once
#ifndef WIN32PATHINFORMATION_H
#define WIN32PATHINFORMATION_H

#include "IPathInformation.hpp"

#include "../Export.hpp"

namespace IO
{
	/*! 
	 *  Returns Path Information for the WIn32 Platform
	 */
	class Win32PathInformation : public IPathInformation
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~Win32PathInformation( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		Win32PathInformation( ) { };

		/*! Returns the path to the data directory 
		*
		* @return ( std::string )
		*/
		GAMEAPI std::string GetGlobalDataPath( ) const;


		/*! Returns the local path to the data directory
		*
		* @return ( std::string )
		*/
		GAMEAPI std::string GetLocalDataPath( ) const;


		/*! Returns the path to the development data directory
		*
		* @return ( std::string )
		*/
		GAMEAPI std::string GetGlobalDevelopmentPath( ) const;


		/*! Formats a file path to the Platforms Path Format
		*
		* @param[in] const std::string & input
		* @return ( GAMEAPI std::string )
		*/
		GAMEAPI std::string FormatPath( const std::string& input ) const;

	private:

		Win32PathInformation( const Win32PathInformation & copy ) { };
		Win32PathInformation & operator = ( const Win32PathInformation & copy ) { return *this; };
		
	};
};

#endif
