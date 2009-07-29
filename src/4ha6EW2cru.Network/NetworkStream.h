/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkStream.h
*  @date   2009/07/28
*/
#pragma once
#ifndef NETWORKSTREAM_H
#define NETWORKSTREAM_H

#include "IO/MemoryStream.h"
#include "INetworkStream.hpp"

#include "Maths/MathVector3.hpp"

namespace Network
{
	/*! 
	 *  A Stream to transmit data over the Network
	 */
	class NetworkStream : public IO::MemoryStream, public INetworkStream
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~NetworkStream( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		NetworkStream( )
			: m_readPosition( 0 )
		{

		}


		using MemoryStream::Read;
		using MemoryStream::Write;

		/*! Sets the position of the read cursor
		*
		* @param[in] const unsigned int & position
		* @return ( void )
		*/
		GAMEAPI inline void SetReadPosition( const unsigned int& position ) { m_readPosition = position; };


		/*! Writes float data to the stream
		*
		* @param[in] const std::string & data
		* @return ( void )
		*/
		GAMEAPI void Write( const float& data );


		/*! Reads data into the float
		*
		* @param[in] std::string data
		* @return ( GAMEAPI void )
		*/
		GAMEAPI void Read( float& data );


		/*! Writes string data to the stream
		*
		* @param[in] const std::string & data
		* @return ( void )
		*/
		GAMEAPI void Write( const std::string& data );


		/*! Reads data into the string
		*
		* @param[in] std::string data
		* @return ( GAMEAPI void )
		*/
		GAMEAPI void Read( std::string& data );


		/*! Writes Vector data to the Stream
		*
		* @param[in] const Maths::MathVector3 & data
		* @return ( GAMEAPI void )
		*/
		GAMEAPI void Write( const Maths::MathVector3& data );


		/*! Reads Vector data from the Stream
		*
		* @param[in] const Maths::MathVector3 & data
		* @return ( GAMEAPI void )
		*/
		GAMEAPI void NetworkStream::Read( Maths::MathVector3& data );

	private:

		NetworkStream( const NetworkStream & copy ) { };
		NetworkStream & operator = ( const NetworkStream & copy ) { return *this; };

		unsigned int m_readPosition;
		
	};
};

#endif