/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkServerController.hpp
*  @date   2009/08/16
*/
#pragma once
#ifndef INETWORKSERVERCONTROLLER_HPP
#define INETWORKSERVERCONTROLLER_HPP

#include <string>

#include "INetworkController.hpp"

#include "Maths/MathVector3.hpp"
#include "Maths/MathQuaternion.hpp"

#include <RakNetTypes.h>

namespace Network
{
	/*! 
	 *  Dispatches Server Messages to the Network
	 */
	class GAMEAPI INetworkServerController : public INetworkController
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~INetworkServerController( ) { };


		/*! Initialized the Server Controller
		 *
		 * @return ( void )
		 */
		virtual void Initialize( ) = 0;

		
		/*! Instructs the Controller that a client has connected
		 *
		 * @param[in] const SystemAddress & clientAddress
		 * @return ( void )
		 */
		virtual void ClientConnected( const SystemAddress& clientAddress ) = 0;


		/*! Instructs the controller that a client has disconnected
		 *
		 * @param[in] const SystemAddress & clientDisconnected
		 * @return ( void )
		 */
		virtual void ClientDisconnected( const SystemAddress& clientDisconnected ) = 0;


		/*! Broadcasts to the connected clients to create the Entity
		 *
		 * @param[in] const std::string & entityName
		 * @param[in] const std::string & filePath
		 * @return ( void )
		 */
		virtual void CreateEntity( const std::string& entityName, const std::string& filePath ) = 0;


		/*! Broadcasts to the connected clients to destroy the entity
		 *
		 * @param[in] const std::string & entityName
		 * @return ( void )
		 */
		virtual void DestroyEntity( const std::string& entityName ) = 0;


		/*! Pushes a world update to the client at the given address
		 *
		 * @param[in] const SystemAddress & address
		 * @return ( void )
		 */
		virtual void SendWorldUpdate( const SystemAddress& address ) = 0;


		/*! Sends an Entity Position update to all clients
		 *
		 * @param[in] const std::string & entityName
		 * @param[in] const Maths::MathVector3 & position
		 * @return ( void )
		 */
		virtual void SetEntityPosition( const std::string& entityName, const Maths::MathVector3& position ) = 0;
		
	};
};

#endif