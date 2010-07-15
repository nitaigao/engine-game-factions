/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkClientEndpoint.hpp
*  @date   2009/08/19
*/
#pragma once
#ifndef INETWORKCLIENTENDPOINT_HPP
#define INETWORKCLIENTENDPOINT_HPP

#include "INetworkEndpoint.hpp"

namespace Network
{
  /*! 
   *  Receives traffic from the Server
   */
  class GAMEAPI INetworkClientEndpoint : public INetworkEndpoint
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~INetworkClientEndpoint() { };


    /*! Stops the Endpoint from Receiving data
     *
     * @param[in] bool isPassive
     * @return (void)
     */
    virtual void SetPassive(bool isPassive) = 0;
    
  };
};

#endif