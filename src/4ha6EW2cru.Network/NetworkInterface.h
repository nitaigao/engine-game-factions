/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkInterface.h
*  @date   2009/08/17
*/
#pragma once
#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include "INetworkInterface.hpp"

#include <RakPeerInterface.h>

namespace Network
{
	/*! 
	 *  Transmits and Received data across the Network
	 */
	class NetworkInterface : public INetworkInterface
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~NetworkInterface( );


		/*! Default Constructor
		*
		* @return (  )
		*/
		NetworkInterface( );


		/*! Initializes the Network Interface
		*
		* @param[in] unsigned int port
		* @param[in] int maxConnections
		* @return ( void )
		*/
		void Initialize( unsigned int port, int maxConnections );


		/*! Shuts the Network Interface Down
		*
		* @return ( void )
		*/
		void Destroy( unsigned int timeToBlock );

		/*! Receives information from the Network
		*
		* @return ( Packet* )
		*/
		Packet* Receive( );


		/*! Deallocates the Packet and deletes the pointer to it
		*
		* @param[in] Packet * packet
		* @return ( void )
		*/
		void DeAllocatePacket( Packet* packet );

	private:

		NetworkInterface( const NetworkInterface & copy ) { };
		NetworkInterface & operator = ( const NetworkInterface & copy ) { return *this; };

		RakPeerInterface* m_networkAdapter;
		
	};
};

#endif