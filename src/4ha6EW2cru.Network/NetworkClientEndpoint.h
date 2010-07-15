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

#include "Events/IEventManager.hpp"
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
    NetworkClientEndpoint( INetworkInterface* networkInterface, INetworkSystemScene* networkScene, Events::IEventManager* eventManager, Services::IServiceManager* serviceManager );


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

    void LoadLevel( const std::string& levelName );
    void UpdateWorld( RakNet::BitStream& stream, RakNet::RPC3* rpcFromNetwork );
    void CreateEntity( RakNet::RakString entityName, RakNet::RakString filePath, RakNet::RPC3* rpcFromNetwork );
    void DestroyEntity( RakNet::RakString entityname, RakNet::RPC3* rpcFromNetwork );
    void MessageEntity( const std::string& entityName, const System::MessageType& message, AnyType::AnyTypeMap parameters, const SystemAddress& sender );
    

  private:

    NetworkClientEndpoint( const NetworkClientEndpoint & copy ) { };
    NetworkClientEndpoint & operator = ( const NetworkClientEndpoint & copy ) { return *this; };

    INetworkInterface* m_networkInterface;
    INetworkSystemScene* m_networkScene;
    IServerCache* m_serverCache;

    Events::IEventManager* m_eventManager;
    Services::IServiceManager* m_serviceManager;

    bool m_isPassive;

    static NetworkClientEndpoint* m_clientEndpoint;
    
  };
};

#endif