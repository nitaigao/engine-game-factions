/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_LINEAR_CAST_VEHICLE_DEMO_H
#define HK_LINEAR_CAST_VEHICLE_DEMO_H

#include <Physics/Vehicle/Camera/hkp1dAngularFollowCam.h>

class hkpVehicleInstance;
class hkpReorientAction;
class hkRagdoll;

class LinearCastVehicleDemo : public hkDefaultPhysicsDemo
{
public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO);

	LinearCastVehicleDemo( hkDemoEnvironment* env, hkBool createWorld = true );

	virtual ~LinearCastVehicleDemo();

	virtual Result stepDemo(); 
	
	void createDodgeBoxes(hkUint16 num, hkVector4& halfExtents, hkVector4& startPos, hkVector4& diffPos);
	
	void createRagdollGrid( hkpWorld* world, int x_size, int y_size, hkReal xStep, hkReal yStep, hkArray<hkRagdoll*>& ragdollsOut);

public:
	hkpVehicleInstance* m_vehicle;

public:

	hkp1dAngularFollowCam m_camera;

	hkReal m_inputXPosition;
	hkReal m_inputYPosition;

	hkReferencedObject* m_track;

	// For use with calls to the displayHandler.
	int m_tag;

	hkArray<int> m_displayWheelId;

	// This action uprights the vehicle when it turns over. 	 
	hkpReorientAction* m_reorientAction;

	hkArray<hkRagdoll*>	m_ragdolls;
};

#endif // HK_LINEAR_CAST_VEHICLE_DEMO_H

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
