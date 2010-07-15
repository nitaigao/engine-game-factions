#include "precompiled.h"

#include "NetworkInterface.h"

#include <RakPeer.h>
#include <RakNetworkFactory.h>
using namespace RakNet;

namespace Network
{
  NetworkInterface::~NetworkInterface()
  {
    RakNetworkFactory::DestroyRakPeerInterface(m_networkAdapter);
    delete m_rpc;
  }

  NetworkInterface::NetworkInterface()
    : m_networkAdapter(RakNetworkFactory::GetRakPeerInterface())
    , m_rpc(new RakNet::RPC3())
  {

  }

  void NetworkInterface::Initialize(unsigned int port, int maxConnections)
  {
    m_networkAdapter->SetMaximumIncomingConnections(maxConnections);

    SocketDescriptor descriptor(port, 0);
    m_networkAdapter->Startup(maxConnections, 0, &descriptor, 1);
    m_networkAdapter->SetOccasionalPing(true);
    m_networkAdapter->AttachPlugin(m_rpc);
  }

  void NetworkInterface::Destroy(unsigned int timeToBlock)
  {
    m_networkAdapter->Shutdown(timeToBlock);
  }

  Packet* NetworkInterface::Receive()
  {
    return m_networkAdapter->Receive();
  }

  void NetworkInterface::DeAllocatePacket(Packet* packet)
  {
    m_networkAdapter->DeallocatePacket(packet);
  }

  void NetworkInterface::SetOfflinePingInformation(BitStream* information)
  {
    m_networkAdapter->SetOfflinePingResponse((const char*) information->GetData(), information->GetNumberOfBytesUsed());
  }

  void NetworkInterface::Connect(unsigned int port, const std::string& address)
  {
    m_networkAdapter->Connect(address.c_str(), port, 0, 0);
  }

  void NetworkInterface::Disconnect()
  {
    m_networkAdapter->CloseConnection(m_networkAdapter->GetSystemAddressFromIndex(0), true);
  }

  void NetworkInterface::AttachPlugin(PluginInterface2* plugin)
  {
    m_networkAdapter->AttachPlugin(plugin);
  }

  void NetworkInterface::BroadcastOfflinePing(unsigned int port)
  {
    m_networkAdapter->Ping("255.255.255.255", port, true);
  }

  SystemAddress NetworkInterface::GetAddress(const SystemAddress& address)
  {
    return m_networkAdapter->GetExternalID(address);
  }
}