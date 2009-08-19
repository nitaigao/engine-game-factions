/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkClientEndpoint.h
*  @date   2009/08/19
*/
#pragma once
#ifndef NETWORKCLIENTENDPOINT_H
#define NETWORKCLIENTENDPOINT_H

#include "INetworkClientEndpoint.hpp"
#include "INetworkInterface.hpp"

#include "Export.hpp"

namespace Network
{
	/*! 
	 *  Endpoint for Incoming client information
	 */
	class NetworkClientEndpoint : public INetworkClientEndpoint
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~NetworkClientEndpoint( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		NetworkClientEndpoint( INetworkInterface* networkInterface )
			: m_networkInterface( networkInterface )
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

		static void LoadLevel( RakNet::RakString levelName, RakNet::RPC3* rpcFromNetwork );

	private:

		NetworkClientEndpoint( const NetworkClientEndpoint & copy ) { };
		NetworkClientEndpoint & operator = ( const NetworkClientEndpoint & copy ) { return *this; };

		INetworkInterface* m_networkInterface;
		
	};
};

#endif