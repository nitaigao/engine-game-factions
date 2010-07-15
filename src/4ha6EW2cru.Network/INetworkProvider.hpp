/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkProvider.hpp
*  @date   2009/08/17
*/
#pragma once
#ifndef INETWORKPROVIDER_HPP
#define INETWORKPROVIDER_HPP

#include <vector>
#include "System/SystemType.hpp"
#include "System/AnyType.hpp"
#include "System/ISystemComponent.hpp"

#include "Export.hpp"


namespace Network
{
  /*! 
   *  Receives and Transmits to Clients on the Network
   */
  class GAMEAPI INetworkProvider
  {

  public:

    typedef std::vector< INetworkProvider* > NetworkProviderList;

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~INetworkProvider( ) { };


    /*! Initializes the Network Interface
     *
     * @param[in] int maxConnections
     * @return ( void )
     */
    virtual void Initialize( int maxConnections ) = 0;


    /*! Updates the Network Provider
     *
     * @param[in] float deltaMilliseconds
     * @return ( void )
     */
    virtual void Update( float deltaMilliseconds ) = 0;


    /*! Distributes the message for the entity across the Network
     *
     * @param[in] ISystemComponent* subject
     * @param[in] const System::Message & message
     * @param[in] AnyType::AnyTypeMap parameters
     * @return ( void )
     */
    virtual void Message( ISystemComponent* subject, const System::MessageType& message, AnyType::AnyTypeMap parameters ) = 0;


    /*! Destroys the Provider
     *
     * @return ( void )
     */
    virtual void Destroy( ) = 0;
    
  };
};

#endif