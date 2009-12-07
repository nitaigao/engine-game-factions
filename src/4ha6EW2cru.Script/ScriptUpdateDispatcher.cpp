#include "precompiled.h"

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
		for( IScriptFunctionHandler::FunctionList::iterator i = m_updateHandlers.begin( ); i != m_updateHandlers.end( );)
		{
			if( ( *i )->IsMarkedForDeletion( ) )
			{
				delete ( *i );
				i = m_updateHandlers.erase( i );
			}
			else
			{
				( *i )->CallFunction( deltaMilliseconds );
				++i;
			}
		}
	}

	void ScriptUpdateDispatcher::UnRegisterUpdateHandler( IScriptFunctionHandler* handler )
	{
		for( IScriptFunctionHandler::FunctionList::iterator i = m_updateHandlers.begin( ); i != m_updateHandlers.end( ); ++i )
		{
			if ( ( *i )->Compare( handler ) )
			{
				( *i )->MarkForDeletion( );
			}
		}

		delete handler;
	}
}