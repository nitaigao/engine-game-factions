/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ClientNetworkProvider.h
*  @date   2009/07/15
*/
#pragma once
#ifndef CLIENTNETWORKPROVIDER_H
#define CLIENTNETWORKPROVIDER_H

#include "INetworkProvider.hpp"
#include "INetworkSystem.hpp"
#include "NetworkMessage.hpp"
#include "IServerAdvertisement.hpp"
#include "ClientMessageRouter.h"
#include "ClientPacketTranslator.h"

namespace Network
{
	/*! 
	 *  A network provider that communicates with servers
	 */
	class ClientNetworkProvider : public INetworkProvider
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~ClientNetworkProvider( );


		/*! Default Constructor
		*
		* @return (  )
		*/
		ClientNetworkProvider( INetworkSystem* networkSystem )
			: m_configuration( 0 )
			, m_networkSystem( networkSystem )
			, m_messageRouter( 0 )
			, m_packetTranslator( 0 )
		{

		}

		void Initialize( Configuration::IConfiguration* configuration );

		void Update( float deltaMilliseconds );

		void TranslatePackets( Packet* packet );
		void Release( );

		AnyType::AnyTypeMap Message( const System::Message& message, AnyType::AnyTypeMap parameters );

		void PushMessage( const System::Message& message, AnyType::AnyTypeMap parameters );

		void SendNetworkMessage( const NetworkMessage& message, const SystemAddress& destination );

		/*! Sends a message to a single client across the network
		*
		* @param[in] const std::string & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		void PushMessage( const SystemAddress& address, const System::Message& message, AnyType::AnyTypeMap parameters );

	private:

		ClientNetworkProvider( const ClientNetworkProvider & copy ) { };
		ClientNetworkProvider & operator = ( const ClientNetworkProvider & copy ) { return *this; };

		Configuration::IConfiguration* m_configuration;

		RakPeerInterface* m_networkInterface;
		INetworkSystem* m_networkSystem;
		IClientMessageRouter* m_messageRouter;
		IClientPacketTranslator* m_packetTranslator;
		
	};
};

#endif
