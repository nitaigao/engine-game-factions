/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkInterface.h
*  @date   2009/08/17
*/
#pragma once
#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include "INetworkInterface.hpp"

#include <RakPeerInterface.h>

namespace Network
{
  /*! 
   *  Transmits and Received data across the Network
   */
  class NetworkInterface : public INetworkInterface
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    ~NetworkInterface();


    /*! Default Constructor
    *
    * @return ()
    */
    NetworkInterface();


    /*! Initializes the Network Interface
    *
    * @param[in] int maxConnections
    * @return (void)
    */
    void Initialize(unsigned int port, int maxConnections);


    /*! Shuts the Network Interface Down
    *
    * @return (void)
    */
    void Destroy(unsigned int timeToBlock);

    /*! Receives information from the Network
    *
    * @return (Packet*)
    */
    Packet* Receive();


    /*! Deallocates the Packet and deletes the pointer to it
    *
    * @param[in] Packet * packet
    * @return (void)
    */
    void DeAllocatePacket(Packet* packet);


    /*! Sets the Information that will be sent in an offline Ping Response
    *
    * @param[in] BitStream * information
    * @return (void)
    */
    void SetOfflinePingInformation(RakNet::BitStream* information);


    /*! Returns the Number of Peer connected to the Interface
    *
    * @return (int)
    */
    inline int GetConnectionCount() { return m_networkAdapter->NumberOfConnections(); };


    /*! Connects the interface to a Peer
    *
    * @param[in] const std::string address
    * @return (void)
    */
    void Connect(unsigned int port, const std::string& address);


    /*! Disconnects the Interface from it's connected Peer
    *
    * @return (void)
    */
    void Disconnect();


    /*! Attaches a plugin to the interface
    *
    * @param[in] PluginInterface2 * plugin
    * @return (void)
    */
    void AttachPlugin(PluginInterface2* plugin);


    /*! Returns the RPC interface
    *
    * @return (RakNet::RPC3*)
    */
    inline RakNet::RPC3* GetRPC() { return m_rpc; }


    /*! Broadcasts the Network with a Ping
    *
    * @return (void)
    */
    void BroadcastOfflinePing(unsigned int port);


    /*! Finds the NetworkAddress for communicating with the given address
    *
    * @param[in] const SystemAddress & address
    * @return (SystemAddress)
    */
    SystemAddress GetAddress(const SystemAddress& address);

  private:

    NetworkInterface(const NetworkInterface & copy) { };
    NetworkInterface & operator = (const NetworkInterface & copy) { return *this; };

    RakPeerInterface* m_networkAdapter;
    RakNet::RPC3* m_rpc;
    
  };
};

#endif