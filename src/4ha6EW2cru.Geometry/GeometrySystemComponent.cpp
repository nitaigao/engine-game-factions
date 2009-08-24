#include "GeometrySystemComponent.h"

using namespace Maths;

namespace Geometry
{
	void GeometrySystemComponent::Initialize()
	{
		
	}

	AnyType GeometrySystemComponent::Observe( const ISubject* subject, const System::MessageType& message, AnyType::AnyTypeMap parameters )
	{
		if ( message == System::Messages::SetPosition )
		{
			m_attributes[ System::Attributes::Position ] = parameters[ System::Attributes::Position ].As< MathVector3 >( );
		}

		if ( message == System::Messages::SetOrientation )
		{
			m_attributes[ System::Attributes::Orientation ] = parameters[ System::Attributes::Orientation ].As< MathQuaternion >( );
		}

		if( message == System::Messages::PostInitialize )
		{
			this->PushMessage( System::Messages::SetPosition, m_attributes );
			this->PushMessage( System::Messages::SetOrientation, m_attributes );
		}

		return AnyType( );
	}

	AnyType GeometrySystemComponent::PushMessage( const System::MessageType& message, AnyType::AnyTypeMap parameters )
	{
		for( ObserverList::iterator i = m_observers.begin( ); i != m_observers.end( ); ++i )
		{
			( *i )->Observe( this, System::Messages::SetPosition, m_attributes );
		}

		return AnyType( );
	}
};