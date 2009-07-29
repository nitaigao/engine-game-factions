/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MemoryStream.h
*  @date   2009/07/27
*/
#pragma once
#ifndef MEMORYSTREAM_H
#define MEMORYSTREAM_H

#include "IMemoryStream.hpp"

#include "../System/AnyType.hpp"

#include "../Export.hpp"

namespace IO
{
	/*! 
	 *  A Stream that stores data in memory
	 */
	class MemoryStream : public IMemoryStream
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		GAMEAPI ~MemoryStream( );


		/*! Default Constructor
		*
		* @return (  )
		*/
		GAMEAPI MemoryStream( )
			: m_data1( 0 )
			, m_data2( 0 )
			, m_currentData( &m_data1 )
			, m_writePosition( 0 )
		{

		}


		/*! Returns the position of the write cursor
		*
		* @return ( int )
		*/
		GAMEAPI inline int GetWritePosition( ) const { return m_writePosition; };


		/*! Writes the given buffer and size to the IStream
		*
		* @param[in] const int & count
		* @param[in] void * buffer
		* @return ( void )
		*/
		GAMEAPI void Write( void* buffer, const int& count );


		/*! Reads the given buffer of size from the IStream
		*
		* @param[in] const int & count
		* @param[in] void * buffer
		* @return ( void )
		*/
		GAMEAPI void Read( void* buffer, const int& count, const int& offset ) const;


		/*! Returns the total length of the stream data
		*
		* @return ( int )
		*/
		inline int GetLength( ) const { return m_writePosition; };


		/*! Returns whether or not the stream contains data
		*
		* @return ( bool )
		*/
		inline bool IsEmpty( ) const { return m_writePosition == 0; };


		/*! Copies the contents of the stream to the output buffer
		*
		* @param[in] char * output
		* @return ( int )
		*/
		GAMEAPI int CopyData( void* buffer ) const;


	protected:

		void** m_currentData;

		void* m_data1;
		void* m_data2;

		unsigned int m_writePosition;

	private:

		MemoryStream( const MemoryStream & copy ) { };
		MemoryStream & operator = ( const MemoryStream & copy ) { return *this; };

		
	};
};

#endif