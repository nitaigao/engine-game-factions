/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkSystemComponentFactory.hpp
*  @date   2009/08/17
*/
#pragma once
#ifndef NETWORKSYSTEMCOMPONENTFACTORY_HPP
#define NETWORKSYSTEMCOMPONENTFACTORY_HPP

#include "INetworkSystemComponentFactory.hpp"

#include "NetworkSystemComponent.h"

namespace Network
{
  /*! 
   *  Creates Network System Components
   */
  class NetworkSystemComponentFactory : public INetworkSystemComponentFactory
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    ~NetworkSystemComponentFactory() { };


    /*! Default Constructor
    *
    * @return ()
    */
    NetworkSystemComponentFactory() { };


    /*! Creates a Network System Component
    *
    * @param[in] const std::string & name
    * @return (INetworkSystemComponent*)
    */
    INetworkSystemComponent* Create(const std::string& name)
    {
      INetworkSystemComponent* component = new NetworkSystemComponent();
      component->SetAttribute(System::Attributes::Name, name);
      component->SetAttribute(System::Attributes::SystemType, System::Types::NETWORK);
      return component;
    }

  private:

    NetworkSystemComponentFactory(const NetworkSystemComponentFactory & copy) { };
    NetworkSystemComponentFactory & operator = (const NetworkSystemComponentFactory & copy) { return *this; };
    
  };
};

#endif