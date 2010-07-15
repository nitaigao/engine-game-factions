/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkSystem.hpp
*  @date   2009/04/27
*/
#pragma once
#ifndef INETWORKSYSTEM_HPP
#define INETWORKSYSTEM_HPP

#include <System/ISystem.hpp>

#include <RakNetTypes.h>

namespace Network
{
  /*!
  *  The Sound System 
  */
  class GAMEAPI INetworkSystem : public ISystem
  {

  public:

    /*! Default Destructor
    *
    *  @return ()
    */
    virtual ~INetworkSystem( ) { };

  };
};

#endif
