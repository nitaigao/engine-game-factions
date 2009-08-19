/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkServerEndpoint.h
*  @date   2009/08/17
*/
#pragma once
#ifndef NETWORKSERVERENDPOINT_H
#define NETWORKSERVERENDPOINT_H

#include "INetworkServerController.hpp"
#include "INetworkServerEndpoint.hpp"
#include "INetworkInterface.hpp"

#include <RPC3.h>

#include "Export.hpp"

namespace Network
{
	/*! 
	 *  The Server Endpoint for receiving Network messages
	 */
	class NetworkServerEndpoint : public INetworkServerEndpoint
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~NetworkServerEndpoint( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		NetworkServerEndpoint( INetworkInterface* networkInterface, INetworkServerController* controller )
			: m_networkInterface( networkInterface )
			, m_networkController( controller )
		{

		}


		/*! Initializes the Endpoint
		*
		* @return ( void )
		*/
		GAMEAPI void Initialize( );


		/*! Updates the Endpoint
		*
		* @param[in] float deltaMilliseconds
		* @return ( void )
		*/
		GAMEAPI void Update( float deltaMilliseconds );

		static void SelectCharacter( RakNet::RakString characterName, RakNet::RPC3* rpcFromnetwork );

	private:

		NetworkServerEndpoint( const NetworkServerEndpoint & copy ) { };
		NetworkServerEndpoint & operator = ( const NetworkServerEndpoint & copy ) { return *this; };
		
		INetworkInterface* m_networkInterface;
		INetworkServerController* m_networkController;

	};
};

#endif