#include "precompiled.h"

#include "UXFacadeManager.h"

using namespace Script;

namespace UX
{
  void UXFacadeManager::Initialize( ISystemComponent* scriptComponent )
  {
    IScriptFacade* systemFacade = m_facadeFactory->CreateScriptFacade( IScriptFacade::SYSTEM, scriptComponent, m_state );
    m_facades.push_back( systemFacade );
    systemFacade->Initialize( );

    IScriptFacade* inputFacade = m_facadeFactory->CreateScriptFacade( IScriptFacade::INPUT, scriptComponent, m_state );
    m_facades.push_back( inputFacade );
    inputFacade->Initialize( );

    IScriptFacade* instFacade = m_facadeFactory->CreateScriptFacade( IScriptFacade::INSTRUMENTATION, scriptComponent, m_state );
    m_facades.push_back( instFacade );
    instFacade->Initialize( );

    IScriptFacade* netFacade = m_facadeFactory->CreateScriptFacade( IScriptFacade::NETWORK, scriptComponent, m_state );
    m_facades.push_back( netFacade );
    netFacade->Initialize( );
  }

  void UXFacadeManager::Destroy()
  {
    for( IScriptFacade::ScriptFacadeList::iterator i = m_facades.begin( ); i != m_facades.end( ); )
    {
      delete ( *i );
      i = m_facades.erase( i );
    }
  }
}