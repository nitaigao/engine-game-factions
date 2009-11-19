/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkServerProvider.h
*  @date   2009/08/17
*/
#pragma once
#ifndef NETWORKSERVERPROVIDER_H
#define NETWORKSERVERPROVIDER_H


#include "INetworkProvider.hpp"
#include "INetworkServerController.hpp"
#include "INetworkServerEndpoint.hpp"
#include "INetworkServerProvider.hpp"
#include "INetworkInterface.hpp"

#include "Configuration/IConfiguration.hpp"

#include "Events/EventManager.h"
#include "Events/Event.h"

#include "Export.hpp"

namespace Network
{
	/*! 
	 *  Receives input from clients on the Network and Transmits Updates
	 */
	class NetworkServerProvider : public INetworkServerProvider
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		GAMEAPI ~NetworkServerProvider( );


		/*! IoC Constructor
		 *
		 * @param[in] INetworkInterface * networkInterface
		 * @return (  )
		 */
		NetworkServerProvider( Configuration::IConfiguration* configuration, INetworkInterface* networkInterface, INetworkServerController* controller, INetworkServerEndpoint* endpoint )
			: m_networkInterface( networkInterface )
			, m_controller( controller )
			, m_configuration( configuration )
			, m_endpoint( endpoint )
		{

		}


		/*! Initializes the Network Interface
		*
		* @param[in] int maxConnections
		* @return ( void )
		*/
		GAMEAPI void Initialize( int maxConnections );


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
		GAMEAPI void Message( const std::string& entityName, const System::MessageType& message, AnyType::AnyTypeMap parameters );


		/*! Destroys the Provider
		*
		* @return ( void )
		*/
		GAMEAPI void Destroy( );


		GAMEAPI void OnGameLevelChanged( const Events::IEvent* event );


	private:

		NetworkServerProvider( const NetworkServerProvider & copy ) { };
		NetworkServerProvider & operator = ( const NetworkServerProvider & copy ) { return *this; };

		INetworkInterface* m_networkInterface;
		INetworkServerController* m_controller;
		Configuration::IConfiguration* m_configuration;
		INetworkServerEndpoint* m_endpoint;
		
	};
};

#endif