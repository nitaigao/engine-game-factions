/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockInstrumentation.hpp
*  @date   2009/08/20
*/
#pragma once
#ifndef MOCKINSTRUMENTATION_HPP
#define MOCKINSTRUMENTATION_HPP

#include <gmock/gmock.h>

namespace
{
  class MockInstrumentation : public System::IInstrumentation
  {

  public:

    MOCK_CONST_METHOD0(GetFPS, int());
    MOCK_METHOD1(SetFPS, void(int));
    MOCK_METHOD1(GetRoundTime, float(const System::Queues::Queue&));
    MOCK_METHOD2(SetRoundTime, void(const System::Queues::Queue&, float));
    MOCK_METHOD1(SetLevelName, void(const std::string&));
    MOCK_CONST_METHOD0(GetLevelName, std::string());

  };
};

#endif