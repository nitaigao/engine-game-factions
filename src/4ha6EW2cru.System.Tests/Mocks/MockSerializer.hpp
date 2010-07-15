/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockSerializer.hpp
*  @date   2009/08/13
*/
#pragma once
#ifndef MOCKSERIALIZER_HPP
#define MOCKSERIALIZER_HPP

#include "State/Serilaization/IWorldLoader.hpp"

namespace 
{
  /*! 
   *  
   */
  class MockSerializer : public Serialization::IWorldSerializer
  {

  public:
    
    MOCK_METHOD2(DeSerializeLevel, void (IWorld*, const std::string&));
    MOCK_METHOD2(DeSerializeEntity, void(IWorldEntity*, const std::string&));
    MOCK_METHOD1(Update, void(float));
    
  };
};

#endif