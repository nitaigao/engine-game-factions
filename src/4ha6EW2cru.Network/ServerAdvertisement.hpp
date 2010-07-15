/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ServerAdvertisement.hpp
*  @date   2009/08/06
*/
#pragma once
#ifndef SERVERADVERTISEMENT_HPP
#define SERVERADVERTISEMENT_HPP

#include "IServerAdvertisement.hpp"

namespace Network
{
  /*! 
   *  An Object that contains information passed from a Server Advertisement
   */
  class ServerAdvertisement : public IServerAdvertisement
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    ~ServerAdvertisement() { };


    /*! Default Constructor
    *
    * @return ()
    */
    ServerAdvertisement(const std::string& serverName, const std::string& levelName, int maxPlayers, int playerCount, int ping, const std::string& serverAddress, int serverPort)
      : m_serverName(serverName)
      , m_levelName(levelName)
      , m_maxPlayers(maxPlayers)
      , m_playerCount(playerCount)
      , m_ping(ping)
      , m_serverAddress(serverAddress)
      , m_serverPort(serverPort)
    {

    }


    /*! Returns the name of the server
    *
    * @return (std::string)
    */
    inline std::string GetServerName() { return m_serverName; };


    /*! Returns the name of the level running on the server
    *
    * @return (std::string)
    */
    inline std::string GetLevelName() { return m_levelName; };

    /*! Returns the maximum number of players that are allowed to connect
    *
    * @return (int)
    */
    inline int GetMaxPlayers() { return m_maxPlayers; };


    /*! Returns the number of players currently connected to the server
    *
    * @return (int)
    */
    inline int GetPlayerCount() { return m_playerCount; };


    /*! Returns the round trip time from the client to the server
    *
    * @return (int)
    */
    inline int GetPing() { return m_ping; };


    /*! Returns the serverAddress of the server including the port
    *
    * @return (int)
    */
    inline std::string GetServerAddress() { return m_serverAddress; };


    /*! Returns the serverAddress of the server including the port
    *
    * @return (int)
    */
    inline int GetServerPort() { return m_serverPort; };

  private:

    ServerAdvertisement() { };
    ServerAdvertisement(const ServerAdvertisement & copy) { };
    ServerAdvertisement & operator = (const ServerAdvertisement & copy) { return *this; };

    std::string m_serverName;
    std::string m_levelName;
    int m_maxPlayers;
    int m_playerCount;
    int m_ping;
    std::string m_serverAddress;
    int m_serverPort;
    
  };
};

#endif