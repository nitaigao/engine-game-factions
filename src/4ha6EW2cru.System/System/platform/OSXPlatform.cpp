#include "OSXPlatform.h"
#include "dlfcn.h"

#include <sstream>
#include <iostream>

namespace Platform
{
  Library* OSXPlatform::LoadLibrary(const std::string& path)
  {
    std::stringstream full_path;
    full_path << "lib" << path << ".dylib";
		
		std::cout << "Loading Library: " << full_path.str().c_str();
    
    void* library = dlopen(full_path.str().c_str(), RTLD_LAZY);
    return new Library(library);
  }
}