/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockService.hpp
*  @date   2009/09/02
*/
#pragma once
#ifndef MOCKSERVICE_HPP
#define MOCKSERVICE_HPP

#include <gmock/gmock.h>

#include "Service/IService.hpp"

namespace
{
  class MockService : public Services::IService
  {

  public:

  
    MOCK_CONST_METHOD0( GetType, System::Types::Type( ) );

    MOCK_METHOD2( ProcessMessage, AnyType::AnyTypeMap( const System::MessageType&, AnyType::AnyTypeMap ) );

    
  };
};

#endif