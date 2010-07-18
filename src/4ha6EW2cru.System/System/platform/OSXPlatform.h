/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   OSXPlatform.h
*  @date   2010/07/17
*/
#pragma once
#ifndef OSXPLATFORM_H
#define OSXPLATFORM_H

#include "../../Export.hpp"

#include "IPlatform.hpp"
#include "Library.hpp"
#include <string>

namespace Platform
{
  /*! 
   *  Represents a the OSX Platform
   */
  class OSXPlatform : public IPlatform
  {

  public:

    /*! Loads a Library from the specified local path on the file system
    *
    *  @param[in] const std::string & path
    *  @return (ILibrary*)
    */
    Library* LoadLibrary(const std::string& path);
  
  };
};
#endif
