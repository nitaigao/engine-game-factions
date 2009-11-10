#include "ScriptUpdateDispatcher.h"

namespace Script
{
	void ScriptUpdateDispatcher::Destroy()
	{
		for( IScriptFunctionHandler::FunctionList::iterator i = m_updateHandlers.begin( ); i != m_updateHandlers.end( ); ++i )
		{
			delete ( *i );
		}
	}

	void ScriptUpdateDispatcher::RegisterUpdateHandler( IScriptFunctionHandler* handler )
	{
		m_updateHandlers.push_back( handler );
	}

	void ScriptUpdateDispatcher::Update( float deltaMilliseconds )
	{
		for( IScriptFunctionHandler::FunctionList::iterator i = m_updateHandlers.begin( ); i != m_updateHandlers.end( ); ++i )
		{
			( *i )->CallFunction( deltaMilliseconds );
		}
	}

	void ScriptUpdateDispatcher::UnRegisterUpdateHandler( IScriptFunctionHandler* handler )
	{
		for( IScriptFunctionHandler::FunctionList::iterator i = m_updateHandlers.begin( ); i != m_updateHandlers.end( ); )
		{
			if ( ( *i )->Compare( handler ) )
			{
				delete ( *i );
				i = m_updateHandlers.erase( i );
			}
			else
			{
				++i;
			}
		}

		delete handler;
	}
}