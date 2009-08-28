#include "EventManager.h"

#include "../Logging/Logger.h"
using namespace Logging;

#include "../Exceptions/NullReferenceException.hpp"
#include "../Exceptions/UnInitializedException.hpp"
#include "../Exceptions/AlreadyInitializedException.hpp"
using namespace Exceptions;

namespace Events
{
	void EventManager::QueueEvent( const IEvent* event )
	{
		if ( 0 == event )
		{
			NullReferenceException e( "EventManager::QueueEvent - Attempted to add a NULL Event to the Queue" );
			Fatal( e.what ( ) );
			throw e;
		}

		m_eventQueue.push( event );
	}

	void EventManager::TriggerEvent( const IEvent* event )
	{
		if ( 0 == event )
		{
			NullReferenceException e( "EventManager::TriggerEvent - Attempted to trigger a NULL Event" );
			Fatal( e.what ( ) );
			throw e;
		}

		IEventListener::EventListenerList eventListeners( m_eventListeners );

		for ( IEventListener::EventListenerList::iterator i = eventListeners.begin( ); i != eventListeners.end( ); ++i )
		{
			if ( 
				( *i )->GetEventType( ) == event->GetEventType( ) && !( *i )->IsMarkedForDeletion( ) || 
				( *i )->GetEventType( ) == ALL_EVENTS && !( *i )->IsMarkedForDeletion( ) 
				)
			{
				( *i )->HandleEvent( event );
			}
		}

		delete event;
	}

	void EventManager::Update( float deltaMilliseconds )
	{
		while( m_eventQueue.size( ) > 0 )
		{
			this->TriggerEvent( m_eventQueue.front( ) );
			m_eventQueue.pop( );
		}

		for ( IEventListener::EventListenerList::iterator i = m_eventListeners.begin( ); i != m_eventListeners.end( ); )
		{
			if ( ( *i )->IsMarkedForDeletion( ) )
			{
				delete ( *i );
				i = m_eventListeners.erase( i );
			}
			else
			{
				++i;
			}
		}
	}

	EventManager::~EventManager()
	{
		//Info( "Releasing Event Manager" );

		while( m_eventQueue.size( ) > 0 )
		{
			delete m_eventQueue.front( );
			m_eventQueue.pop( );
		}

		for( IEventListener::EventListenerList::iterator i = m_eventListeners.begin( ); i != m_eventListeners.end( ); ++i )
		{
			delete ( *i );
		}

		m_eventListeners.clear( );
	}

	void EventManager::RemoveEventListener( IEventListener* eventListener )
	{
		for ( IEventListener::EventListenerList::iterator i = m_eventListeners.begin( ); i != m_eventListeners.end( ); ++i )
		{
			if (
				eventListener->GetHandlerAddress( ) == ( *i )->GetHandlerAddress( ) &&
				eventListener->GetEventType( ) == ( *i )->GetEventType( ) &&
				eventListener->GetHandlerFunctionName( ) == ( *i )->GetHandlerFunctionName( )
				)
			{
				( *i )->MarkForDeletion( );
			}
		}

		delete eventListener;
	}

	void EventManager::AddEventListener( IEventListener* eventListener )
	{
		m_eventListeners.push_back( eventListener );
	}
}