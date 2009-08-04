/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IStream.hpp
*  @date   2009/07/27
*/
#pragma once
#ifndef ISTREAM_HPP
#define ISTREAM_HPP

#include <string>

namespace IO
{
	/*! 
	 *  A Base class for input/output 
	 */
	class IStream
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~IStream( ) { };


		/*! Writes the given data and size to the IStream
		*
		* @param[in] const int & count
		* @param[in] void * data
		* @return ( void )
		*/
		virtual void Write( void* buffer, const int& count ) = 0;


		/*! Reads the given buffer of size from the IStream
		*
		* @param[in] const int & count
		* @param[in] void * buffer
		* @return ( void )
		*/
		virtual void Read( void* buffer, const int& count, const int& offset ) const = 0;


		/*! Returns the total length of the stream data
		*
		* @return ( int )
		*/
		virtual int GetLength( ) const = 0;


		/*! Returns whether or not the stream contains data
		*
		* @return ( bool )
		*/
		virtual bool IsEmpty( ) const = 0;


		/*! Copies the contents of the stream to the output buffer
		*
		* @param[in] char * output
		* @return ( int )
		*/
		virtual int CopyData( void* buffer ) const = 0;
		
	};
};

#endif

