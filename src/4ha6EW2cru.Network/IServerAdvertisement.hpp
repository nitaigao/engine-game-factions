/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IServerAdvertisement.h
*  @date   2009/08/06
*/
#pragma once
#ifndef ISERVERADVERTISEMENT_HPP
#define ISERVERADVERTISEMENT_HPP

#include <deque>
#include <map>

namespace Network
{
  /*! 
   *  An Object that contains information passed from a Server Advertisement
   */
  class IServerAdvertisement
  {

  public:

    typedef std::deque< IServerAdvertisement* > ServerAdvertisementList;
    typedef std::map< std::string, IServerAdvertisement* > ServerAdvertisementMap;

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~IServerAdvertisement( ) { };


    /*! Returns the name of the server
    *
    * @return ( std::string )
    */
    virtual std::string GetServerName( ) = 0;
    

    /*! Returns the name of the level running on the server
    *
    * @return ( std::string )
    */
    virtual std::string GetLevelName( ) = 0;


    /*! Returns the maximum number of players that are allowed to connect
    *
    * @return ( int )
    */
    virtual int GetMaxPlayers( ) = 0;


    /*! Returns the number of players currently connected to the server
    *
    * @return ( int )
    */
    virtual int GetPlayerCount( ) = 0;


    /*! Returns the round trip time from the client to the server
    *
    * @return ( int )
    */
    virtual int GetPing( ) = 0;


    /*! Returns the address of the server including the port
    *
    * @return ( std::string )
    */
    virtual std::string GetServerAddress( ) = 0;


    /*! Returns the serverAddress of the server including the port
    *
    * @return ( int )
    */
    virtual int GetServerPort( ) = 0;
  };
};

#endif