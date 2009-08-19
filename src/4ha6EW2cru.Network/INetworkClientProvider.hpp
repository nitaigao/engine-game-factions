/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkClientProvider.hpp
*  @date   2009/08/18
*/
#pragma once
#ifndef INETWORKCLIENTPROVIDER_HPP
#define INETWORKCLIENTPROVIDER_HPP

#include "INetworkProvider.hpp"
#include <string>

namespace Network
{
	/*! 
	 *  A Client Network Provider
	 */
	class INetworkClientProvider : public INetworkProvider
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~INetworkClientProvider( ) { };


		/*! Connects the Provider to a Server Address
		 *
		 * @param[in] const std::string & serverAddress
		 * @param[in] unsigned int port
		 * @return (  )
		 */
		virtual void Connect( const std::string& serverAddress, unsigned int port ) = 0;


		/*! Disconnects the Provider if connected to a Server
		 *
		 * @return ( void )
		 */
		virtual void Disconnect( ) = 0;

	};
};

#endif