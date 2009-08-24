/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkServerController.h
*  @date   2009/08/17
*/
#pragma once
#ifndef NETWORKSERVERCONTROLLER_H
#define NETWORKSERVERCONTROLLER_H

#include "INetworkServerController.hpp"
#include "INetworkInterface.hpp"

#include "Service/IServiceManager.h"

namespace Network
{
	/*! 
	 *  A Controller that transmits messages across the network
	 */
	class GAMEAPI NetworkServerController : public INetworkServerController
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~NetworkServerController( );


		/*! Default Constructor
		*
		* @return (  )
		*/
		NetworkServerController( INetworkInterface* networkInterface, Services::IServiceManager* serviceManager )
			: m_networkInterface( networkInterface )
			, m_serviceManager( serviceManager )
		{

		}


		/*! Initializes the Server Controller
		*
		* @return ( void )
		*/
		void Initialize( );


		/*! Instructs the Controller that a client has connected
		*
		* @param[in] const SystemAddress & clientAddress
		* @return ( void )
		*/
		void ClientConnected( const SystemAddress& clientAddress );


		/*! Instructs the controller that a client has disconnected
		*
		* @param[in] const SystemAddress & clientDisconnected
		* @return ( void )
		*/
		void ClientDisconnected( const SystemAddress& clientAddress );


		/*! Broadcasts to the connected clients to create the Entity
		*
		* @param[in] const std::string & entityName
		* @param[in] const std::string & filePath
		* @return ( void )
		*/
		void CreateEntity( const std::string& entityName, const std::string& entityType );


		/*! Broadcasts to the connected clients to destroy the entity
		*
		* @param[in] const std::string & entityName
		* @return ( void )
		*/
		void DestroyEntity( const std::string& entityName );


		/*! Pushes a world update to the client at the given address
		*
		* @param[in] const SystemAddress & address
		* @return ( void )
		*/
		void SendWorldUpdate( const SystemAddress& address );


		/*! Sends an Entity Position update to all clients
		*
		* @param[in] const std::string & entityName
		* @param[in] const Maths::MathVector3 & position
		* @return ( void )
		*/
		void SetEntityPosition( const std::string& entityName, const Maths::MathVector3& position );


		/*! Forwards the Message to the given Entity
		*
		* @param[in] const std::string & entityName
		* @param[in] const System::MessageType & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		void MessageEntity( const std::string& entityName, const System::MessageType& message, AnyType::AnyTypeMap parameters );

	private:

		NetworkServerController( const NetworkServerController & copy ) { };
		NetworkServerController & operator = ( const NetworkServerController & copy ) { return *this; };

		INetworkInterface* m_networkInterface; 
		Services::IServiceManager* m_serviceManager;
	};
};

#endif