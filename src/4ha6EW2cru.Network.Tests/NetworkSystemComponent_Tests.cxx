#include <gtest/gtest.h>
using namespace testing;

#include "NetworkSystemComponent.h"
using namespace Network;

#include "Mocks/MockNetworkSystemProvider.hpp"

#include "Maths/MathVector3.hpp"
using namespace Maths;

TEST( NetworkSystemComponent, should_forward_internal_messages_to_registered_providers )
{
	AnyType::AnyTypeMap parameters;
	parameters[ System::Attributes::Position ] = MathVector3::Forward( );

	std::string entityName = "hello";
	System::Message message = System::Messages::SetPosition;

	MockNetworkSystemProvider provider;
	EXPECT_CALL( provider, Message( entityName, message, A< AnyType::AnyTypeMap >( ) ) );

	NetworkSystemComponent component;
	component.SetAttribute( System::Attributes::Name, entityName );
	component.AddProvider( &provider );
	component.Message( message, parameters );
}