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

namespace Network
{
	/*! 
	 *  A Client for transmitting and receiving client messages to and from the server
	 */
	class GAMEAPI NetworkClientProvider : public INetworkClientProvider
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~NetworkClientProvider( );
	

		/*! IoC Constructor
		*
		* @return (  )
		*/
		NetworkClientProvider( INetworkInterface* networkInterface, INetworkClientController* controller, 
			INetworkClientEndpoint* endpoint, IServerCache* serverCache )
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
		void Initialize( unsigned int port, int maxConnections );


		/*! Updates the Network Provider
		*
		* @param[in] float deltaMilliseconds
		* @return ( void )
		*/
		void Update( float deltaMilliseconds );


		/*! Distributes the message for the entity across the Network
		*
		* @param[in] const std::string & entityName
		* @param[in] const System::Message & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		void Message( const std::string& entityName, const System::MessageType& message, AnyType::AnyTypeMap parameters );


		/*! Destroys the Provider
		*
		* @return ( void )
		*/
		void Destroy( );


		/*! Connects the Provider to a Server Address
		*
		* @param[in] const std::string & serverAddress
		* @param[in] unsigned int port
		* @return (  )
		*/
		void Connect( const std::string& serverAddress, unsigned int port );


		/*! Disconnects the Provider if connected to a Server
		*
		* @return ( void )
		*/
		void Disconnect( );


		/*! Selects a Character to play on the Server
		*
		* @param[in] const std::string & characterName
		* @return ( void )
		*/
		void SelectCharacter( const std::string& characterName );


		/*! Broadcasts the Local Network for Servers
		*
		* @return ( void )
		*/
		void FindServers( );


		/*! Finds the Server Advertisement at the given cache index
		*
		* @param[in] int cacheIndex
		* @return ( IServerAdvertisement* )
		*/
		IServerAdvertisement* GetServerAdvertisement( int cacheIndex );


		/*! Stops the Client from receiving traffic, but it can still send messages
		*
		* @param[in] bool isPassive
		* @return ( void )
		*/
		 inline void SetPassive( bool isPassive ) 
		 { 
			 m_endpoint->SetPassive( isPassive ); 
			 m_controller->SetPassive( isPassive );
		 };


		 /*! Tells the Server that the Client has finished loading the level
		 *
		 * @return ( void )
		 */
		 inline void LevelLoaded( ) { m_controller->LevelLoaded( ); };

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