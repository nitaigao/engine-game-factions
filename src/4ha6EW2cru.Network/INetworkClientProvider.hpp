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
#include "IServerAdvertisement.hpp"

#include <string>

namespace Network
{
	/*! 
	 *  A Client Network Provider
	 */
	class GAMEAPI INetworkClientProvider : public INetworkProvider
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
		virtual void Connect( const std::string& serverAddress ) = 0;


		/*! Disconnects the Provider if connected to a Server
		 *
		 * @return ( void )
		 */
		virtual void Disconnect( ) = 0;


		/*! Selects a Character to play on the Server
		 *
		 * @param[in] const std::string & characterName
		 * @return ( void )
		 */
		virtual void SelectCharacter( const std::string& characterName ) = 0;


		/*! Broadcasts the Local Network for Servers
		 *
		 * @return ( void )
		 */
		virtual void FindServers( ) = 0;


		/*! Stops the Client from receiving traffic, but it can still send messages
		 *
		 * @param[in] bool isPassive
		 * @return ( void )
		 */
		virtual void SetPassive( bool isPassive ) = 0;


		/*! Tells the Server that the Client has finished loading the level
		 *
		 * @return ( void )
		 */
		virtual void LevelLoaded( ) = 0;
	};
};

#endif