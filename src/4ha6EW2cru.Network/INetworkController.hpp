/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkController.hpp
*  @date   2009/08/19
*/
#pragma once
#ifndef INETWORKCONTROLLER_HPP
#define INETWORKCONTROLLER_HPP

#include "Export.hpp"

#include "Logging/Logger.h"
using namespace Logging;

namespace Network
{
  /*! 
   *  Sends information across the Network
   */
  class GAMEAPI INetworkController
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~INetworkController() { };


    /*! Initializes the Controller
    *
    * @return (void)
    */
    virtual void Initialize() = 0;


    /*! Updates the internal state of the controller and processes the send queue at the send interval
     *
     * @param[in] float deltaMilliseconds
     * @return (void)
     */
    virtual void Update(float deltaMilliseconds) = 0;
    
  };
};

#endif