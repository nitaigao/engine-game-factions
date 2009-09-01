/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <Demos/demos.h>

#include <Demos/Physics/Api/Vehicle/SerializedManager/SerializedManagerDemo.h>

#include <Graphics/Bridge/DisplayHandler/hkgDisplayHandler.h>

// 
// Includes for default vehicle implementation (including camera).
// 
#include <Physics/Vehicle/hkpVehicleInstance.h>
#include <Physics/Vehicle/WheelCollide/RayCast/hkpVehicleRayCastWheelCollide.h>
#include <Physics/Vehicle/DriverInput/Default/hkpVehicleDefaultAnalogDriverInput.h>

#include <Physics/Vehicle/Camera/hkp1dAngularFollowCam.h>

//
// Include for camera setup and user input handling.
//
#include <Demos/Physics/Api/Vehicle/VehicleApi/VehicleApiUtils.h>
#include <Demos/Physics/Api/Vehicle/VehicleApi/VehicleSetup.h>


//
// Includes for serialization.
//
#include <Physics/Dynamics/World/hkpPhysicsSystem.h>

#include <Physics/Utilities/Serialize/hkpPhysicsData.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>

// Used for loading the landscape
#include <Physics/Utilities/Serialize/hkpHavokSnapshot.h>

#include <Common/Base/Reflection/Registry/hkTypeInfoRegistry.h>
#include <Common/Base/Reflection/Registry/hkVtableClassRegistry.h>

#include <Common/Serialize/Util/hkSerializeUtil.h>

// As we serialize and deserialize objects of some classes, we need to use their ...Class classes.
extern const hkClass hkpVehicleManagerClass;
extern const hkTypeInfo FrictionMapVehicleRaycastWheelCollideTypeInfo;
extern const hkClass FrictionMapVehicleRaycastWheelCollideClass;

SerializedManager::SerializedManager(hkDemoEnvironment* env )
	:	hkDefaultPhysicsDemo(env),
		m_path("Resources/Physics/Api/Vehicle/SerializedManager/vehicle.xml"),
		m_resource( HK_NULL )
{
	// Register the FrictionMap...WheelCollide class, so it can be serialized.
	hkBuiltinTypeRegistry::getInstance().addType( &FrictionMapVehicleRaycastWheelCollideTypeInfo, &FrictionMapVehicleRaycastWheelCollideClass );

	// Initially "controller" is at (0,0), i.e. neither pointing left/right nor up/down.
	m_inputXPosition = 0.0f;
	m_inputYPosition = 0.0f;

	//
	// Setup the camera. Actually overwritten by step function, and when we first add the vehicle.
	//
	{
		hkVector4 from(0.0f, 0.0f, 10.0f);
		hkVector4 to(0.0f, 0.0f, 0.0f);
		hkVector4 up(0.0f, 1.0f, 0.0f);
		setupDefaultCameras( m_env, from, to, up );
	}

	//
	// Create the world.
	//
	{
		hkpWorldCinfo info;
		info.m_collisionTolerance = 0.1f;
		info.m_gravity.set(0.0f, -9.8f, 0.0f);
		info.setBroadPhaseWorldSize(850.0f) ;
		info.setupSolverInfo(hkpWorldCinfo::SOLVER_TYPE_4ITERS_MEDIUM);
		m_world = new hkpWorld( info );
		m_world->lock();

		// Register all agents.
		hkpAgentRegisterUtil::registerAllAgents(m_world->getCollisionDispatcher());
		// Graphics.
		setupGraphics();
	}

	//
	// Create the landscape
	//
	{
		hkVector4 landscapeHalfExtents( 100.0f, 1.0f, 100.0f );
		hkpBoxShape* landscapeShape = new hkpBoxShape( landscapeHalfExtents );
		hkpRigidBodyCinfo info;
		{
			info.m_shape = landscapeShape;
			info.m_position.setZero4();
			info.m_rotation.setIdentity();
			info.m_motionType = hkpMotion::MOTION_FIXED;
		}
		hkpRigidBody* landscape = new hkpRigidBody( info );
		m_world->addEntity( landscape );
		landscape->removeReference();
		landscapeShape->removeReference();
	}

	// Create a vehicle manager.
	m_vehicleManager = new hkpVehicleManager();

	//
	// Create some vehicles.
	//

	// Create vehicle's chassis shape.
	hkpConvexVerticesShape* chassisShape = VehicleApiUtils::createCarChassisShape(); 
	VehicleSetup setup;

	int chassisLayer = 1;

	for (int vehicleId = 0; vehicleId < 3; vehicleId++)
	{
		//
		// Create the chassis body.
		//
		hkpRigidBody* chassisRigidBody;
		{
			hkpRigidBodyCinfo chassisInfo;
			chassisInfo.m_mass = 750.0f;	
			chassisInfo.m_shape = chassisShape;
			chassisInfo.m_friction = 0.8f;
			chassisInfo.m_motionType = hkpMotion::MOTION_BOX_INERTIA;
			// Position chassis on the ground.
			chassisInfo.m_position.set( -40.0f, 4.f, vehicleId * 5.0f);
			// Inertia tensor will be set by VehicleSetup.
			chassisInfo.m_inertiaTensor.setIdentity();

			chassisInfo.m_centerOfMass.set( -0.037f, 0.143f, 0.0f);
			chassisInfo.m_collisionFilterInfo = hkpGroupFilter::calcFilterInfo( chassisLayer, 0 );

			chassisRigidBody = new hkpRigidBody(chassisInfo);
		}

		hkpVehicleInstance* vehicle = new hkpVehicleInstance( chassisRigidBody );

		setup.buildVehicle( m_world, *vehicle );
		vehicle->addToWorld( m_world );
		m_vehicleManager->addVehicle( vehicle );
		vehicle->removeReference();

		chassisRigidBody->removeReference();
	}
	chassisShape->removeReference();

	//
	// The display wheels could be created here.
	//
	
	VehicleApiUtils::createCamera( m_camera );

	m_world->unlock();
}


SerializedManager::~SerializedManager( )
{
	m_world->markForWrite();

	m_vehicleManager->removeFromWorld();
	m_vehicleManager->removeReference();
	if ( m_resource )
	{
		m_resource->removeReference();
	}

	m_world->unmarkForWrite();
}


//////////////////////////////////////////////////////////////////////////


void SerializedManager::loadVehicle()
{
	hkResource* resource = hkSerializeUtil::load( m_path.cString() );

	if ( resource )
	{
		hkpVehicleManager* manager = resource->getContents<hkpVehicleManager>();

		if ( manager )
		{
			m_vehicleManager->removeFromWorld();
			m_vehicleManager->removeReference();
			// Check whether a resource is already allocated.
			if ( m_resource )
			{
				m_resource->removeReference();
			}

			m_resource = resource;
			m_vehicleManager = manager;

			m_vehicleManager->addReference();
			m_vehicleManager->addToWorld( m_world );
		}
	}
	else
	{
		HK_WARN( 0xa887bcee, "Cannot open packfile." );
	}
}


void SerializedManager::saveVehicle( bool binaryFormat )
{
	hkOstream outfile( m_path.cString() );
	if ( outfile.isOk() )
	{
		hkSerializeUtil::savePackfile( m_vehicleManager, hkpVehicleManagerClass, outfile.getStreamWriter(), hkPackfileWriter::Options(), binaryFormat );
	}
	else
	{
		HK_WARN( 0xa887bcee, "Cannot open outfile to write packfile." );
	}
}


hkDemo::Result SerializedManager::stepDemo()
{
	//
	// Steer the vehicle from user input.
	//

	VehicleApiUtils::steer( m_env->m_gamePad,
		m_inputXPosition,
		m_inputYPosition,
		m_vehicleManager->getVehicle(0),
		m_timestep);

	//
	// Load and restore the vehicle.
	// Press 
	//   * button L1 ("delete" on PC) to save 
	//   * button R1 ("end" on PC) to reload
	// the vehicle state.
	//
	{
		const hkgPad* pad = m_env->m_gamePad;

		// Save the vehicle
		if ( pad->wasButtonPressed(HKG_PAD_BUTTON_L1) )
		{
			m_world->lock();
			// Save vehicle
			saveVehicle();
			m_world->unlock();
		}

		// Load the vehicle
		if ( pad->wasButtonPressed(HKG_PAD_BUTTON_R1) )
		{
			m_world->lock();
			// Load vehicle
			loadVehicle();

			m_world->unlock();
		}
	}

	m_world->markForWrite();
	m_vehicleManager->stepVehicles( m_world->m_dynamicsStepInfo.m_stepInfo );
	m_world->unmarkForWrite();

	//
	// Step the world.
	//
	{
		hkDefaultPhysicsDemo::stepDemo();
	}

	//
	// Synchronize the display wheels, update the tyremarks display, update the RPM and
	// gear display (not done here).
	//
	VehicleApiUtils::updateCamera( m_env, *m_vehicleManager->getVehicle(0).getChassis(), m_timestep, m_camera);

	return DEMO_OK;
}


#if defined(HK_COMPILER_MWERKS)
#	pragma force_active on
#	pragma fullpath_file on
#endif


static const char helpString[] =	\
"This is a bare-bones demo which shows how a vehicle manager can be serialized. (The vehicles don't even have wheels!).\n" \
"To save the vehicle manager, press \232. To reload, press \233.\n" \
"Controls: " \
"\224/\225 - accelerate / brake " \
"\226/\227 - steer " \
"\221 - handbrake";
 
HK_DECLARE_DEMO(SerializedManager, HK_DEMO_TYPE_PHYSICS | HK_DEMO_TYPE_SERIALIZE, "Serialized vehicle manager.", helpString);

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
