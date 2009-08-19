/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkProvider.hpp
*  @date   2009/08/17
*/
#pragma once
#ifndef INETWORKPROVIDER_HPP
#define INETWORKPROVIDER_HPP

#include <vector>
#include "System/SystemType.hpp"
#include "System/AnyType.hpp"

namespace Network
{
	/*! 
	 *  Receives and Transmits to Clients on the Network
	 */
	class INetworkProvider
	{

	public:

		typedef std::vector< INetworkProvider* > NetworkProviderList;

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~INetworkProvider( ) { };


		/*! Initializes the Network Interface
		 *
		 * @param[in] unsigned int port
		 * @param[in] int maxConnections
		 * @return ( void )
		 */
		virtual void Initialize( unsigned int port, int maxConnections ) = 0;


		/*! Updates the Network Provider
		 *
		 * @param[in] float deltaMilliseconds
		 * @return ( void )
		 */
		virtual void Update( float deltaMilliseconds ) = 0;


		/*! Distributes the message for the entity across the Network
		 *
		 * @param[in] const std::string & entityName
		 * @param[in] const System::Message & message
		 * @param[in] AnyType::AnyTypeMap parameters
		 * @return ( void )
		 */
		virtual void Message( const std::string& entityName, const System::Message& message, AnyType::AnyTypeMap parameters ) = 0;


		/*! Destroys the Provider
		 *
		 * @return ( void )
		 */
		virtual void Destroy( ) = 0;
		
	};
};

#endif