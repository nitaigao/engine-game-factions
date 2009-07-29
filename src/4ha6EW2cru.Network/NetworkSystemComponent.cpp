#include "NetworkSystemComponent.h"

#include "NetworkSystemScene.h"

#include "Maths/MathVector3.hpp"
#include "Maths/MathQuaternion.hpp"
using namespace Maths;

namespace Network
{
	AnyType NetworkSystemComponent::Message( const System::Message& message, AnyType::AnyTypeMap parameters )
	{
		if ( message == System::Messages::SetPosition )
		{
			m_attributes[ System::Attributes::Position ] = parameters[ System::Attributes::Position ].As< MathVector3 >( );
		}

		if ( message == System::Messages::SetOrientation )
		{
			m_attributes[ System::Attributes::Orientation ] = parameters[ System::Attributes::Orientation ].As< MathQuaternion >( );
		}

		if ( message == System::Messages::Mouse_Moved )
		{
			m_attributes[ System::Parameters::DeltaX ] = parameters[ System::Parameters::DeltaX ].As< float >( );
		}

		INetworkSystemScene* networkScene = m_attributes[ System::Attributes::Parent ].As< NetworkSystemScene* >( );
		networkScene->GetSystem( )->PushMessage( message, m_attributes );
		
		return AnyType( );
	}

	void NetworkSystemComponent::MessageFromNetwork( const System::Message& message, AnyType::AnyTypeMap parameters )
	{
		this->PushMessage( message, parameters );
	}

	void NetworkSystemComponent::Initialize( )
	{
		INetworkSystemScene* networkScene = m_attributes[ System::Attributes::Parent ].As< NetworkSystemScene* >( );
		networkScene->GetSystem( )->PushMessage( System::Messages::Entity::CreateEntity, m_attributes );
	}

	void NetworkSystemComponent::Destroy( )
	{

	}
}