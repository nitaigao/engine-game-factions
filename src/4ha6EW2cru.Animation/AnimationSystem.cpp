#include "precompiled.h"

#include "AnimationSystem.h"

#include "AnimationSystemScene.h"

#include "Logging/Logger.h"
using namespace Logging;

namespace Animation
{
  void AnimationSystem::Initialize(Configuration::IConfiguration* configuration)
  {
    hkPoolMemory* memoryManager = new hkPoolMemory();
    m_threadMemory = new hkThreadMemory(memoryManager);
    hkBaseSystem::init(memoryManager, m_threadMemory, errorReportFunction);
    memoryManager->removeReference();

    int stackSize = 0x100000;
    m_stackBuffer = hkAllocate<char>(stackSize, HK_MEMORY_CLASS_BASE);
    hkThreadMemory::getInstance().setStackArea(m_stackBuffer, stackSize);
  }

  void AnimationSystem::errorReportFunction(const char* errorMessage, void* errorOutputObject)
  {
    Warn(errorMessage);
  }

  void AnimationSystem::Update(float deltaMilliseconds)
  {
    m_scene->Update(deltaMilliseconds);
  }

  void AnimationSystem::Release()
  {
    m_threadMemory->setStackArea(0, 0);
    hkDeallocate(m_stackBuffer);
    m_threadMemory->removeReference();

    hkBaseSystem::quit();
  }

  ISystemScene* AnimationSystem::CreateScene()
  {
    m_scene = new AnimationSystemScene(m_resourceCache);
    return m_scene;
  }
}