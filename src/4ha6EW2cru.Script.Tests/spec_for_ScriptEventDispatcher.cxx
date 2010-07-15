#include <gtest/gtest.h>
using namespace testing;

#include "ScriptEventDispatcher.h"
using namespace Script;

#include "Mocks/MockEventManager.hpp"
#include "Mocks/MockScriptFunctionHandler.hpp"

#include "Events/IEventListener.hpp"
using namespace Events;

namespace given_a_script_is_running
{
  class ScriptEventDispatcher_BaseContext : public TestHarness< ScriptEventDispatcher >
  {

  protected:

    MockEventManager* m_eventManager;

    virtual void EstablishContext( )
    {
      m_eventManager = new MockEventManager( );
    }

    virtual void DestroyContext( )
    {
      delete m_eventManager;
    }

    ScriptEventDispatcher* CreateSubject( )
    {
      return new ScriptEventDispatcher( m_eventManager ); 
    }
  };
  
  class when_registering_for_an_event : public ScriptEventDispatcher_BaseContext
  {
  
  protected:
  
    void Expecting( )
    {
      EXPECT_CALL( *m_eventManager, AddEventListener( A< const std::string& >( ), An< IEventListener* >( ) ) )
        .WillOnce( Invoke( MockEventManager::ConsumeEventListener ) );

      EXPECT_CALL( *m_eventManager, RemoveEventListener( A< const std::string& >( ), An< IEventListener* >( ) ) )
        .WillOnce( Invoke( MockEventManager::ConsumeEventListener ) );
    }

    void When( )
    {
      m_subject->RegisterEventHandler( EventTypes::TEST_EVENT, new MockScriptFunctionHandler( ) );

      //m_subject->Destroy( );
    }
    
  };

  //TEST_F( when_registering_for_an_event, then_the_event_manager_should_be_informed ) { }
  TEST_F( when_registering_for_an_event, then_the_handler_should_receive_events ) { };
};