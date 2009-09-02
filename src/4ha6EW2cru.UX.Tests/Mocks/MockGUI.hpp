/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   Mock_GUI.hpp
*  @date   2009/09/02
*/
#pragma once
#ifndef MOCK_GUI_HPP
#define MOCK_GUI_HPP

#include <gmock/gmock.h>

#include "IGUI.hpp"

namespace
{
	class MockGUI : public IGUI
	{

	public:

		MOCK_METHOD1( Initialize, void( const std::string& ) );
		MOCK_METHOD0( Destroy, void( ) );
		MOCK_METHOD3( MouseMoved, void( int, int, int ) );
		MOCK_METHOD3( MousePressed, void( int, int, int ) );
		MOCK_METHOD3( MouseReleased, void( int, int, int ) );
		MOCK_METHOD1( KeyReleased, void( int ) );
		MOCK_METHOD1( KeyPressed, void( int ) );
		MOCK_CONST_METHOD0( GetViewWidth, int( ) );
		MOCK_CONST_METHOD0( GetViewHeight, int( ) );
		MOCK_CONST_METHOD1( FindWidget, MyGUI::WidgetPtr( const std::string& ) );
		MOCK_CONST_METHOD0( ShowMouse, void( ) );
		MOCK_CONST_METHOD0( HideMouse, void( ) );
		MOCK_CONST_METHOD0( WindowResized, void( ) );
		MOCK_METHOD1( LoadLayout, void( const std::string& ) );
		MOCK_METHOD1( Update, void( float ) );

	};
};

#endif