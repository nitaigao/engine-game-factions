/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkClientProvider.h
*  @date   2009/08/18
*/
#pragma once
#ifndef NETWORKCLIENTPROVIDER_H
#define NETWORKCLIENTPROVIDER_H

#include "INetworkClientProvider.hpp"
#include "INetworkClientEndpoint.hpp"
#include "INetworkClientController.hpp"
#include "INetworkInterface.hpp"
#include "IServerCache.hpp"

#include "Configuration/IConfiguration.hpp"

#include "Export.hpp"

namespace Network
{
	/*! 
	 *  A Client for transmitting and receiving client messages to and from the server
	 */
	class NetworkClientProvider : public INetworkClientProvider
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		GAMEAPI ~NetworkClientProvider( );
	

		/*! IoC Constructor
		*
		* @return (  )
		*/
		NetworkClientProvider( INetworkInterface* networkInterface, INetworkClientController* controller, INetworkClientEndpoint* endpoint, IServerCache* serverCache )
			: m_networkInterface( networkInterface )
			, m_endpoint( endpoint )
			, m_controller( controller )
			, m_serverCache( serverCache )
		{

		}


		/*! Initializes the Network Interface
		*
		* @param[in] unsigned int port
		* @param[in] int maxConnections
		* @return ( void )
		*/
		GAMEAPI void Initialize( unsigned int port, int maxConnections );


		/*! Updates the Network Provider
		*
		* @param[in] float deltaMilliseconds
		* @return ( void )
		*/
		GAMEAPI void Update( float deltaMilliseconds );


		/*! Distributes the message for the entity across the Network
		*
		* @param[in] const std::string & entityName
		* @param[in] const System::Message & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		GAMEAPI void Message( const std::string& entityName, const System::Message& message, AnyType::AnyTypeMap parameters ) { };


		/*! Destroys the Provider
		*
		* @return ( void )
		*/
		GAMEAPI void Destroy( );


		/*! Connects the Provider to a Server Address
		*
		* @param[in] const std::string & serverAddress
		* @param[in] unsigned int port
		* @return (  )
		*/
		GAMEAPI void Connect( const std::string& serverAddress, unsigned int port );


		/*! Disconnects the Provider if connected to a Server
		*
		* @return ( void )
		*/
		GAMEAPI void Disconnect( );


		/*! Selects a Character to play on the Server
		*
		* @param[in] const std::string & characterName
		* @return ( void )
		*/
		GAMEAPI void SelectCharacter( const std::string& characterName );

	private:

		NetworkClientProvider( const NetworkClientProvider & copy ) { };
		NetworkClientProvider & operator = ( const NetworkClientProvider & copy ) { return *this; };

		INetworkInterface* m_networkInterface;
		INetworkClientEndpoint* m_endpoint;
		INetworkClientController* m_controller;
		IServerCache* m_serverCache;
		
	};
};

#endif