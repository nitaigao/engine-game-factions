/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ISoundSystem.hpp
*  @date   2009/04/27
*/
#pragma once
#ifndef ISOUNDSYSTEM_HPP
#define ISOUNDSYSTEM_HPP

#include "System/ISystem.hpp"

#include <fmod.hpp>
#include <fmod_event.hpp>

namespace Sound
{
  /*!
   *  The Sound System 
   */
  class GAMEAPI ISoundSystem : public ISystem
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~ISoundSystem() { };


    /*! Opens a sound file for FMOD
     *
     * @param[in] const char * name
     * @param[in] int unicode
     * @param[in] unsigned int * filesize
     * @param[in] void * * handle
     * @param[in] void * * userdata
     * @return (bool)
     */
    virtual bool FileOpen(const char* name, int unicode, unsigned int* filesize, void** handle, void** userdata) = 0;

  };
};

#endif
