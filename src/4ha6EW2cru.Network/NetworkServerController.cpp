#include "NetworkServerController.h"

namespace Network
{
	NetworkServerController::~NetworkServerController()
	{
		delete m_rpc;
	}

	void NetworkServerController::Initialize( )
	{

	}

	void NetworkServerController::SetOrientation( const std::string& name, const Maths::MathQuaternion& orientation )
	{

	}

	void NetworkServerController::SetPosition( const std::string& name, const Maths::MathVector3& position )
	{

	}

	void NetworkServerController::AdvertiseSystem( const SystemAddress& clientAddress, const RakNetTime& clientTime )
	{

	}
}