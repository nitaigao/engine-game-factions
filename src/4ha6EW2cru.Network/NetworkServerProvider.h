/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkServerProvider.h
*  @date   2009/08/17
*/
#pragma once
#ifndef NETWORKSERVERPROVIDER_H
#define NETWORKSERVERPROVIDER_H


#include "INetworkServerController.hpp"
#include "INetworkProvider.hpp"

#include "Export.hpp"

namespace Network
{
	/*! 
	 *  Receives input from clients on the Network and Transmits Updates
	 */
	class NetworkServerProvider : public INetworkProvider
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		GAMEAPI ~NetworkServerProvider( );


		/*! Default Constructor
		*
		* @return (  )
		*/
		GAMEAPI NetworkServerProvider( );


		/*! IoC Constructor
		 *
		 * @param[in] INetworkInterface * networkInterface
		 * @return (  )
		 */
		NetworkServerProvider( INetworkServerController* controller )
			: m_controller( controller )
		{

		}


		/*! Initializes the Network Interface
		*
		* @param[in] unsigned int port
		* @param[in] int maxPlayers
		* @return ( void )
		*/
		GAMEAPI void Initialize( unsigned int port, int maxPlayers );


		/*! Updates the Network Provider
		*
		* @param[in] float deltaMilliseconds
		* @return ( void )
		*/
		GAMEAPI void Update( float deltaMilliseconds ) { };


		/*! Distributes the message for the entity across the Network
		*
		* @param[in] const std::string & entityName
		* @param[in] const System::Message & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		GAMEAPI void Message( const std::string& entityName, const System::Message& message, AnyType::AnyTypeMap parameters );


	private:

		NetworkServerProvider( const NetworkServerProvider & copy ) { };
		NetworkServerProvider & operator = ( const NetworkServerProvider & copy ) { return *this; };

		INetworkServerController* m_controller;
		
	};
};

#endif