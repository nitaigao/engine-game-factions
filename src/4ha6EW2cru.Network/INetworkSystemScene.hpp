/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkSystemScene.hpp
*  @date   2009/07/06
*/
#pragma once
#ifndef INETWORKSYSTEMSCENE_HPP
#define INETWORKSYSTEMSCENE_HPP

#include "System/ISystemScene.hpp"
#include "INetworkSystem.hpp"
#include "INetworkProvider.hpp"

namespace Network
{
  /*! 
   *  A Network System Scene
   */
  class GAMEAPI INetworkSystemScene : public ISystemScene
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~INetworkSystemScene( ) { };


    /*! Adds a Network provider to the Scene
     *
     * @param[in] INetworkProvider * provider
     * @return ( void )
     */
    virtual void AddNetworkProvider( INetworkProvider* provider ) = 0;


    /*! Messages a component within the Scene
    *
    * @param[in] const std::string componentId
    * @param[in] const System::MessageType & message
    * @param[in] AnyType::AnyTypeMap parameters
    * @return ( void )
    */
    virtual void MessageComponent( const std::string& componentId, const System::MessageType& message, AnyType::AnyTypeMap parameters ) = 0;
    
  };
};

#endif
