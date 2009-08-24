/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkClientEndpoint.h
*  @date   2009/08/19
*/
#pragma once
#ifndef NETWORKCLIENTENDPOINT_H
#define NETWORKCLIENTENDPOINT_H

#include "INetworkClientEndpoint.hpp"
#include "INetworkInterface.hpp"
#include "INetworkSystemScene.hpp"
#include "IServerCache.hpp"

#include "Events/EventManager.h"
#include "Service/IServiceManager.h"

#include "Maths/MathVector3.hpp"

namespace Network
{
	/*! 
	 *  Endpoint for Incoming client information
	 */
	class GAMEAPI NetworkClientEndpoint : public INetworkClientEndpoint
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~NetworkClientEndpoint( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		NetworkClientEndpoint( INetworkInterface* networkInterface, INetworkSystemScene* networkScene, IServerCache* serverCache, Events::EventManager* eventManager, Services::IServiceManager* serviceManager );


		/*! Initializes the Endpoint
		*
		* @return ( void )
		*/
		void Initialize( );


		/*! Updates the Endpoint
		*
		* @param[in] float deltaMilliseconds
		* @return ( void )
		*/
		void Update( float deltaMilliseconds );


		/*! Stops the Endpoint from Receiving data
		*
		* @param[in] bool isPassive
		* @return ( void )
		*/
		inline void SetPassive( bool isPassive ) { m_isPassive = isPassive; };


		static void Net_LoadLevel( RakNet::RakString levelName, RakNet::RPC3* rpcFromNetwork );
		static void Net_UpdateWorld( RakNet::BitStream& stream, RakNet::RPC3* rpcFromNetwork );

		static void Net_CreateEntity( RakNet::RakString entityName, RakNet::RakString filePath, RakNet::RPC3* rpcFromNetwork );
		static void Net_DestroyEntity( RakNet::RakString entityname, RakNet::RPC3* rpcFromNetwork );
		static void Net_MessageEntity( RakNet::RakString entityName, RakNet::RakString message, RakNet::BitStream& parameters, RakNet::RPC3* rpcFromNetwork );
		static void Net_SetEntityPosition( RakNet::RakString entityName, const Maths::MathVector3& position, RakNet::RPC3* rpcFromNetwork );

		void UpdateWorld( RakNet::BitStream& stream, RakNet::RPC3* rpcFromNetwork );
		void CreateEntity( RakNet::RakString entityName, RakNet::RakString filePath, RakNet::RPC3* rpcFromNetwork );
		void DestroyEntity( RakNet::RakString entityname, RakNet::RPC3* rpcFromNetwork );
		void MessageEntity( const std::string& entityName, const System::MessageType& message, AnyType::AnyTypeMap parameters, RakNet::RPC3* rpcFromNetwork );
		void SetEntityPosition( RakNet::RakString entityName, const Maths::MathVector3& position, RakNet::RPC3* rpcFromNetwork );
		

	private:

		NetworkClientEndpoint( const NetworkClientEndpoint & copy ) { };
		NetworkClientEndpoint & operator = ( const NetworkClientEndpoint & copy ) { return *this; };

		INetworkInterface* m_networkInterface;
		INetworkSystemScene* m_networkScene;
		IServerCache* m_serverCache;

		Events::EventManager* m_eventManager;
		Services::IServiceManager* m_serviceManager;

		bool m_isPassive;

		static NetworkClientEndpoint* m_clientEndpoint;
		
	};
};

#endif