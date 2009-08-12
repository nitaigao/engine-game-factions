/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ClientPacketTranslator.h
*  @date   2009/08/11
*/
#pragma once
#ifndef CLIENTPACKETRANSLATOR_H
#define CLIENTPACKETRANSLATOR_H

#include <RakPeerInterface.h>
#include <string>

#include "INetworkSystem.hpp"

namespace Network
{
	class IClientPacketTranslator
	{

	public:

		virtual ~IClientPacketTranslator( ) { };

		virtual void OnAdvertiseSystem( Packet* packet ) = 0;
		virtual void OnPacketReceived( Packet* packet ) = 0;

		virtual void OnChangeLevel( const std::string& levelName ) = 0;
		virtual void OnCreateEntity( const std::string& name, const std::string& filePath, const SystemAddress& packetAddress ) = 0;
		virtual void OnDisconnected( Packet* packet ) = 0;
	};

	/*! 
	 *  Translates Packets into Client System calls
	 */
	class ClientPacketTranslator : public IClientPacketTranslator
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~ClientPacketTranslator( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		ClientPacketTranslator( INetworkSystem* networkSystem, RakPeerInterface* networkInteface )
			: m_networkSystem( networkSystem )
			, m_networkInterface( networkInteface )
		{

		}

		void OnAdvertiseSystem( Packet* packet );
		void OnPacketReceived( Packet* packet );

		void OnDestroyEntity( const std::string& name );
		void OnChangeLevel( const std::string& levelName );
		void OnCreateEntity( const std::string& name, const std::string& filePath, const SystemAddress& packetAddress );
		void OnDisconnected( Packet* packet );

	private:

		ClientPacketTranslator( const ClientPacketTranslator & copy ) { };
		ClientPacketTranslator & operator = ( const ClientPacketTranslator & copy ) { return *this; };

		void OnComponentUpdate( RakNet::BitStream* stream );

		INetworkSystem* m_networkSystem;
		RakPeerInterface* m_networkInterface;
		
	};
};

#endif