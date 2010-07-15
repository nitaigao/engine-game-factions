/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IServerCache.hpp
*  @date   2009/08/20
*/
#pragma once
#ifndef ISERVERCACHE_HPP
#define ISERVERCACHE_HPP

#include "IServerAdvertisement.hpp"

namespace Network
{
  /*! 
   *  A Cache of Server Advertisement
   */
  class IServerCache
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~IServerCache( ) { };


    virtual bool Exists( const std::string& systemAddress ) const = 0;


    virtual int GetCount( ) const = 0;


    virtual void Add( const std::string& serverName, const std::string& mapName, int maxPlayers, int numPlayers, int ping, const std::string& address, unsigned int port ) = 0;


    virtual IServerAdvertisement* Find( int index ) const = 0;


    virtual void Clear( ) = 0;
    
  };
};

#endif