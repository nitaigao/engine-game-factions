#include "EntityService.h"

#include "../IO/IStream.hpp";
using namespace IO;

namespace State
{
	AnyType::AnyTypeMap EntityService::Message( const System::Message& message, AnyType::AnyTypeMap parameters )
	{
		if( message == System::Messages::Entity::DeSerializeWorld )
		{
			m_world->DeSerialize( parameters[ System::Parameters::IO::Stream ].As< IStream* >( ) );
		}

		if( message == System::Messages::Entity::SerializeWorld )
		{
			m_world->Serialize( parameters[ System::Parameters::IO::Stream ].As< IStream* >( ) );
		}

		if ( message == System::Messages::Entity::CreateEntity )
		{
			m_world->CreateEntity( parameters[ System::Attributes::Name ].As< std::string >( ), parameters[ System::Attributes::FilePath ].As< std::string >( ) );
		}

		if ( message == System::Messages::Entity::DestroyEntity )
		{
			m_world->DestroyEntity( parameters[ System::Attributes::Name ].As< std::string >( ) );
		}

		return AnyType::AnyTypeMap( );
	}
}