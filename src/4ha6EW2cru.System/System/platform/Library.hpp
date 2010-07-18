/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ILibrary.hpp
*  @date   2010/07/17
*/
#pragma once
#ifndef ILIBRARY_H
#define ILIBRARY_H

#include "../../Export.hpp"

#include <dlfcn.h>
#include <string>

namespace Platform
{
  /*! 
   *  Represents a library that contains behavior
   */
  class GAMEAPI Library
  {

  public:
    
    Library(void* library)
      : m_library(library)
    {
      
    }
    
    /*! Retrieves a function exported from the Library
    *
    *  @return (T) The Function
    */
    template<class T>
    inline T Function(const std::string& function_name) 
    { 
      void* symbol = 0;
#     ifdef __APPLE__
      symbol = dlsym(m_library, function_name.c_str());
#     endif
      return reinterpret_cast<T>(symbol);
    };
    
  private:
    
    void* m_library;

  
  };
};
#endif
