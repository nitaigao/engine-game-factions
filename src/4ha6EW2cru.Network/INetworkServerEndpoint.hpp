/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkServerEndpoint.hpp
*  @date   2009/08/17
*/
#pragma once
#ifndef INETWORKSERVERENDPOINT_HPP
#define INETWORKSERVERENDPOINT_HPP

namespace Network
{
	/*! 
	 *  An endpoint that receives client information
	 */
	class INetworkServerEndpoint
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~INetworkServerEndpoint( ) { };


		/*! Updates the Endpoint and probes for network messages
		 *
		 * @param[in] float deltaMilliseconds
		 * @return ( void )
		 */
		virtual void Update( float deltaMilliseconds ) = 0;
		
	};
};

#endif