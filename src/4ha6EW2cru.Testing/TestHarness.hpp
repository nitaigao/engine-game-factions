/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   TestHarness.hpp
*  @date   2009/08/20
*/
#pragma once
#ifndef TESTHARNESS_HPP
#define TESTHARNESS_HPP

namespace Testing
{
  /*! 
   *  A Test Harness for Unit Tests
   */
  template< class T >
  class TestHarness : public testing::Test
  {

  public:

    virtual void SetUp( )
    {
      EstablishContext( );
      m_subject = CreateSubject( );
    }

    virtual void TearDown( )
    {
      DestroyContext( );
      delete m_subject;
    }

  protected:

    virtual void EstablishContext( ) { };
    virtual void DestroyContext( ) { };
    virtual T* CreateSubject( ) = 0;

    T* m_subject;

  };

};

#endif