#include <gtest/gtest.h>
using namespace testing;

#include "IO/ResourceCache.h"
using namespace Resources;

#include "../Mocks/MockFileSystem.hpp"

namespace base_context
{
  class ResourceCache_BaseContext : public TestHarness< ResourceCache >
  {

  protected:

    MockFileSystem* m_fileSystem;
    std::string m_filePath;

    virtual void EstablishContext( )
    {
      m_filePath = "some_file";
      m_fileSystem = new MockFileSystem( );
    }

    virtual void DestroyContext( )
    {
      delete m_fileSystem;
    }

    ResourceCache* CreateSubject( )
    {
      return new ResourceCache( m_fileSystem );; 
    }
  };
};

namespace in_general
{
  class when_a_resource_exists : public base_context::ResourceCache_BaseContext
  {
  
  protected:
  
    void Expecting( )
    {
      EXPECT_CALL( *m_fileSystem, FileExists( m_filePath, false ) ).WillOnce( Return( true ) );
    }
  
    void When( )
    {
      bool exists = m_subject->ResourceExists( m_filePath );
      ASSERT_TRUE( exists );
    }
    
  };

  TEST_F( when_a_resource_exists, then_the_resource_cache_should_report_this ) { }

  class when_a_resource_doesnt_exists : public base_context::ResourceCache_BaseContext
  {

  protected:

    void Expecting( )
    {
      EXPECT_CALL( *m_fileSystem, FileExists( m_filePath, false ) ).WillOnce( Return( false ) );
    }

    void When( )
    {
      bool exists = m_subject->ResourceExists( m_filePath );
      ASSERT_FALSE( exists );
    }

  };

  TEST_F( when_a_resource_doesnt_exists, then_the_resource_cache_should_report_this ) { }
}