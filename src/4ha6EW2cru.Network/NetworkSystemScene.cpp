#include "NetworkSystemScene.h"

#include "NetworkSystemComponent.h"
#include "NetworkSystemComponentFactory.hpp"

namespace Network
{
	NetworkSystemScene::~NetworkSystemScene()
	{
		for( INetworkProvider::NetworkProviderList::iterator i = m_networkProviders.begin( ); i != m_networkProviders.end( ); ++i )
		{
			delete ( *i );
		}

		delete m_componentFactory;
	}

	NetworkSystemScene::NetworkSystemScene( )
		: m_componentFactory( new NetworkSystemComponentFactory( ) )
	{

	}

	ISystemComponent* NetworkSystemScene::CreateComponent( const std::string& name, const std::string& type )
	{
		INetworkSystemComponent* component = m_componentFactory->Create( name );
		component->SetAttribute( System::Attributes::Parent, this );

		for( INetworkProvider::NetworkProviderList::iterator i = m_networkProviders.begin( ); i != m_networkProviders.end( ); ++i )
		{
			component->AddProvider( ( *i ) );
		}

		m_components.insert( std::make_pair( name, component ) );

		return component;
	}

	void NetworkSystemScene::DestroyComponent( ISystemComponent* component )
	{
		m_components.erase( component->GetAttributes( )[ System::Attributes::Name ].As< std::string >( ) );
		component->Destroy( );
		delete component;
		component = 0;
	}

	void NetworkSystemScene::MessageComponent( const std::string& componentId, const System::Message& message, AnyType::AnyTypeMap parameters )
	{
		static_cast< INetworkSystemComponent* >( m_components[ componentId ] )->MessageFromNetwork( message, parameters );
	}

	void NetworkSystemScene::Update( float deltaMilliseconds )
	{
		for( INetworkProvider::NetworkProviderList::iterator i = m_networkProviders.begin( ); i != m_networkProviders.end( ); ++i )
		{
			( *i )->Update( deltaMilliseconds );
		}
	}

	void NetworkSystemScene::Destroy()
	{
		for( INetworkProvider::NetworkProviderList::iterator i = m_networkProviders.begin( ); i != m_networkProviders.end( ); ++i )
		{
			( *i )->Destroy( );
		}
	}
}