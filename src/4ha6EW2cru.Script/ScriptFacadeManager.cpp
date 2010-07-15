#include "precompiled.h"

#include "ScriptFacadeManager.h"

namespace Script
{
  void ScriptFacadeManager::Initialize(ISystemComponent* scriptComponent)
  {
    for(int i = 0; i < IScriptFacade::FACADETYPE_MAX; i++)
    {
      IScriptFacade* facade = m_facadeFactory->CreateScriptFacade(static_cast< IScriptFacade::FacadeType >(i), scriptComponent, m_state);
      m_facades.push_back(facade);
      facade->Initialize();
    }
  }

  void ScriptFacadeManager::Destroy()
  {
    for(IScriptFacade::ScriptFacadeList::iterator i = m_facades.begin(); i != m_facades.end();)
    {
      delete (*i);
      i = m_facades.erase(i);
    }
  }
}