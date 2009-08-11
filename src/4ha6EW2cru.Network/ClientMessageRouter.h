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

namespace Network
{
	class IClientMessageRouter
	{

	public:

		virtual ~IClientMessageRouter( ) { };

		virtual void Connect( AnyType::AnyTypeMap &parameters ) = 0;
		virtual void Disconnect( ) = 0;
		virtual void GetServerAdvertisement( AnyType::AnyTypeMap &parameters, AnyType::AnyTypeMap &results ) = 0;
		virtual void SelectCharacter( const System::Message& message, AnyType::AnyTypeMap &parameters ) = 0;
		virtual void FindServers( ) = 0;
		virtual void PushMessage( const System::Message& message, AnyType::AnyTypeMap parameters ) = 0;
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
		{

		}


		void Connect( AnyType::AnyTypeMap &parameters );
		void Disconnect( );
		
		void SelectCharacter( const System::Message& message, AnyType::AnyTypeMap &parameters );

		void FindServers( );
		void GetServerAdvertisement( AnyType::AnyTypeMap &parameters, AnyType::AnyTypeMap &results );

		void PushMessage( const System::Message& message, AnyType::AnyTypeMap parameters );
		
	private:

		SystemAddress m_serverAddress;
		RakPeerInterface* m_networkInterface;

		ClientMessageRouter( const ClientMessageRouter & copy ) { };
		ClientMessageRouter & operator = ( const ClientMessageRouter & copy ) { return *this; };
		
	};
};

#endif