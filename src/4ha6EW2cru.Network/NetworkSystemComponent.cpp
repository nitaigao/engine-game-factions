#include "NetworkSystemComponent.h"

#include "NetworkSystemScene.h"

#include "Maths/MathVector3.hpp"
#include "Maths/MathQuaternion.hpp"
using namespace Maths;

#include "Logging/Logger.h"
using namespace Logging;

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
		if ( message == System::Messages::SetPosition )
		{
			MathVector3 currentPosition = m_attributes[ System::Attributes::Position ].As< MathVector3 >( );
			MathVector3 targetPosition = parameters[ System::Attributes::Position ].As< MathVector3 >( );
			MathVector3 positionDifference = targetPosition - currentPosition;

			float distanceApart = positionDifference.Length( );
			
			if ( distanceApart < 4.0f && distanceApart > 0.1f )
			{
				MathVector3 interpolatedPosition = currentPosition.Interpolate( targetPosition, 0.1f );
				parameters[ System::Attributes::Position ] = interpolatedPosition;

				Debug( "Current Position", currentPosition.X, currentPosition.Y, currentPosition.Z );
				Debug( "Interp  Position", interpolatedPosition.X, interpolatedPosition.Y, interpolatedPosition.Z );
				Debug( "Target  Position", targetPosition.X, targetPosition.Y, targetPosition.Z );
			}
		}

		if ( message == System::Messages::SetOrientation )
		{
			MathQuaternion currentOrientation = m_attributes[ System::Attributes::Orientation ].As< MathQuaternion >( );
			
			float currentAngle;
			MathVector3 currentAxis;
			currentOrientation.ToAngleAxis( currentAngle, currentAxis );
			
			MathQuaternion targetOrientation = parameters[ System::Attributes::Orientation ].As< MathQuaternion >( );
			
			float targetAngle;
			MathVector3 targetAxis;
			targetOrientation.ToAngleAxis( targetAngle, targetAxis );

			float angleDifference = targetAngle - currentAngle;
			MathVector3 axisDifference = targetAxis - currentAxis;

			float angleDifferenceDegrees = angleDifference * ( 180.0f / MathUnits::PI( ) );

			if ( angleDifference < 10.0f && angleDifference > 0.0f )
			{
				float interpolatedAngle = currentAngle + ( angleDifference * 0.1f );
				MathVector3 interpolatedAxis = currentAxis + ( axisDifference * 0.1f );

				MathQuaternion interpolatedOrientation( interpolatedAxis, interpolatedAngle );
				parameters[ System::Attributes::Orientation ] = interpolatedOrientation;

				Debug( "Current Angle", currentAngle );
				Debug( "Interp  Angle", interpolatedAngle );
				Debug( "Target  Angle", targetAngle );
			}
		}

		this->PushMessage( message, parameters );
	}

	void NetworkSystemComponent::Initialize( )
	{
		INetworkSystemScene* networkScene = m_attributes[ System::Attributes::Parent ].As< NetworkSystemScene* >( );
		networkScene->GetSystem( )->PushMessage( System::Messages::Entity::CreateEntity, m_attributes );
	}

	void NetworkSystemComponent::Destroy( )
	{
		INetworkSystemScene* networkScene = m_attributes[ System::Attributes::Parent ].As< NetworkSystemScene* >( );
		networkScene->GetSystem( )->PushMessage( System::Messages::Entity::DestroyEntity, m_attributes );
	}
}