/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_MULTITHREADED_VEHICLE_RAYCAST_DEMO_H
#define HK_MULTITHREADED_VEHICLE_RAYCAST_DEMO_H

#include <Demos/DemoCommon/DemoFramework/hkDefaultPhysicsDemo.h> 
#include <Demos/DemoCommon/Utilities/VehicleDisplay/VehicleDisplayUtils.h>

#include <Common/Base/Thread/Semaphore/hkSemaphoreBusyWait.h>
#include <Physics/Vehicle/Manager/hkpVehicleCastBatchingManager.h>

class hkpVehicleInstance;
class hkpVehicleInstanceMultithreaded;
class hkp1dAngularFollowCam;
class hkDefaultAnalogDriverInput;
class hkpReorientAction;
class hkRagdoll;

///[Introduction]
/// A demo that shows how to use the Multithreaded Ray Cast Vehicle Kit to construct basic vehicles including
/// hkActions used to update the vehicles, and a simple controller to drive the first vehicle. The constructor
/// creates fifty basic four-wheeled vehicles and a MOPP landscape to drive on. stepDemo() creates ray cast
/// commands and processes all of them at once asynchronously. Then it updates the first vehicle based on user
/// input (steering, acceleration etc.), and updates the camera to follow the first vehicle.
/// [IMAGE Resources/Car.png]

class VehicleManagerDemo : public hkDefaultPhysicsDemo
{
	public:
		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DEMO );

		VehicleManagerDemo( hkDemoEnvironment* env, hkBool createWorld = true, int numWheels = 4, int numVehicles = 1 );

		virtual ~VehicleManagerDemo();

		void makeFakeInput();
		virtual Result stepDemo(); 

	protected:

		virtual void steer();

			// Set up hkpWorld
		void setUpWorld();

			// Build the landscape to drive on and add it to m_world.
		void buildLandscape();

		void createDisplayWheels( hkReal radius = 0.4f, hkReal thickness = 0.2f );

		void createDodgeBoxes( hkUint16 num, hkVector4& halfExtents, hkVector4& startPos, hkVector4& diffPos );

		static void createRagdollGrid( hkpWorld* world, int x_size, int y_size, hkReal xStep, hkReal yStep, hkArray<hkRagdoll*>&	ragdollsOut );

	public:

		// The number of wheels in each vehicle.
		int m_numWheels;
		int m_numVehicles;

		hkArray< VehicleDisplayUtils::VehicleDataAndDisplayInfo >	m_vehicles;

	public:
	
		hkp1dAngularFollowCam m_camera;
		hkBool m_followCarView;

		hkReal m_inputXPosition;
		hkReal m_inputYPosition;
		
		hkReferencedObject* m_track;

			// For use with calls to the displayHandler.
		int m_tag;

			// m_displayWheelId is for display reference only.
			// An hkObjectArray with one element for each vehicle. Each vehicle element in turn
			// is an hkArray with one element for each wheel.
		hkObjectArray< hkArray<int> > m_displayWheelId;

			// This action uprights the vehicle when it turns over. 	 
		hkpReorientAction* m_reorientAction;

		hkArray<hkRagdoll*>	m_ragdolls;

		// Below added for multithreading
	private:
		hkReal								m_time;

		// Depending on the variant, this will either be rayCastBatchingManager or a linearCastBatchingManager.
		hkpVehicleCastBatchingManager* m_vehicleManager;
};

#endif // HK_MULTITHREADED_VEHICLE_RAYCAST_DEMO_H

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
