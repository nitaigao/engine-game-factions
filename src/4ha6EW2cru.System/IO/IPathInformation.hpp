/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IPathInformation.hpp
*  @date   2009/07/31
*/
#pragma once
#ifndef IPATHINFORMATION_HPP
#define IPATHINFORMATION_HPP

#include <string>

namespace IO
{
	/*! 
	 *  Returns Path Information for the Given Platform
	 */
	class IPathInformation
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~IPathInformation( ) { };

		/*! Returns the path to the data directory 
		*
		* @return ( std::string )
		*/
		virtual std::string GetGlobalDataPath( ) const = 0;


		/*! Returns the local path to the data directory
		*
		* @return ( std::string )
		*/
		virtual std::string GetLocalDataPath( ) const = 0;


		/*! Returns the path to the development data directory
		*
		* @return ( std::string )
		*/
		virtual std::string GetGlobalDevelopmentPath( ) const = 0;

	};
};

#endif

