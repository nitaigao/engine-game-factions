/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkProvider.hpp
*  @date   2009/07/15
*/
#pragma once
#ifndef INETWORKPROVIDER_HPP
#define INETWORKPROVIDER_HPP

#include "Configuration/IConfiguration.hpp"
#include "System/SystemType.hpp"

#include <RakPeerInterface.h>

namespace Network
{
	/*! 
	 *  A communication provider to the Network
	 */
	class INetworkProvider
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~INetworkProvider( ) { };

		virtual void Initialize( Configuration::IConfiguration* configuration ) = 0;

		virtual void Update( float deltaMilliseconds ) = 0;

		virtual void Release( ) = 0;

		virtual AnyType::AnyTypeMap Message( const System::Message& message, AnyType::AnyTypeMap parameters ) = 0;

		virtual void PushMessage( const System::Message& message, AnyType::AnyTypeMap parameters ) = 0;

		/*! Sends a message to a single client across the network
		*
		* @param[in] const std::string & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		virtual void PushMessage( const SystemAddress& address, const System::Message& message, AnyType::AnyTypeMap parameters ) = 0;
		
	};
};

#endif
