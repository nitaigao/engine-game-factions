cmake_minimum_required(VERSION 2.8)

SET (PROJECT_BINARY_DIR ../../build/bin)
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}) 
SET (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}) 

INCLUDE_DIRECTORIES(.)

INCLUDE_DIRECTORIES(../../etc/vendor/tinyxml/include)
INCLUDE_DIRECTORIES(../../etc/vendor/physfs)
INCLUDE_DIRECTORIES(../../etc/vendor/tclap/include)

INCLUDE_DIRECTORIES(../../../ogre-prebuilt/include/OGRE)

INCLUDE_DIRECTORIES(../4ha6EW2cru.Application)

INCLUDE_DIRECTORIES(../../../boost-trunk)

FIND_LIBRARY(PHYSFS_LIBRARY physfs PATHS ../../etc/vendor/physfs)
FIND_LIBRARY(BOOST_LIBRARY boost_filesystem PATHS ../../../boost-trunk/stage/lib)

IF(APPLE)
   #SET(GUI_TYPE MACOSX_BUNDLE)
   FIND_LIBRARY(OGRE_LIBRARY Ogre)
   MARK_AS_ADVANCED (OGRE_LIBRARY)
   SET(EXTRA_LIBS ${OGRE_LIBRARY})
   SET(CMAKE_OSX_ARCHITECTURES i386)
ENDIF (APPLE)

ADD_LIBRARY(System SHARED 
  
  #Deps -- need to be split out
  #tinyxml
  ../../etc/vendor/tinyxml/include/ticpp.cpp 
  ../../etc/vendor/tinyxml/include/tinyxml.cpp 
  ../../etc/vendor/tinyxml/include/tinyxmlparser.cpp 
  ../../etc/vendor/tinyxml/include/tinyxmlerror.cpp
  
  precompiled.cpp 
  Export.hpp
  
  Configuration/Configuration.cpp
  Configuration/ConfigurationFile.cpp
  
  Logging/Logger.cpp
  Events/EventManager.cpp
  Service/ServiceManager.cpp
  System/SystemManager.cpp
  
  # this needs to go through a converter of somesort inside the relevent system files instead of being in the core library
  # FMOD, Havok (replace with bullet)
  Maths/MathMatrix.cpp
  
  Game/Game.cpp
  Game/GameFactory.cpp
  
  IO/ResourceCache.cpp
  IO/FileSystem.cpp
  
  State/World.cpp
  State/WorldEntity.cpp
  State/WorldEntityFactory.cpp

  Platform/ProgramOptions.cpp
  Platform/OSXPlatformManager.cpp
  Platform/OSXClock.cpp
  IO/OSXPathInformation.cpp
  
  State/Serilaization/AIComponentSerializer.cpp
  State/Serilaization/AnimationComponentSerializer.cpp
  State/Serilaization/AIComponentSerializer.cpp
  State/Serilaization/GeometryComponentSerializer.cpp
  State/Serilaization/GraphicsComponentSerializer.cpp
  State/Serilaization/InputComponentSerializer.cpp
  State/Serilaization/NetworkComponentSerializer.cpp
  State/Serilaization/PhysicsComponentSerializer.cpp
  State/Serilaization/ScriptComponentSerializer.cpp
  State/Serilaization/SoundComponentSerializer.cpp
  State/Serilaization/ComponentSerializerFactory.cpp
  State/Serilaization/XMLSerializer.cpp
  
)
  
TARGET_LINK_LIBRARIES(System ${EXTRA_LIBS} ${PHYSFS_LIBRARY} ${BOOST_LIBRARY})

ADD_EXECUTABLE (Application ../4ha6EW2cru.Application/main_osx.cpp) 
TARGET_LINK_LIBRARIES (Application ${PHYSFS_LIBRARY} System) 