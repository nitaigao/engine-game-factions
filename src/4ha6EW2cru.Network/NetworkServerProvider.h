/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkServerProvider.h
*  @date   2009/08/17
*/
#pragma once
#ifndef NETWORKSERVERPROVIDER_H
#define NETWORKSERVERPROVIDER_H


#include "INetworkProvider.hpp"
#include "INetworkServerController.hpp"
#include "INetworkServerEndpoint.hpp"
#include "INetworkServerProvider.hpp"
#include "INetworkInterface.hpp"

#include "Configuration/IConfiguration.hpp"

#include "Events/EventManager.h"
#include "Events/Event.h"

namespace Network
{
  /*! 
   *  Receives input from clients on the Network and Transmits Updates
   */
  class GAMEAPI NetworkServerProvider : public INetworkServerProvider
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    ~NetworkServerProvider( );


    /*! IoC Constructor
     *
     * @param[in] INetworkInterface * networkInterface
     * @return (  )
     */
    NetworkServerProvider( Configuration::IConfiguration* configuration, INetworkInterface* networkInterface, INetworkServerController* controller, INetworkServerEndpoint* endpoint )
      : m_networkInterface( networkInterface )
      , m_controller( controller )
      , m_configuration( configuration )
      , m_endpoint( endpoint )
    {

    }


    /*! Initializes the Network Interface
    *
    * @param[in] int maxConnections
    * @return ( void )
    */
    void Initialize( int maxConnections );


    /*! Updates the Network Provider
    *
    * @param[in] float deltaMilliseconds
    * @return ( void )
    */
    void Update( float deltaMilliseconds );


    /*! Distributes the message for the entity across the Network
    *
    * @param[in] ISystemComponent* subject
    * @param[in] const System::Message & message
    * @param[in] AnyType::AnyTypeMap parameters
    * @return ( void )
    */
    void Message( ISystemComponent* subject, const System::MessageType& message, AnyType::AnyTypeMap parameters );


    /*! Destroys the Provider
    *
    * @return ( void )
    */
    void Destroy( ) { };


    /*! Instructs all connected clients that the level has changed
     *
     * @param[in] const Events::IEvent * event
     * @return ( void )
     */
    void OnGameLevelChanged( const Events::IEvent* event );


  private:

    NetworkServerProvider( const NetworkServerProvider & copy ) { };
    NetworkServerProvider & operator = ( const NetworkServerProvider & copy ) { return *this; };

    INetworkInterface* m_networkInterface;
    INetworkServerController* m_controller;
    Configuration::IConfiguration* m_configuration;
    INetworkServerEndpoint* m_endpoint;
    
  };
};

#endif