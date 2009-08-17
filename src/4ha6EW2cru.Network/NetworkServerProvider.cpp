#include "NetworkServerProvider.h"

#include "NetworkInterface.h"

#include "Maths/MathVector3.hpp"
using namespace Maths;

namespace Network
{
	NetworkServerProvider::NetworkServerProvider( )
		//: m_networkInterface( new NetworkInterface( ) )
	{

	}

	NetworkServerProvider::~NetworkServerProvider( )
	{
		//delete m_networkInterface;
	}

	void NetworkServerProvider::Initialize( unsigned int port, int maxPlayers )
	{
		//m_networkInterface->Initialize( port, maxPlayers ); 
	}

	void NetworkServerProvider::Message( const std::string& entityName, const System::Message& message, AnyType::AnyTypeMap parameters )
	{
		if ( message == System::Messages::SetPosition )
		{
			m_controller->SetPosition( entityName, parameters[ System::Attributes::Position ].As< MathVector3 >( ) );
		}

		if ( message == System::Messages::SetOrientation )
		{
			//m_attributes[ System::Attributes::Orientation ] = parameters[ System::Attributes::Orientation ].As< MathQuaternion >( );
		}

		if ( message == System::Messages::Mouse_Moved )
		{
			//m_attributes[ System::Parameters::DeltaX ] = parameters[ System::Parameters::DeltaX ].As< float >( );
		}
	}
}