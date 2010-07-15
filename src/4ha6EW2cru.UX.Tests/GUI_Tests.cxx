#include <gtest/gtest.h>
using namespace testing;

#include "GUI.h"
using namespace UX;

#include <MyGUI.h>

class GUI_Tests : public TestHarness< GUI >
{

protected:

  void EstablishContext( )
  {

  }


  void DestroyContext( )
  {

  }

  GUI* CreateSubject( )
  {
    return new GUI( new MyGUI::Gui( ), 0 ); 
  }
};