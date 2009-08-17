#include <gtest/gtest.h>
using namespace testing;

#include "NetworkServerProvider.h"
using namespace Network;

#include "Maths/MathVector3.hpp"
using namespace Maths;

#include "System/AnyType.hpp"

#include "Mocks/MockNetworkServerController.hpp"

TEST( NetworkServerProvider, should_handle_set_position_messages )
{
	std::string entityName = "test";
	MathVector3 position = MathVector3::Forward( );

	MockNetworkServerController* controller = new MockNetworkServerController( );
	EXPECT_CALL( *controller, SetPosition( entityName, position ) );

	AnyType::AnyTypeMap parameters;
	parameters[ System::Attributes::Position ] = position;

	NetworkServerProvider provider( controller );
	provider.Message( entityName, System::Messages::SetPosition, parameters );

	delete controller;
}