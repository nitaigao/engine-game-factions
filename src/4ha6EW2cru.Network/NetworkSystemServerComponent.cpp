#include "NetworkSystemServerComponent.h"

#include "Maths/MathVector3.hpp"
using namespace Maths;

namespace Network
{
	AnyType NetworkSystemServerComponent::Message( const System::Message& message, AnyType::AnyTypeMap parameters )
	{
		if ( message == System::Messages::SetPosition )
		{
			m_attributes[ System::Attributes::Position ] = parameters[ System::Attributes::Position ].As< MathVector3 >( );

			m_messageDispatcher->SetPosition( 
				m_attributes[ System::Attributes::Name ].As< std::string >( ), 
				m_attributes[ System::Attributes::Position ].As< MathVector3 >( ) 
				);
		}

		if ( message == System::Messages::SetOrientation )
		{
			m_attributes[ System::Attributes::Orientation ] = parameters[ System::Attributes::Orientation ].As< MathQuaternion >( );

			m_messageDispatcher->SetOrientation(
				m_attributes[ System::Attributes::Name ].As< std::string >( ),
				m_attributes[ System::Attributes::Orientation ].As< MathQuaternion >( )
				);
		}

		return AnyType( );
	}
}