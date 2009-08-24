#include "NetworkSystemComponent.h"

#include "NetworkSystemScene.h"

#include "Maths/MathVector3.hpp"
#include "Maths/MathQuaternion.hpp"
using namespace Maths;

#include "Logging/Logger.h"
using namespace Logging;

namespace Network
{
	AnyType NetworkSystemComponent::Observe( const ISubject* subject, const System::MessageType& message, AnyType::AnyTypeMap parameters )
	{
		for ( INetworkProvider::NetworkProviderList::iterator i = m_networkProviders.begin( ); i != m_networkProviders.end( ); ++i )
		{
			( *i )->Message( m_attributes[ System::Attributes::Name ].As< std::string >( ), message, parameters );
		}

		return AnyType( );
	}

	void NetworkSystemComponent::MessageFromNetwork( const System::MessageType& message, AnyType::AnyTypeMap parameters )
	{
		this->PushMessage( message, parameters );
	}

	void NetworkSystemComponent::Initialize( )
	{
		for ( INetworkProvider::NetworkProviderList::iterator i = m_networkProviders.begin( ); i != m_networkProviders.end( ); ++i )
		{
			( *i )->Message( m_attributes[ System::Attributes::Name ].As< std::string >( ), System::Messages::Entity::CreateEntity, m_attributes );
		}
	}

	void NetworkSystemComponent::Destroy( )
	{
		for ( INetworkProvider::NetworkProviderList::iterator i = m_networkProviders.begin( ); i != m_networkProviders.end( ); ++i )
		{
			( *i )->Message( m_attributes[ System::Attributes::Name ].As< std::string >( ), System::Messages::Entity::DestroyEntity, m_attributes );
		}
	}
}