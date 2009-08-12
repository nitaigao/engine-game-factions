/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ServerNetworkProvider.h
*  @date   2009/07/15
*/
#pragma once
#ifndef SERVERNETWORKPROVIDER_H
#define SERVERNETWORKPROVIDER_H

#include "INetworkProvider.hpp"
#include "INetworkSystem.hpp"

#include "ServerPacketTranslator.h"

#include <RakPeerInterface.h>

#include <deque>

namespace Network
{
	/*! 
	 *  A Network Provider that servers to clients
	 */
	class ServerNetworkProvider : public INetworkProvider
	{

		typedef std::deque< SystemAddress > SystemAddressList;

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~ServerNetworkProvider( );


		/*! Default Constructor
		*
		* @return (  )
		*/
		ServerNetworkProvider( INetworkSystem* networkSystem )
			: m_configuration( 0 )
			, m_packetTranslator( 0 )
			, m_networkSystem( networkSystem )
			, m_tickRate( 0.0f )
			, m_tickTotal( 0.0f )
		{

		}

		void Initialize( Configuration::IConfiguration* configuration );

		void Update( const float& deltaMilliseconds );

		inline AnyType::AnyTypeMap Message( const System::Message& message, AnyType::AnyTypeMap parameters ) { return AnyType::AnyTypeMap( ); };

		void Release( );

		void PushMessage( const System::Message& message, AnyType::AnyTypeMap parameters );

	private:

		ServerNetworkProvider( const ServerNetworkProvider & copy ) { };
		ServerNetworkProvider & operator = ( const ServerNetworkProvider & copy ) { return *this; };

		void TranslatePackets( Packet* packet );
		void UpdateClients( const float& deltaMilliseconds );

		Configuration::IConfiguration* m_configuration;

		RakPeerInterface* m_networkInterface;
		IServerPacketTranslator* m_packetTranslator;

		SystemAddressList m_clients;
		INetworkSystem* m_networkSystem;
		RakNet::BitStream m_sendBuffer;

		float m_tickRate;
		float m_tickTotal;
		
	};
};

#endif
