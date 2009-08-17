#include <gtest/gtest.h>
using namespace testing;

#include "NetworkServerController.h"
using namespace Network;

TEST( NetworkServerController, should_call_rpc_on_set_position )
{
	NetworkServerController controller;
	controller.SetPosition( "somename", Maths::MathVector3( ) );
}