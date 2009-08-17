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


		/*! Updates the Endpoint and probes for network messages
		*
		* @param[in] float deltaMilliseconds
		* @return ( void )
		*/
		GAMEAPI void Update( float deltaMilliseconds );

	private:

		NetworkServerEndpoint( const NetworkServerEndpoint & copy ) { };
		NetworkServerEndpoint & operator = ( const NetworkServerEndpoint & copy ) { return *this; };
		
		INetworkInterface* m_networkInterface;
		INetworkServerController* m_networkController;

	};
};

#endif