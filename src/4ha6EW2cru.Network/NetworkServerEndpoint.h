/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkServerEndpoint.h
*  @date   2009/08/17
*/
#pragma once
#ifndef NETWORKSERVERENDPOINT_H
#define NETWORKSERVERENDPOINT_H

#include "INetworkServerController.hpp"
#include "INetworkServerEndpoint.hpp"
#include "INetworkInterface.hpp"
#include "INetworkSystemScene.hpp"

#include "Service/IServiceManager.h"

namespace Network
{
  /*! 
   *  The Server Endpoint for receiving Network messages
   */
  class GAMEAPI NetworkServerEndpoint : public INetworkServerEndpoint
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    ~NetworkServerEndpoint() { };


    /*! Default Constructor
    *
    * @return ()
    */
    NetworkServerEndpoint(INetworkInterface* networkInterface, INetworkSystemScene* networkScene, INetworkServerController* controller, Services::IServiceManager* serviceManager);


    /*! Initializes the Endpoint
    *
    * @return (void)
    */
    void Initialize();


    /*! Updates the Endpoint
    *
    * @param[in] float deltaMilliseconds
    * @return (void)
    */
    void Update(float deltaMilliseconds);


    /*! Called when a client has finished loading a level
    *
    * @param[in] RakNet::RPC3 * rpcFromNetwork
    * @return (void)
    */
    void LevelLoaded(RakNet::RPC3* rpcFromNetwork);


    /*! Called when a client has selected a character
    *
    * @param[in] const std::string & characterName
    * @param[in] RakNet::RPC3 * rpcFromnetwork
    * @return (void)
    */
    void SelectCharacter(const std::string& characterName, RakNet::RPC3* rpcFromnetwork);

    static void Net_LevelLoaded(RakNet::RakString levelName, RakNet::RPC3* rpcFromNetwork);
    static void Net_SelectCharacter(RakNet::RakString characterName, RakNet::RPC3* rpcFromnetwork);
    static void Net_MessageEntity(RakNet::RakString entityName, RakNet::RakString message, RakNet::BitStream& parameters, RakNet::RPC3* rpcFromNetwork);

    void MessageEntity(const std::string& entityName, const System::MessageType& message, AnyType::AnyTypeMap parameters, RakNet::RPC3* rpcFromNetwork);

  private:

    NetworkServerEndpoint(const NetworkServerEndpoint & copy) { };
    NetworkServerEndpoint & operator = (const NetworkServerEndpoint & copy) { return *this; };
    
    INetworkInterface* m_networkInterface;
    INetworkServerController* m_networkController;
    INetworkSystemScene* m_networkScene;
    Services::IServiceManager* m_serviceManager;

    static NetworkServerEndpoint* m_networkServerEndpoint;

  };
};

#endif