#include "Platform.h"

#include "OSXPlatform.h"

namespace Platform
{
  IPlatform* Local()
  {
    return new OSXPlatform();
  }
}