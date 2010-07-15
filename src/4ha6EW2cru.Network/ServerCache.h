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
#include "IServerCache.hpp"

#include "Export.hpp"

namespace Network
{
  /*! 
   *  A Cache of Available Servers for the Client
   */
  class ServerCache : public IServerCache
  {

  public:

    GAMEAPI ~ServerCache();

    ServerCache() { };


    GAMEAPI bool Exists(const std::string& systemAddress) const;
    GAMEAPI int GetCount() const;
    GAMEAPI void Add(const std::string& serverName, const std::string& mapName, int maxPlayers, int numPlayers, int ping, const std::string& address, unsigned int port);
    GAMEAPI IServerAdvertisement* Find(int index) const;
    GAMEAPI void Clear();



  private:

    ServerCache(const ServerCache & copy) { };
    ServerCache & operator = (const ServerCache & copy) { return *this; };


    IServerAdvertisement::ServerAdvertisementMap m_advertCache;
    static ServerCache* m_instance;
    
  };
};

#endif