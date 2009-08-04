/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkStream.hpp
*  @date   2009/07/28
*/
#pragma once
#ifndef INETWORKSTREAM_HPP
#define INETWORKSTREAM_HPP

#include "IO/MemoryStream.h"

namespace Network
{
	/*! 
	 *  A Stream to transmit across the Network
	 */
	class INetworkStream
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~INetworkStream( ) { };


		/*! Writes string data to the stream
		*
		* @param[in] const std::string & data
		* @return ( void )
		*/
		virtual void Write( const std::string& data ) = 0;


		/*! Reads data into the string
		*
		* @param[in] std::string data
		* @return ( GAMEAPI void )
		*/
		virtual void Read( std::string& data ) = 0;



		/*! Sets the position of the read cursor
		*
		* @param[in] const unsigned int & position
		* @return ( void )
		*/
		virtual void SetReadPosition( const unsigned int& position ) = 0;
		
	};
};

#endif
