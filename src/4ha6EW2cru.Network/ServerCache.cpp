#include "ServerCache.h"

#include <sstream>

namespace Network
{
	ServerCache* ServerCache::m_instance = 0;

	void ServerCache::Initialize()
	{
		ServerCache::m_instance = new ServerCache( );
	}

	ServerCache* ServerCache::Get()
	{
		return ServerCache::m_instance;
	}

	void ServerCache::Destroy()
	{
		ServerCache::m_instance->Clear( );
		delete ServerCache::m_instance;
	}

	bool ServerCache::Exists( const std::string& systemAddress ) const
	{
		std::stringstream serverName;
		serverName << systemAddress;

		return ( m_advertCache.find( serverName.str( ) ) != m_advertCache.end( ) );
	}

	int ServerCache::GetCount() const
	{
		return m_advertCache.size( );
	}

	void ServerCache::Add( const std::string& systemAddress, IServerAdvertisement* serverAdvertisement )
	{
		std::stringstream serverName;
		serverName << systemAddress;
		m_advertCache[ serverName.str( ) ] = serverAdvertisement;
	}

	IServerAdvertisement* ServerCache::Find( int index ) const
	{
		int itIndex = 0;

		for ( IServerAdvertisement::ServerAdvertisementMap::const_iterator i = m_advertCache.begin( ); i != m_advertCache.end( ); ++i )
		{
			if ( itIndex == index )
			{
				return ( *i ).second;
			}

			itIndex++;
		}

		return 0;
	}

	void ServerCache::Clear( )
	{
		for( IServerAdvertisement::ServerAdvertisementMap::iterator i = m_advertCache.begin( ); i != m_advertCache.end( ); )
		{
			delete ( *i ).second;
			i = m_advertCache.erase( i );
		}
	}
}