/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IPlatform.hpp
*  @date   2010/07/17
*/
#pragma once
#ifndef IPLATFORM_H
#define IPLATFORM_H

#include "../../Export.hpp"

#include "Library.hpp"
#include <string>

namespace Platform
{
  /*! 
   *  Represents a Platform that the application can talk to (OSX/Linux/Windows/IPhone etc...)
   */
  class IPlatform
  {

  public:

    /*! Loads a Library from the specified local path on the file system
    *
    *  @param[in] const std::string & path
    *  @return (ILibrary*)
    */
    virtual Library* LoadLibrary(const std::string& path) = 0;
  
  };
};
#endif
