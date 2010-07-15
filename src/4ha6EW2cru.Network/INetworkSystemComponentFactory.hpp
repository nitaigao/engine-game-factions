/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkSystemComponentFactory.hpp
*  @date   2009/08/17
*/
#pragma once
#ifndef INETWORKSYSTEMCOMPONENTFACTORY_HPP
#define INETWORKSYSTEMCOMPONENTFACTORY_HPP

#include "INetworkSystemComponent.hpp"

namespace Network
{
  /*! 
   *  Creates Network System Components
   */
  class INetworkSystemComponentFactory
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~INetworkSystemComponentFactory() { };


    /*! Creates a Network System Component
     *
     * @param[in] const std::string & name
     * @return (INetworkSystemComponent*)
     */
    virtual INetworkSystemComponent* Create(const std::string& name) = 0;
    
  };
};

#endif