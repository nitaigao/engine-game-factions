#include <gtest/gtest.h>
using namespace testing;

#include "NetworkSystemComponent.h"
using namespace Network;

#include "Mocks/MockNetworkSystemProvider.hpp"

#include "Maths/MathVector3.hpp"
using namespace Maths;

class NetworkSystemComponent_Tests : public TestHarness< NetworkSystemComponent >
{

protected:

  void EstablishContext()
  {

  }


  void DestroyContext()
  {

  }

  NetworkSystemComponent* CreateSubject()
  {
    return new NetworkSystemComponent();
  }
};

TEST_F(NetworkSystemComponent_Tests, should_forward_internal_messages_to_registered_providers)
{
  AnyType::AnyTypeMap parameters;
  parameters[ System::Attributes::Position ] = MathVector3::Forward();

  std::string entityName = "hello";
  System::MessageType message = System::Messages::SetPosition;

  MockNetworkSystemProvider provider;
  EXPECT_CALL(provider, Message(m_subject, message, A< AnyType::AnyTypeMap >()));

  m_subject->SetAttribute(System::Attributes::Name, entityName);
  m_subject->AddProvider(&provider);
  m_subject->Observe(0, message, parameters);
}

TEST_F(NetworkSystemComponent_Tests, should_notify_network_when_created)
{
  std::string entityName = "hello";
  System::MessageType message = System::Messages::Entity::CreateEntity;

  MockNetworkSystemProvider provider;
  EXPECT_CALL(provider, Message(m_subject, message, An< AnyType::AnyTypeMap >()));

  m_subject->SetAttribute(System::Attributes::Name, entityName);
  m_subject->AddProvider(&provider);
  m_subject->Initialize();
}

TEST_F(NetworkSystemComponent_Tests, should_notify_network_when_destroyed)
{
  std::string entityName = "hello";
  System::MessageType message = System::Messages::Entity::DestroyEntity;

  MockNetworkSystemProvider provider;
  EXPECT_CALL(provider, Message(m_subject, message, An< AnyType::AnyTypeMap >()));

  m_subject->SetAttribute(System::Attributes::Name, entityName);
  m_subject->AddProvider(&provider);
  m_subject->Destroy();
}