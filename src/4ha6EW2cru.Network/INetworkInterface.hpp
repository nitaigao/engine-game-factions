/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkInterface.hpp
*  @date   2009/08/17
*/
#pragma once
#ifndef INETWORKINTERFACE_HPP
#define INETWORKINTERFACE_HPP

#include "RakNetTypes.h"

namespace Network
{
	/*! 
	 *  A Network Interface for Sending and Receiving Data from the Network
	 */
	class INetworkInterface
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~INetworkInterface( ) { };


		/*! Initializes the Network Interface
		 *
		 * @param[in] unsigned int port
		 * @param[in] int maxConnections
		 * @return ( void )
		 */
		virtual void Initialize( unsigned int port, int maxConnections ) = 0;


		/*! Shuts the Network Interface Down
		 *
		 * @return ( void )
		 */
		virtual void Destroy( unsigned int timeToBlock ) = 0;


		/*! Receives information from the Network
		 *
		 * @return ( Packet* )
		 */
		virtual Packet* Receive( ) = 0;


		/*! Deallocates the Packet and deletes the pointer to it
		 *
		 * @param[in] Packet * packet
		 * @return ( void )
		 */
		virtual void DeAllocatePacket( Packet* packet ) = 0;
		
	};
};

#endif