#include "WorldEntity.h"

using namespace IO;

namespace State
{
	void WorldEntity::AddComponent( ISystemComponent* component )
	{
		m_components.push_back( component );

		component->AddObserver( this );

		//TODO: Change this to message
		component->Observe( 0, System::Messages::AddedToComponent, AnyType::AnyTypeMap( ) );
	}

	AnyType WorldEntity::Observe( const ISubject* subject, const System::MessageType& message, AnyType::AnyTypeMap parameters )
	{
		AnyType::AnyTypeKeyMap results;

		for( ISystemComponent::SystemComponentList::const_iterator i = m_components.begin( ); i != m_components.end( ); ++i )
		{
			if ( ( *i ) != subject )
			{
				AnyType result = ( *i )->Observe( subject, message, parameters );
				System::Types::Type systemType = ( *i )->GetAttributes( )[ System::Attributes::SystemType ].As< System::Types::Type >( );
				results.insert( std::make_pair( systemType, result ) );
			}
		}

		for ( ObserverMap::iterator i = m_observers.begin( ); i != m_observers.end( ); ++i )
		{
			if ( ( *i ).first == System::Messages::All_Messages || ( *i ).first == message )
			{
				( *i ).second->Observe( subject, message, parameters );
			}
		}

		return results;
	}

	void WorldEntity::Initialize( )
	{
		//TODO: Change this to message
		this->Observe( 0, System::Messages::PreInitialize, AnyType::AnyTypeMap( ) );

		for( ISystemComponent::SystemComponentList::const_iterator i = m_components.begin( ); i != m_components.end( ); ++i )
		{
			( *i )->Initialize( ); 
		}

		//TODO: Change this to message
		this->Observe( 0, System::Messages::PostInitialize, AnyType::AnyTypeMap( ) );
	}


	void WorldEntity::SetAttribute( const System::Attribute& attribute, const AnyType& value )
	{
		m_attributes[ attribute ] = value;

		for( ISystemComponent::SystemComponentList::const_iterator i = m_components.begin( ); i != m_components.end( ); ++i )
		{
			( *i )->SetAttribute( attribute, value );
		}
	}

	void WorldEntity::Serialize( IStream* stream )
	{
		stream->Write( m_name );

		AnyType::AnyTypeMap::iterator entityType = m_attributes.find( System::Attributes::EntityType );

		if ( entityType != m_attributes.end( ) )
		{
			stream->Write( 1 );
			stream->Write( ( *entityType ).second.As< std::string >( ) );
		}
		else
		{
			stream->Write( 0 );
		}
	}
}