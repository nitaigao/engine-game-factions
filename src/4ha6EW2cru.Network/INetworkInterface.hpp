/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkInterface.hpp
*  @date   2009/08/17
*/
#pragma once
#ifndef INETWORKINTERFACE_HPP
#define INETWORKINTERFACE_HPP

#include <RakNetTypes.h>
#include <PluginInterface2.h>
#include <RPC3.h>

#include <string>

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


		/*! Sets the Information that will be sent in an offline Ping Response
		 *
		 * @param[in] BitStream * information
		 * @return ( void )
		 */
		virtual void SetOfflinePingInformation( RakNet::BitStream* information ) = 0;

		/*! Returns the Number of Peer connected to the Interface
		 *
		 * @return ( int )
		 */
		virtual int GetConnectionCount( ) = 0;


		/*! Connects the interface to a Peer
		 *
		 * @param[in] const std::string address
		 * @param[in] unsigned int port
		 * @return ( void )
		 */
		virtual void Connect( const std::string& address, unsigned int port ) = 0;


		/*! Disconnects the Interface from it's connected Peer
		 *
		 * @return ( void )
		 */
		virtual void Disconnect( ) = 0;


		/*! Attaches a plugin to the interface
		 *
		 * @param[in] PluginInterface2 * plugin
		 * @return ( void )
		 */
		virtual void AttachPlugin( PluginInterface2* plugin ) = 0;


		/*! Returns the RPC interface
		 *
		 * @return ( RakNet::RPC3* )
		 */
		virtual RakNet::RPC3* GetRPC( ) = 0;


		/*! Broadcasts the Network with a Ping
		 *
		 * @return ( void )
		 */
		virtual void BroadcastOfflinePing( ) = 0;
		
	};
};

#endif