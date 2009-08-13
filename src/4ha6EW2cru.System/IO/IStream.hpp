/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IStream.hpp
*  @date   2009/08/13
*/
#pragma once
#ifndef ISTREAM_HPP
#define ISTREAM_HPP

#include <string>

namespace IO
{
	/*! 
	 *  A Stream interface for storing data
	 */
	class IStream
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~IStream( ) { };


		/*! Writes a string to the Stream
		 *
		 * @param[in] const std::string & data
		 * @return ( void )
		 */
		virtual void Write( const std::string& data ) = 0;


		/*! Reads a string from the Stream
		*
		* @param[in] const std::string & data
		* @return ( void )
		*/
		virtual void Read( std::string& data ) = 0;


		/*! Writes an integer to the Stream
		 *
		 * @param[in] int data
		 * @return ( void )
		 */
		virtual void Write( int data ) = 0;


		/*! Reads an integer to the Stream
		*
		* @param[in] int data
		* @return ( void )
		*/
		virtual void Read( int& data ) = 0;
		
	};
};

#endif