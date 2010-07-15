#include <gtest/gtest.h>
using namespace testing;

#include "NetworkSystemScene.h"
using namespace Network;

#include "Mocks/MockNetworkSystemProvider.hpp"
#include "Mocks/MockNetworkSystemComponentFactory.hpp"
#include "Mocks/MockNetworkSystemComponent.hpp"

class NetworkSystemScene_Tests : public TestHarness<NetworkSystemScene>
{

protected:

  MockNetworkSystemComponentFactory* m_componentFactory;
  MockNetworkSystemProvider* m_provider;

  void EstablishContext()
  {
    m_componentFactory = new MockNetworkSystemComponentFactory();
    m_provider = new MockNetworkSystemProvider();
  }

  void DestroyContext()
  {
    delete m_provider;
  }

  NetworkSystemScene* CreateSubject()
  {
    return new NetworkSystemScene(m_componentFactory);
  }
};


TEST_F(NetworkSystemScene_Tests, should_update_providers)
{
  float delta = 99;

  EXPECT_CALL(*m_provider, Update(delta)); 

  m_subject->AddNetworkProvider(m_provider);
  m_subject->Update(delta);
}


TEST_F(NetworkSystemScene_Tests, should_add_providers_to_a_new_component)
{
  MockNetworkSystemComponent* component = new MockNetworkSystemComponent();

  std::string name = "test";

  EXPECT_CALL(*m_componentFactory, Create(name))
    .WillOnce(Return(component));

  EXPECT_CALL(*component, AddProvider(m_provider));
 
  m_subject->AddNetworkProvider(m_provider);
  m_subject->CreateComponent(name, "default");

  delete component;
}

TEST_F(NetworkSystemScene_Tests, should_release_all_providers)
{
  EXPECT_CALL(*m_provider, Destroy()); 

  m_subject->AddNetworkProvider(m_provider);
  m_subject->Destroy();
}