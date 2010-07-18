#include "precompiled.h"
#include "OSXPlatformManager.h"

#include "../Events/Event.h"

#include "/System/Library/Frameworks/CoreFoundation.framework/Headers/CoreFoundation.h"

namespace Platform
{
  OSXPlatformManager::~OSXPlatformManager()
  {
    if (0 != m_pathInformation)
    {
      delete m_pathInformation;
      m_pathInformation = 0;
    }
  }

  void OSXPlatformManager::Initialize()
  {
    m_pathInformation->Initialize();
  }

  void OSXPlatformManager::CreateInteractiveWindow(const std::string& title, int width, int height, bool fullScreen)
  {
    
  }

  void OSXPlatformManager::CreateConsoleWindow()
  {
    
  }

  void OSXPlatformManager::OutputToConsole(const std::string& message)
  {
    
  }

  void OSXPlatformManager::Update(float deltaMilliseconds)
  {
    while(CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.003, TRUE) == kCFRunLoopRunHandledSource);
  }

  void OSXPlatformManager::CloseWindow()
  {

  }

  size_t OSXPlatformManager::GetWindowId() const
  {
    return 0;
  }

  void OSXPlatformManager::OutputDebugMessage(const std::string& message)
  {

  }

  std::string OSXPlatformManager::GenUUID() const
  {
    return "";
  }
}