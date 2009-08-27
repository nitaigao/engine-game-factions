#include <gtest/gtest.h>
using namespace testing;

#include "LuaState.h"
using namespace Script;

using namespace luabind;

class LuaState_Tests : public TestHarness< LuaState >
{

protected:

	void EstablishContext( )
	{

	}


	void DestroyContext( )
	{

	}

	LuaState* CreateSubject( )
	{
		return new LuaState( ); 
	}
};

TEST_F( LuaState_Tests, should_initialize_and_destroy )
{
	m_subject->Initialize( );
	m_subject->Destroy( );
}

TEST_F( LuaState_Tests, should_register_type )
{
	m_subject->Initialize( );
	
	scope types = class_< std::string >( "string" );
	m_subject->RegisterTypes( types );

	m_subject->Destroy( );
}