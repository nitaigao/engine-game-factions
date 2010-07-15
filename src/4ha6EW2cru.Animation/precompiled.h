#define NOMINMAX

#include <windows.h>
#include <shellapi.h>
#include <mmsystem.h>
#include <crtdbg.h>

#include <string>
#include <map>
#include <vector>
#include <map>
#include <iostream>

#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/Memory/hkThreadMemory.h>
#include <Common/Base/Memory/Memory/Pool/hkPoolMemory.h>  

#define INCLUDE_HAVOK_ANIMATION_CLASSES
#define HK_CLASSES_FILE <Common/Serialize/Classlist/hkClasses.h>
#include <Common/Serialize/Util/hkBuiltinTypeRegistry.cxx>
#define HK_COMPAT_FILE <Common/Compat/hkCompatVersions.h>
#include <Common/Compat/hkCompat_All.cxx> 

#include <Common/Base/System/Io/IStream/hkIStream.h>

#include <Common/Serialize/Packfile/Binary/hkBinaryPackfileReader.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#include <Common/Serialize/Version/hkVersionUtil.h>

#include <Physics/Utilities/Serialize/hkpPhysicsData.h>

#include <Animation/Animation/hkaAnimation.h>
#include <Animation/Animation/hkaAnimationContainer.h>
#include <Animation/Animation/Playback/Control/Default/hkaDefaultAnimationControl.h>
#include <Animation/Animation/Rig/hkaPose.h>
#include <Animation/Animation/Deform/Skinning/Fpu/hkaFPUSkinningDeformer.h>
#include <Animation/Animation/Rig/hkaSkeletonUtils.h>
#include <Animation/Animation/Mapper/hkaSkeletonMapper.h>
#include <Animation/Animation/Mapper/hkaSkeletonMapperData.h>
#include <Animation/Animation/Mapper/hkaSkeletonMapperUtils.h>

#include <Animation/Animation/Ik/Ccd/hkaCcdIkSolver.h>
#include <Animation/Animation/Ik/TwoJoints/hkaTwoJointsIkSolver.h>

#include <Ogre.h>
#include <OgreTagpoint.h>