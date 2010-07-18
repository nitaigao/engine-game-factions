/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   OSXLibrary.h
*  @date   2010/07/17
*/
#pragma once
#ifndef OSXLIBRARY_H
#define OSXLIBRARY_H

#include "ILibrary.hpp"
#include <string>

#include <dlfcn.h>

namespace Platform
{
  /*! 
   *  Represents aa OSX Shared Library
   */
  class OSXLibrary : public ILibrary
  {

  public:
    
    OSXLibrary(void* library)
      : m_library(library)
    {
      
    }
    
    /*! Retrieves a function exported from the Library
    *
    *  @return (T) The Function
    */
    template<class T>
    inline T Function<T>(const std::string& function_name) 
    { 
//      void* symbol = dlsym(m_library, function_name.c_str())
//      return reinterpret_cast<T>(symbol);
      return NULL;
    };
    
  private:
    
    void* m_library;
  
  };
};
#endif
