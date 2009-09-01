/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SerializedManager_H
#define HK_SerializedManager_H

#include <Demos/DemoCommon/DemoFramework/hkDefaultPhysicsDemo.h>
#include <Common/Serialize/Packfile/hkPackfileReader.h>

#include <Physics/Vehicle/Camera/hkp1dAngularFollowCam.h>

#include <Physics/Vehicle/Manager/hkpVehicleManager.h>

class hkpVehicleInstance;
class hkpRigidBody;

//
// This simple game uses the minimum amount of code necessary to add a vehicle
// action to a rigid body (including a camera and steering controller).
//
//
class SerializedManager : public hkDefaultPhysicsDemo
{
	public:
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO);

		SerializedManager(hkDemoEnvironment* env);
		virtual ~SerializedManager();

		virtual Result stepDemo(); 

	protected:
		virtual void saveVehicle( bool binaryFormat = false );
		virtual void loadVehicle();

		hkpVehicleInstance* getVehicle();

	public:
		hkp1dAngularFollowCam	m_camera;
		
		hkReal m_inputXPosition;
		hkReal m_inputYPosition;

		// The filepath to the demo resource.
		hkString m_path;
		
		hkpVehicleManager* m_vehicleManager;

		// When we deserialize the manager, it's memory will be managed by the resource, so we
		// need to keep it around. It's set to HK_NULL prior to loading a vehicle manager.
		hkResource* m_resource;
};

#endif // HK_SerializedManager_H

/*
* Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20090704)
* 
* Confidential Information of Havok.  (C) Copyright 1999-2009
* Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
* Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
* rights, and intellectual property rights in the Havok software remain in
* Havok and/or its suppliers.
* 
* Use of this software for evaluation purposes is subject to and indicates
* acceptance of the End User licence Agreement for this product. A copy of
* the license is included with this software and is also available at www.havok.com/tryhavok.
* 
*/
