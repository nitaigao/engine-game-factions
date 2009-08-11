/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ServerCache.h
*  @date   2009/08/11
*/
#pragma once
#ifndef SERVERCACHE_H
#define SERVERCACHE_H

#include "ServerAdvertisement.hpp"

#include "Export.hpp"

namespace Network
{
	/*! 
	 *  A Cache of Available Servers for the Client
	 */
	class ServerCache
	{

	public:

		GAMEAPI static void Initialize( );
		GAMEAPI static ServerCache* Get( );
		GAMEAPI static void Destroy( );


		GAMEAPI bool Exists( const std::string& systemAddress ) const;
		GAMEAPI int GetCount( ) const;
		GAMEAPI void Add( const std::string& systemAddress, IServerAdvertisement* serverAdvertisement );
		GAMEAPI IServerAdvertisement* Find( int index ) const;
		GAMEAPI void Clear( );



	private:

		~ServerCache( ) { };
		ServerCache( ) { };
		ServerCache( const ServerCache & copy ) { };
		ServerCache & operator = ( const ServerCache & copy ) { return *this; };


		IServerAdvertisement::ServerAdvertisementMap m_advertCache;
		static ServerCache* m_instance;
		
	};
};

#endif