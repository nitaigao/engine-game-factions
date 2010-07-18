CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET (PROJECT_BINARY_DIR ../../build/bin)
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}) 
SET (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}) 

INCLUDE_DIRECTORIES(.)

INCLUDE_DIRECTORIES(../../etc/vendor/tinyxml/include)
INCLUDE_DIRECTORIES(../../etc/vendor/physfs)
INCLUDE_DIRECTORIES(../../etc/vendor/tclap/include)
INCLUDE_DIRECTORIES(../../../ogre-prebuilt/include/OGRE)

INCLUDE_DIRECTORIES(../4ha6EW2cru.Application)
INCLUDE_DIRECTORIES(../4ha6EW2cru.System)

INCLUDE_DIRECTORIES(../../../boost-trunk)

FIND_LIBRARY(PHYSFS_LIBRARY physfs PATHS ../../etc/vendor/physfs)
FIND_LIBRARY(BOOST_LIBRARY boost_filesystem PATHS ../../../boost-trunk/stage/lib)

IF(APPLE)
   FIND_LIBRARY(OGRE_LIBRARY Ogre)
   MARK_AS_ADVANCED (OGRE_LIBRARY)
   SET(EXTRA_LIBS ${OGRE_LIBRARY})
   SET(CMAKE_OSX_ARCHITECTURES i386)
   
   FIND_LIBRARY(CF_LIBRARY CoreFoundation)
   MARK_AS_ADVANCED (CF_LIBRARY)
   SET(EXTRA_LIBS ${EXTRA_LIBS} ${CF_LIBRARY})
ENDIF (APPLE)

ADD_LIBRARY(OGRERenderer SHARED 
  
  precompiled.cpp
  SystemDefinition.cxx
  
  RendererSystem.cpp
  RendererSystemScene.cpp
  RendererSystemComponent.cpp
  CameraComponent.cpp
  FPSCameraComponent.cpp
  Line3d.cpp
  
  OgreMax/OgreMaxScene.cpp
  OgreMax/OgreMaxModel.cpp
  OgreMax/OgreMaxUtilities.cpp
  OgreMax/Version.cpp
  OgreMax/ProgressCalculator.cpp
  
  ../../etc/vendor/tinyxml/include/ticpp.cpp 
  ../../etc/vendor/tinyxml/include/tinyxml.cpp 
  ../../etc/vendor/tinyxml/include/tinyxmlparser.cpp 
  ../../etc/vendor/tinyxml/include/tinyxmlerror.cpp
)
  
TARGET_LINK_LIBRARIES(OGRERenderer ${EXTRA_LIBS} ${PHYSFS_LIBRARY} ${BOOST_LIBRARY})