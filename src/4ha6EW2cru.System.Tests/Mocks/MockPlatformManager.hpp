/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockPlatformManager.hpp
*  @date   2009/11/24
*/
#pragma once
#ifndef MOCKPLATFORMMANAGER_HPP
#define MOCKPLATFORMMANAGER_HPP

#include <gmock/gmock.h>

#include "Platform/IPlatformManager.h"

namespace
{
  class MockPlatformManager : public Platform::IPlatformManager
  {

  public:

    MOCK_METHOD0(Initialize, void());
    MOCK_METHOD4(CreateInteractiveWindow, void(const std::string&, int, int, bool));
    MOCK_METHOD0(CloseWindow, void());
    MOCK_METHOD0(CreateConsoleWindow, void());
    MOCK_METHOD1(OutputToConsole, void(const std::string&));
    MOCK_METHOD1(Update, void(float));
    MOCK_CONST_METHOD0(GetWindowId, size_t());
    MOCK_METHOD0(GetClock, Platform::IClock*());
    MOCK_METHOD1(OutputDebugMessage, void(const std::string&));
    MOCK_CONST_METHOD0(GetProgramOptions, AnyType::AnyTypeMap());
    MOCK_CONST_METHOD0(GenUUID, std::string());
    MOCK_METHOD0(GetPathInformation, IO::IPathInformation*());
    
  };
};

#endif