/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkProviderOld.hpp
*  @date   2009/07/15
*/
#pragma once
#ifndef INETWORKPROVIDEROLD_HPP
#define INETWORKPROVIDEROLD_HPP

#include "Configuration/IConfiguration.hpp"
#include "System/SystemType.hpp"

#include <RakPeerInterface.h>

namespace Network
{
  /*! 
   *  A communication provider to the Network
   */
  class INetworkProviderOld
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~INetworkProviderOld() { };

    virtual void Initialize(Configuration::IConfiguration* configuration) = 0;

    virtual void Update(float deltaMilliseconds) = 0;

    virtual void Release() = 0;

    virtual AnyType::AnyTypeMap Message(const System::MessageType& message, AnyType::AnyTypeMap parameters) = 0;

    virtual void PushMessage(const System::MessageType& message, AnyType::AnyTypeMap parameters) = 0;

    virtual void PushMessage(const SystemAddress& address, const System::MessageType& message, AnyType::AnyTypeMap parameters) = 0;
    
  };
};

#endif
