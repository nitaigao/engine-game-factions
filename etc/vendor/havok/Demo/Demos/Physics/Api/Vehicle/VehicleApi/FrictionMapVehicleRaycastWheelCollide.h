/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef FRICTION_MAP_VEHICLE_RAYCAST_COLLIDE_H
#define FRICTION_MAP_VEHICLE_RAYCAST_COLLIDE_H

#include <Physics/Vehicle/WheelCollide/RayCast/hkpVehicleRayCastWheelCollide.h>
#include <Physics/Vehicle/hkpVehicleInstance.h>
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>

#define VEHICLE_RAYCAST_ICY_FRICTION_PROPERTY 67341

	// This is the class which implements the calcSingleWheelGroundFriction, allowing you to override the
	// ground friction calculation for raycast vehicles. Here, as a very simple example, we overwrite the friction to be
	// 0.01 for all bodies (upon which we are driving) which have been tagged with a VEHICLE_RAYCAST_ICY_FRICTION_PROPERTY
	// user property, otherwise we leave the friction as it is.
	// In general of course, the friction value need not be constant over the body (or time), and any function can be used 
	// here, for example a lookup into your own full 2D 'friction map'.
	// Other ways to store/retrieve friction values would be via:
	//	hkpShape user data
	//	A 'float' hkpProperty stored with a the rigid body
	//	hkMeshMaterials for hkMeshShapes
	//
	
class FrictionMapVehicleRaycastWheelCollide : public hkpVehicleRayCastWheelCollide
{
		virtual void wheelCollideCallback( const hkpVehicleInstance* vehicle, hkUint8 wheelIndex, CollisionDetectionWheelOutput& cdInfo )
		{
			hkpRigidBody* rb = cdInfo.m_contactBody;
			if ( rb )
			{
				if ( rb->hasProperty(VEHICLE_RAYCAST_ICY_FRICTION_PROPERTY) )
				{
					cdInfo.m_contactFriction = 0.01f;
				} 
			}
		}

	// Serialization.

	public:
		// By adding HK_DECLARE_REFLECTION, we enable objects of this class to be serialized.
		// However, the class does need to be registered with the type registry. The following code can be used:
		// hkBuiltinTypeRegistry::getInstance().addType( &FrictionMapVehicleRaycastWheelCollideTypeInfo, &FrictionMapVehicleRaycastWheelCollideClass );
		HK_DECLARE_REFLECTION();

		FrictionMapVehicleRaycastWheelCollide () { }

		FrictionMapVehicleRaycastWheelCollide ( hkFinishLoadedObjectFlag f ) : hkpVehicleRayCastWheelCollide( f ) { }
};

#endif // FRICTION_MAP_VEHICLE_RAYCAST_COLLIDE_H

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
