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

#include <Physics/Collide/Dispatch/hkpAgentRegisterUtil.h>	

#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastInput.h>			
#include <Physics/Collide/Query/Collector/RayCollector/hkpAllRayHitCollector.h>
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>			

#include <Physics/Dynamics/World/hkpWorld.h>								
#include <Physics/Dynamics/Entity/hkpRigidBody.h>							

#define HK_CLASSES_FILE <Common/Serialize/Classlist/hkClasses.h>
#include <Common/Serialize/Util/hkBuiltinTypeRegistry.cxx>
#define HK_COMPAT_FILE <Common/Compat/hkCompatVersions.h>
#include <Common/Compat/hkCompat_All.cxx> 

#include <Common/Base/System/Io/IStream/hkIStream.h>
#include <Common/Serialize/Packfile/Binary/hkBinaryPackfileReader.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Utilities/Serialize/hkpPhysicsData.h>
#include <Common/Serialize/Version/hkVersionUtil.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>