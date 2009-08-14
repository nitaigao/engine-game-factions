/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ServerPacketTranslator.h
*  @date   2009/08/12
*/
#pragma once
#ifndef SERVERPACKETTRANSLATOR_H
#define SERVERPACKETTRANSLATOR_H

#include "INetworkSystem.hpp"

#include <RakPeerInterface.h>
#include <string>

#include <RakString.h>
#include <BitStream.h>

namespace Network
{
	class IServerPacketTranslator
	{
	public:

		virtual void OnPacketReceived( Packet* packet ) = 0;
		virtual void OnClientConnected( Packet* packet ) = 0;
		virtual void OnClientDisconnected( Packet* packet ) = 0;
		virtual void OnAdvertiseSystem( Packet* packet, const std::string& serverName, int maxPlayers, int playerCount ) = 0;
	};

	/*! 
	 *  Translates incoming packs to system calls for the server
	 */
	class ServerPacketTranslator : public IServerPacketTranslator
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~ServerPacketTranslator( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		ServerPacketTranslator( INetworkSystem* networkSystem, RakPeerInterface* networkInteface )
			: m_networkSystem( networkSystem )
			, m_networkInterface( networkInteface )
		{

		}

		void OnPacketReceived( Packet* packet );
		void OnClientConnected( Packet* packet );
		void OnClientDisconnected( Packet* packet );
		void OnAdvertiseSystem( Packet* packet, const std::string& serverName, int maxPlayers, int playerCount );

	private:

		ServerPacketTranslator( const ServerPacketTranslator & copy ) { };
		ServerPacketTranslator & operator = ( const ServerPacketTranslator & copy ) { return *this; };

		void OnComponentUpdate( const std::string& message, RakNet::BitStream* stream );
		void OnCharacterSelected( const std::string& clientName, RakNet::BitStream* stream );
		void OnLevelLoaded( const SystemAddress& clientAddress );

		INetworkSystem* m_networkSystem;
		RakPeerInterface* m_networkInterface;
		
	};
};

#endif