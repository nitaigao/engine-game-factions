#include <gtest/gtest.h>
using namespace testing;

#include "TestHarness.hpp"
using namespace Testing;

#include "System/platform/OSXPlatform.h"
using namespace Platform;

namespace base_context
{
  class OSXPlatform_BaseContext : public TestHarness<OSXPlatform>
  {

  protected:

    virtual void EstablishContext()
    {

    }

    virtual void DestroyContext()
    {
    
    }

    OSXPlatform* CreateSubject()
    {
      return new OSXPlatform();
    }
  };
};

namespace when_we_load_one
{
  class if_the_library_exists : public base_context::OSXPlatform_BaseContext
  {
    
  public:
    
    Library* m_library;
  
  protected:
    
    void EstablishContext()
    {
      m_library = m_subject->LoadLibrary("Null");
    }
    
  };

  TEST_F(if_the_library_exists, it_should_return_a_library)
  {
    ASSERT_TRUE(m_library != 0);
  }  
}