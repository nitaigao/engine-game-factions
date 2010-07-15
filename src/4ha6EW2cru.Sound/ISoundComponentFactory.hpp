/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ISoundComponentFactory.hpp
*  @date   2009/08/26
*/
#pragma once
#ifndef ISOUNDCOMPONENTFACTORY_HPP
#define ISOUNDCOMPONENTFACTORY_HPP

#include "ISoundSystemComponent.hpp"

#include "Export.hpp"

namespace Sound
{
  /*! 
   *  Creates Sound Components
   */
  class GAMEAPI ISoundComponentFactory
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~ISoundComponentFactory() { };


    /*! Creates a SoundSystem Component
     *
     * @param[in] const std::string & name
     * @param[in] const std::string & type
     * @return (ISoundSystemComponent*)
     */
    virtual ISoundSystemComponent* CreateComponent(const std::string& name, const std::string& type) = 0;
    
  };
};

#endif