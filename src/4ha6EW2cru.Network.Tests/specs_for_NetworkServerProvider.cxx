#include <gtest/gtest.h>
using namespace testing;

#include "NetworkServerProvider.h"
using namespace Network;

#include "Mocks/MockNetworkInterface.hpp"
#include "Mocks/MockNetworkServerController.hpp"
#include "Mocks/MockNetworkServerEndpoint.hpp"
#include "Mocks/MockNetworkSystemComponent.hpp"
#include "Mocks/MockConfiguration.hpp"

namespace BaseContext
{
  class NetworkServerProvider_BaseContext : public TestHarness< NetworkServerProvider >
  {

  protected:

    MockNetworkInterface* m_interface;
    MockNetworkServerController* m_controller;
    MockNetworkServerEndpoint* m_endpoint;
    MockConfigurartion* m_configuration;

    virtual void EstablishContext()
    {
      m_interface = new MockNetworkInterface();
      m_controller = new MockNetworkServerController();
      m_endpoint = new MockNetworkServerEndpoint();
      m_configuration = new MockConfigurartion();

    }

    virtual void DestroyContext()
    {
      delete m_configuration;
    }

    NetworkServerProvider* CreateSubject()
    {
      return new NetworkServerProvider(m_configuration, m_interface, m_controller, m_endpoint);
    }
  };
};

namespace given_a_component_sends_a_message
{
  class when_the_message_is_sent : public BaseContext::NetworkServerProvider_BaseContext
  {
    MockNetworkSystemComponent* m_component;
  
  protected:

    void EstablishContext()
    {
      BaseContext::NetworkServerProvider_BaseContext::EstablishContext();

      m_component = new MockNetworkSystemComponent();
    }

    void DestroyContext()
    {
      BaseContext::NetworkServerProvider_BaseContext::DestroyContext();

      delete m_component;
    }
  
    void Expecting()
    {
      EXPECT_CALL(*m_component, GetName())
        .WillRepeatedly(Return("name"));
    }
  
    void When()
    {
      m_subject->Message(m_component, System::Messages::Move_Forward_Pressed, AnyType::AnyTypeMap());
    }
    
  };

  TEST_F(when_the_message_is_sent, then_the_message_should_be_sent_using_the_name_of_the_component) { }
}