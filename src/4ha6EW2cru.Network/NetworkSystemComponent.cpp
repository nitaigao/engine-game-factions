#include "NetworkSystemComponent.h"

#include "Maths/MathVector3.hpp"
using namespace Maths;

#include "Logging/Logger.h"
using namespace Logging;

namespace Network
{
	AnyType NetworkSystemComponent::Observe( const ISubject* subject, const System::MessageType& message, AnyType::AnyTypeMap parameters )
	{
		if ( message == System::Messages::SetPosition )
		{
			m_attributes[ System::Attributes::Position ] = parameters[ System::Attributes::Position ].As< MathVector3 >( );

			if ( m_accumulator * 1000 >= 33.3f )
			{
				for ( INetworkProvider::NetworkProviderList::iterator i = m_networkProviders.begin( ); i != m_networkProviders.end( ); ++i )
				{
					( *i )->Message( this, System::Messages::Network::Server::SetServerPosition, parameters );
				}

				m_accumulator = 0;
			}
		}

		for ( INetworkProvider::NetworkProviderList::iterator i = m_networkProviders.begin( ); i != m_networkProviders.end( ); ++i )
		{
			( *i )->Message( this, message, parameters );
		}

		return AnyType( );
	}

	void NetworkSystemComponent::Initialize( )
	{
		for ( INetworkProvider::NetworkProviderList::iterator i = m_networkProviders.begin( ); i != m_networkProviders.end( ); ++i )
		{
			( *i )->Message( this, System::Messages::Entity::CreateEntity, m_attributes );
		}
	}

	void NetworkSystemComponent::Destroy( )
	{
		for ( INetworkProvider::NetworkProviderList::iterator i = m_networkProviders.begin( ); i != m_networkProviders.end( ); ++i )
		{
			( *i )->Message( this, System::Messages::Entity::DestroyEntity, m_attributes );
		}
	}

	AnyType NetworkSystemComponent::PushMessage( const System::MessageType& message, AnyType::AnyTypeMap parameters )
	{
		if ( message == System::Messages::SetPosition )
		{
			MathVector3 networkPosition = parameters[ System::Attributes::Position ].As< MathVector3 >( );
			MathVector3 currentPosition = m_attributes[ System::Attributes::Position ].As< MathVector3 >( );
			MathVector3 newPosition = networkPosition;

			MathVector3 positionDifference = networkPosition - currentPosition;
			float distanceApart = positionDifference.Length( );

			if( distanceApart > 0.1f && distanceApart < 2.0f ) // between 1cm and 2m apart
			{
				newPosition = currentPosition + ( positionDifference * 0.1f ); // smooth the difference by 10%
				Net( "Old:", currentPosition, "New:", newPosition, "Smooth:", newPosition );
			}

			parameters[ System::Attributes::Position ] = newPosition;
		}

		return m_observer->Observe( this, message, parameters );
	}

	void NetworkSystemComponent::Update( float deltaMilliseconds )
	{
		 m_accumulator += deltaMilliseconds;
	}
}