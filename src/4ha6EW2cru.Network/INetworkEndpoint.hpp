/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkEndpoint.hpp
*  @date   2009/08/19
*/
#pragma once
#ifndef INETWORKENDPOINT_HPP
#define INETWORKENDPOINT_HPP

#include "Export.hpp"

namespace Network
{
  /*! 
   *  An Endpoint for receiving data from the network
   */
  class GAMEAPI INetworkEndpoint
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~INetworkEndpoint( ) { };


    /*! Initializes the Endpoint
     *
     * @return ( void )
     */
    virtual void Initialize( ) = 0;


    /*! Updates the Endpoint
     *
     * @param[in] float deltaMilliseconds
     * @return ( void )
     */
    virtual void Update( float deltaMilliseconds ) = 0;
    
  };
};

#endif