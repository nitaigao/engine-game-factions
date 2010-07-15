#include <gtest/gtest.h>
using namespace testing;

#include "NetworkClientEndpoint.h"
using namespace Network;

#include <PluginInterface2.h>
#include <MessageIdentifiers.h>
#include <GetTIme.h>
using namespace RakNet;

#include "Mocks/MockNetworkInterface.hpp"
#include "Mocks/MockServiceManager.hpp"
#include "Mocks/MockService.h"
#include "Mocks/MockNetworkSystemScene.hpp"

#include "Events/EventManager.h"
using namespace Events;

#include "Maths/MathVector3.hpp"
using namespace Maths;

class NetworkClientEndpoint_Tests : public TestHarness<NetworkClientEndpoint>
{

protected:

  MockNetworkInterface* m_networkInterface;
  EventManager* m_eventManager;
  MockServiceManager* m_serviceManager;
  MockNetworkSystemScene* m_scene;

  void EstablishContext()
  {
    m_networkInterface = new MockNetworkInterface();
    m_scene = new MockNetworkSystemScene();
    m_eventManager = new EventManager();
    m_serviceManager = new MockServiceManager();
  }

  void DestroyContext()
  {
    delete m_networkInterface;
    delete m_scene;
    delete m_eventManager;
    delete m_serviceManager;
  }

  NetworkClientEndpoint* CreateSubject()
  {
    return new NetworkClientEndpoint(m_networkInterface, m_scene, m_eventManager, m_serviceManager);
  }
};

TEST_F(NetworkClientEndpoint_Tests, should_receive_offline_pong_messages)
{
  std::string serverName = "serverName";
  int players = 10;
  int maxPlayers = 32;
  std::string mapName = "mapName";
  std::string serverAddress = "127.0.0.1";
  unsigned int port = 8989;

  BitStream stream;
  stream.Write((MessageID) ID_PONG);
  stream.Write(GetTime());
  stream.Write(RakString(serverName));
  stream.Write(players);
  stream.Write(maxPlayers);
  stream.Write(RakString(mapName));

  Packet* p = new Packet();
  p->systemAddress = SystemAddress(serverAddress.c_str(), port);
  p->data = stream.GetData();
  p->length = stream.GetNumberOfBytesUsed();

  EXPECT_CALL(*m_networkInterface, Receive())
    .WillOnce(Return(p));

  EXPECT_CALL(*m_networkInterface, DeAllocatePacket(p));

  m_subject->Update(99);

  delete p;
}

TEST_F(NetworkClientEndpoint_Tests, should_destroy_an_entity_if_not_passive)
{
  MockService mockService;

  EXPECT_CALL(*m_serviceManager, FindService(System::Types::ENTITY))
    .WillOnce(Return(&mockService));

  std::string entityName = "test";
  
  EXPECT_CALL(mockService, ProcessMessage(System::Messages::Entity::DestroyEntity, An<AnyType::AnyTypeMap>()))
    .WillOnce(Return(AnyType::AnyTypeMap()));

  m_subject->DestroyEntity(entityName, 0);
}

TEST_F(NetworkClientEndpoint_Tests, should_message_entity_mouse_moved_if_not_passive)
{
  AnyType::AnyTypeMap parameters;
  parameters[ System::Parameters::DeltaX ] = 0.1f;

  SystemAddress entityName("127.0.0.0", 8989);

  SystemAddress sender("127.0.0.1", 8989);

  EXPECT_CALL(*m_scene, MessageComponent(entityName.ToString(), System::Messages::Mouse_Moved, An<AnyType::AnyTypeMap>()));

  m_subject->MessageEntity(entityName.ToString(), System::Messages::Mouse_Moved, parameters, sender);
}

TEST_F(NetworkClientEndpoint_Tests, when_a_server_responds__then_the_client_should_broadcast_that_it_has_found_the_server)
{
  
}