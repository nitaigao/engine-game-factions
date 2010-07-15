#include <gtest/gtest.h>
using namespace testing;

#include "NetworkClientController.h"
using namespace Network;

#include "Mocks/MockNetworkInterface.hpp"

class NetworkClientController_Tests : public TestHarness< NetworkClientController >
{

protected:

  MockNetworkInterface* m_networkInterface;

  void EstablishContext()
  {
    m_networkInterface = new MockNetworkInterface();
  }


  void DestroyContext()
  {
    delete m_networkInterface;
  }

  NetworkClientController* CreateSubject()
  {
    return new NetworkClientController(m_networkInterface); 
  }
};


TEST_F(NetworkClientController_Tests, should_broadcast_offline_ping_when_looking_for_servers)
{
  int port = 0;
  EXPECT_CALL(*m_networkInterface, BroadcastOfflinePing(port));
  m_subject->FindServers(port);
}