/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ClientMessageRouter.h
*  @date   2009/08/11
*/
#pragma once
#ifndef CLIENTMESSAGEROUTER_H
#define CLIENTMESSAGEROUTER_H

#include "System/AnyType.hpp"
#include "System/SystemType.hpp"

#include "IServerAdvertisement.hpp"

#include <RakPeerInterface.h>
#include <BitStream.h>

namespace Network
{
	class IClientMessageRouter
	{

	public:

		virtual ~IClientMessageRouter( ) { };

		virtual void Connect( AnyType::AnyTypeMap &parameters ) = 0;
		virtual void Disconnect( ) = 0;
		virtual void GetServerAdvertisement( AnyType::AnyTypeMap &parameters, AnyType::AnyTypeMap &results ) = 0;
		virtual void SelectCharacter( const System::MessageType& message, AnyType::AnyTypeMap &parameters ) = 0;
		virtual void FindServers( ) = 0;
		virtual void PushMessage( const System::MessageType& message, AnyType::AnyTypeMap parameters ) = 0;
		virtual void UpdateServer( float deltaMilliseconds, float updateRate ) = 0;
		virtual void LevelLoaded( ) = 0;
	};

	/*! 
	 *  Routes Incoming Messages to the relevant parts of the client system
	 */
	class ClientMessageRouter : public IClientMessageRouter
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~ClientMessageRouter( ) { }


		/*! Default Constructor
		*
		* @return (  )
		*/
		ClientMessageRouter( RakPeerInterface* networkInterface )
			: m_networkInterface( networkInterface )
			, m_tickRate( 0.0f )
			, m_tickTotal( 0.0f )
		{

		}

		void Connect( AnyType::AnyTypeMap &parameters );
		void Disconnect( );
		
		void SelectCharacter( const System::MessageType& message, AnyType::AnyTypeMap &parameters );

		void FindServers( );
		void GetServerAdvertisement( AnyType::AnyTypeMap &parameters, AnyType::AnyTypeMap &results );

		void PushMessage( const System::MessageType& message, AnyType::AnyTypeMap parameters );
		void UpdateServer( float deltaMilliseconds, float updateRate );
		void LevelLoaded( );
		
	private:

		ClientMessageRouter( const ClientMessageRouter & copy ) { };
		ClientMessageRouter & operator = ( const ClientMessageRouter & copy ) { return *this; };

		SystemAddress m_serverAddress;
		RakPeerInterface* m_networkInterface;
		RakNet::BitStream m_sendBuffer;

		float m_tickRate;
		float m_tickTotal;
		
	};
};

#endif