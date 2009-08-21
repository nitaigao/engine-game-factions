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


		/*! Sends the SetPosition message for an Entity across the Network
		*
		* @param[in] const std::string & name
		* @param[in] const Maths::MathVector3 & position
		* @return ( void )
		*/
		void SetPosition( const std::string& name, const Maths::MathVector3& position );


		/*! Sends the SetOrientation message for an given Entity across the network
		*
		* @param[in] const std::string & name
		* @param[in] const Maths::MathQuaternion & orientation
		* @return ( void )
		*/
		void SetOrientation( const std::string& name, const Maths::MathQuaternion& orientation );


		/*! Instructs the Controller that a client has connected
		*
		* @param[in] const SystemAddress & clientAddress
		* @return ( void )
		*/
		void ClientConnected( const SystemAddress& clientAddress );


		/*! Broadcasts to the connected clients to create the Entity
		*
		* @param[in] const std::string & entityName
		* @param[in] const std::string & filePath
		* @return ( void )
		*/
		void CreateEntity( const std::string& entityName, const std::string& entityType );


		/*! Pushes a world update to the client at the given address
		*
		* @param[in] const SystemAddress & address
		* @return ( void )
		*/
		void SendWorldUpdate( const SystemAddress& address );

	private:

		NetworkServerController( const NetworkServerController & copy ) { };
		NetworkServerController & operator = ( const NetworkServerController & copy ) { return *this; };

		INetworkInterface* m_networkInterface; 
		Services::IServiceManager* m_serviceManager;
	};
};

#endif