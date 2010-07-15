#include <gtest/gtest.h>
using namespace testing;

#include "Events/EventManager.h"
using namespace Events;

#include "Events/Event.h"

#include "../Mocks/MockEventListener.hpp"

namespace in_general
{
  class EventManager_BaseContext : public TestHarness< EventManager >
  {

  protected:

    MockEventListener* m_eventListener;

    virtual void EstablishContext()
    {
      m_eventListener = new MockEventListener();
    }

    virtual void DestroyContext()
    {
      //delete m_eventListener;
    }

    EventManager* CreateSubject()
    {
      return new EventManager(); 
    }
  };

  class when_an_event_is_queued : public EventManager_BaseContext
  {
  
  protected:
  
    void Expecting()
    {
      EXPECT_CALL(*m_eventListener, HandleEvent(A< const IEvent* >()));
    }
  
    void When()
    {
      m_subject->AddEventListener(EventTypes::TEST_EVENT, m_eventListener);
      m_subject->QueueEvent(EventTypes::TEST_EVENT, 0);
      m_subject->Update(99);
    }
    
  };

  TEST_F(when_an_event_is_queued, then_the_event_listener_should_be_called_on_the_next_update) { }
  
  class when_an_event_is_fired : public EventManager_BaseContext
  {
  
  protected:

    IEvent* m_event;
    std::string m_eventType;

    void EstablishContext()
    {
      EventManager_BaseContext::EstablishContext();

      m_eventType = "SOME_EVENT";

      m_event = new Event(m_eventType);
    }
  
    void Expecting()
    {
      EXPECT_CALL(*m_eventListener, HandleEvent(m_event));
    }
  
    void When()
    {
      m_subject->AddEventListener(m_eventType, m_eventListener);
      m_subject->QueueEvent(m_event);
      m_subject->Update(0);
    }
    
  };

  TEST_F(when_an_event_is_fired, then_the_handler_should_be_executed) { };

  class when_an_event_listener_is_removed : public EventManager_BaseContext
  {

    IEvent* m_event;
    std::string m_eventType;

    MockEventListener* m_eventListenerToRemove;
  
  protected:

    void EstablishContext()
    {
      EventManager_BaseContext::EstablishContext();
      
      m_eventType = "SOME_EVENT";
      m_event = new Event(m_eventType); 
      m_eventListenerToRemove = new MockEventListener();
    }
  
    void Expecting()
    {
      EXPECT_CALL(*m_eventListener, GetHandlerAddress()).WillOnce(Return(0));
      EXPECT_CALL(*m_eventListener, GetHandlerFunctionName()).WillOnce(Return("test"));
      EXPECT_CALL(*m_eventListener, IsMarkedForDeletion()).WillOnce(Return(true));

      EXPECT_CALL(*m_eventListenerToRemove, GetHandlerAddress()).WillOnce(Return(0));
      EXPECT_CALL(*m_eventListenerToRemove, GetHandlerFunctionName()).WillOnce(Return("test"));

      EXPECT_CALL(*m_eventListener, HandleEvent(m_event))
        .Times(0);
    }
  
    void When()
    {
      m_subject->AddEventListener(m_eventType, m_eventListener);
      m_subject->RemoveEventListener(m_eventType, m_eventListenerToRemove);
      m_subject->TriggerEvent(m_event);
    }
    
  };

  TEST_F(when_an_event_listener_is_removed, then_it_should_no_longer_receive_events) { };
};