/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>

#include <Demos/Physics/Api/Vehicle/VehicleManager/VehicleManagerDemo.h>
#include <Demos/Physics/Api/Vehicle/VehicleApi/VehicleSetup.h>
#include <Demos/Physics/Api/Vehicle/VehicleApi/VehicleApiUtils.h>

#include <Demos/DemoCommon/Utilities/GameUtils/Landscape/FlatLand.h>
#include <Demos/DemoCommon/Utilities/GameUtils/GameUtils.h>

#include <Physics/Dynamics/World/hkpPhysicsSystem.h>

#include <Physics/Vehicle/Camera/hkp1dAngularFollowCam.h>
#include <Physics/Vehicle/hkpVehicleInstance.h>

#include <Graphics/Bridge/DisplayHandler/hkgDisplayHandler.h>
#include <Graphics/Common/DisplayObject/hkgDisplayObject.h>
#include <Graphics/Common/Material/hkgMaterial.h>
#include <Graphics/Common/Window/hkgWindow.h>

#include <Common/Base/Types/Color/hkColor.h>
#include <Common/Visualize/Shape/hkDisplayGeometry.h>
#include <Common/Visualize/hkDebugDisplay.h>


// Need this to get user 'friction' property we will tag some bodies with.
#include <Demos/Physics/Api/Vehicle/VehicleApi/FrictionMapVehicleRaycastWheelCollide.h>

#include <Physics/Utilities/Actions/Reorient/hkpReorientAction.h>
#include <Physics/Utilities/Serialize/hkpPhysicsData.h>

// Need this for Multithreading Ray Casts
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>
#include <Physics/Collide/Query/Multithreaded/CollisionQuery/hkpCollisionQueryJobQueueUtils.h>
#include <Common/Base/Thread/Job/ThreadPool/Cpu/hkCpuJobThreadPool.h>

#include <Physics/Vehicle/Manager/RayCastBatchingManager/hkpVehicleRayCastBatchingManager.h>
#include <Physics/Vehicle/Manager/LinearCastBatchingManager/hkpVehicleLinearCastBatchingManager.h>

#include <Demos/Physics/Api/Vehicle/VehicleApi/LinearCastVehicleSetup.h>

#include <Physics/Collide/Query/Collector/PointCollector/hkpFixedBufferCdPointCollector.h>

#if defined HK_PLATFORM_PS3_PPU
#define NUM_SPUS 5
#else
#define NUM_SPUS 1
#endif


// Collision layers
enum {
	CHASSIS_LAYER = 1,
	RAGDOLL_LAYER,
	WHEEL_LAYER,
	GROUND_LAYER
};

struct MTVehicleRayCastDemoVariant
{
	enum DemoType
	{
		SINGLETHREADED_RAY_CAST,
		MULTITHREADED_RAY_CAST,
		SINGLETHREADED_LINEAR_CAST,
		MULTITHREADED_LINEAR_CAST
	};

	const char*	m_name;
	DemoType	m_demoType;
	const char*	m_details;
};

static const char helpString[] = "Controls:\n" \
"\224\225 - accelerate / brake " \
"\226\227 - steer\n" \
"\221 - handbrake " \
"\223 - brake / reverse " \
"\235 - reorient\n" \
"\n" \
"A vehicle manager containing with 50 vehicles.\n" \
"Variants of this demo exists where wheel collisions can be performed single or multithreaded, and performed using ray or linear casts.\n" \
"Linear casts are slower, but give a more realistic interaction with the entities they drive over.\n" \
"Use 'f' and 'r' to change view."
;


static const MTVehicleRayCastDemoVariant g_MTVehicleRayCastDemoVariants[] =
{
	{ "Singlethreaded Ray Cast",	MTVehicleRayCastDemoVariant::SINGLETHREADED_RAY_CAST,		helpString },
	{ "Multithreaded Ray Cast",		MTVehicleRayCastDemoVariant::MULTITHREADED_RAY_CAST,		helpString },
	{ "Singlethreaded Linear Cast",	MTVehicleRayCastDemoVariant::SINGLETHREADED_LINEAR_CAST,	helpString },
	{ "Multithreaded Linear Cast",	MTVehicleRayCastDemoVariant::MULTITHREADED_LINEAR_CAST,		helpString }
};


VehicleManagerDemo::VehicleManagerDemo( hkDemoEnvironment* env, hkBool createWorld, int numWheels, int numVehicles )
:	hkDefaultPhysicsDemo( env )
{
	const MTVehicleRayCastDemoVariant& variant = g_MTVehicleRayCastDemoVariants[m_variantId];

	m_bootstrapIterations = 150;

	numVehicles = 50;
	m_numVehicles = numVehicles;
	m_numWheels = numWheels;

	m_vehicles.setSize( m_numVehicles );

	setUpWorld();

	if (!createWorld)
	{
		return;
	}

	m_world->lock();

	//
	// Create a vehicle manager and a vehicle setup object.
	//
	VehicleSetup* vehicleSetup;
	if ( variant.m_demoType == MTVehicleRayCastDemoVariant::SINGLETHREADED_RAY_CAST || variant.m_demoType == MTVehicleRayCastDemoVariant::MULTITHREADED_RAY_CAST )
	{
		m_vehicleManager = new hkpVehicleRayCastBatchingManager();
		vehicleSetup = new VehicleSetup();
	}
	else
	{
		m_vehicleManager = new hkpVehicleLinearCastBatchingManager();
		vehicleSetup = new LinearCastVehicleSetup();
	}

	//
	// Setup vehicle chassis and create vehicles
	//
	{
		//
		// Create vehicle's chassis shape.
		//
		hkpConvexVerticesShape* chassisShape = VehicleApiUtils::createCarChassisShape(); 

		createDisplayWheels();

		for ( int vehicleId = 0; vehicleId < m_vehicles.getSize(); vehicleId++ )
		{
			//
			// Create the vehicle.
			//
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

					// Inertia tensor will be set by VehicleSetupMultithreaded.
					chassisInfo.m_position.set(-40.0f, -4.5f, vehicleId * 5.0f);
					chassisInfo.m_inertiaTensor.setDiagonal(1.0f, 1.0f, 1.0f);
					
					chassisInfo.m_centerOfMass.set( -0.037f, 0.143f, 0.0f);
					chassisInfo.m_collisionFilterInfo = hkpGroupFilter::calcFilterInfo( CHASSIS_LAYER, 0 );

					chassisRigidBody = new hkpRigidBody( chassisInfo );
				}

				// Create vehicle
				{
					hkpVehicleInstance *const vehicle = new hkpVehicleInstance( chassisRigidBody );
					vehicleSetup->buildVehicle( m_world, *vehicle );
					vehicle->addToWorld( m_world );
					m_vehicleManager->addVehicle( vehicle );

					m_vehicles[vehicleId].m_vehicle = vehicle;
					m_vehicles[vehicleId].m_lastRPM = 0.0f;
					m_vehicles[vehicleId].m_vehicle->m_wheelCollide->setCollisionFilterInfo( hkpGroupFilter::calcFilterInfo( WHEEL_LAYER, 0 ) );
				}

				// This hkpAction flips the car upright if it turns over. 	 
				if (vehicleId == 0) 	 
				{ 	 
					hkVector4 rotationAxis(1.0f, 0.0f, 0.0f); 	 
					hkVector4 upAxis(0.0f, 1.0f, 0.0f); 	 
					m_reorientAction = new hkpReorientAction(chassisRigidBody, rotationAxis, upAxis); 	 
				}

				chassisRigidBody->removeReference();
			}
		}
		chassisShape->removeReference();
	} 
	vehicleSetup->removeReference();

	//
	// Create the camera.
	//
	{
		VehicleApiUtils::createCamera( m_camera );
		m_followCarView = true;
	}

	m_world->unlock();

	//
	// Setup for multithreading.
	//
	hkpCollisionQueryJobQueueUtils::registerWithJobQueue( m_jobQueue );
	
	// register the default addCdPoint() function; you are free to register your own implementation here though
	hkpFixedBufferCdPointCollector::registerDefaultAddCdPointFunction();

	// Special case for this demo variant: we do not allow the # of active SPUs to drop to zero as this can cause a deadlock.
	if ( variant.m_demoType == MTVehicleRayCastDemoVariant::MULTITHREADED_RAY_CAST || variant.m_demoType == MTVehicleRayCastDemoVariant::MULTITHREADED_LINEAR_CAST )
	{
		m_allowZeroActiveSpus = false;
	}
}

VehicleManagerDemo::~VehicleManagerDemo( )
{
	m_world->lock();
	
	for (int vehicleId = 0; vehicleId < m_vehicles.getSize(); vehicleId++ )
	{
		// Check size of each element as not all vehicles have same number of wheels.
		for (int wheelNum = 0; wheelNum < m_displayWheelId[vehicleId].getSize(); wheelNum++)
		{
			m_env->m_displayHandler->removeGeometry(m_displayWheelId[vehicleId][wheelNum], m_tag, 0);
		}

		m_vehicles[vehicleId].m_vehicle->removeFromWorld();
		m_vehicles[vehicleId].m_vehicle->removeReference();
	}

	delete m_vehicleManager;
	
	// Release the underlying geometry data.
	// Note: normally this data is owned by the graphics system (not in our case though).
	if (m_track)
	{
		m_track->removeReference();
	}

	if (m_reorientAction != HK_NULL)
	{
		m_reorientAction->removeReference();
	}

	m_world->unlock();
}


void VehicleManagerDemo::makeFakeInput()
{
	m_env->m_gamePad->forceButtonPressed(HKG_PAD_DPAD_UP);
}

///[stepGame]
/// This is called every simulation timestep. We need to
/// - Steer the first vehicle based on user input.
/// - Step the simulation.
/// - Sync each vehicle's display wheels.
/// - Update the camera that follows the first vehicle.
/// - Draw skidmarks for the first vehicle if it is skidding.
/// - Update the RPM meter and speedometer.
///
hkDemo::Result VehicleManagerDemo::stepDemo()
{
	const MTVehicleRayCastDemoVariant& variant = g_MTVehicleRayCastDemoVariants[m_variantId];

	// Steer the vehicle from user input.
	{
		m_world->markForWrite();
		steer();
		m_world->unmarkForWrite();
	}

	m_world->markForWrite();
	
	HK_TIMER_BEGIN( "Simulate vehicles", HK_NULL );

	if ( variant.m_demoType == MTVehicleRayCastDemoVariant::MULTITHREADED_RAY_CAST || variant.m_demoType == MTVehicleRayCastDemoVariant::MULTITHREADED_LINEAR_CAST )
	{
		// Multithreaded
		m_vehicleManager->stepVehiclesSynchronously( m_world, m_jobThreadPool, m_jobQueue, NUM_SPUS );
	}
	else
	{
		// Singlethreaded
		m_vehicleManager->stepVehicles( m_world->m_dynamicsStepInfo.m_stepInfo );
	}
	HK_TIMER_END();
	
	m_world->unmarkForWrite();
	
	//
	// Step the world.
	//
	{
		hkDefaultPhysicsDemo::stepDemo();
	}


	{
		m_world->markForWrite();

		for (int vehicleId = 0; vehicleId < m_vehicles.getSize(); vehicleId++ )
		{
			VehicleApiUtils::syncDisplayWheels(m_env, 
				*m_vehicles[vehicleId].m_vehicle,
				m_displayWheelId[vehicleId], m_tag);
		}

		// Update the "follow" camera.
		VehicleDisplayUtils::VehicleDataAndDisplayInfo& playerVehicle = m_vehicles[0];

		if (m_followCarView)
		{
			VehicleApiUtils::updateCamera( m_env, *playerVehicle.m_vehicle->getChassis(), m_timestep, m_camera);
		}

		VehicleDisplayUtils::updateTyremarks( m_timestep, playerVehicle.m_vehicle );

		VehicleDisplayUtils::updateInfo( m_env, m_vehicles[0] );

		m_world->unmarkForWrite();
	}

	return DEMO_OK;
}
///>

void VehicleManagerDemo::steer()
{
	// Process Keyboard Input

	// Change follow car view
	if (m_env->getKeyState(0, 'F'))
	{
		m_followCarView = true;	
	}
	else
	{
		if (m_env->getKeyState(0, 'R'))
		{
			m_followCarView = false;	
		}
	}


	//
	// Activate chassis if any of the driving/reorientation keys have been pressed
	//
	if(m_env->m_gamePad->isButtonPressed(HKG_PAD_BUTTON_0)
		|| m_env->m_gamePad->isButtonPressed(HKG_PAD_BUTTON_2)
		|| m_env->m_gamePad->isButtonPressed(HKG_PAD_BUTTON_3)
		|| m_env->m_gamePad->isButtonPressed(HKG_PAD_DPAD_UP)
		|| m_env->m_gamePad->isButtonPressed(HKG_PAD_DPAD_DOWN)
		|| m_env->m_gamePad->isButtonPressed(HKG_PAD_DPAD_RIGHT)
		|| m_env->m_gamePad->isButtonPressed(HKG_PAD_DPAD_LEFT)
		|| m_env->m_gamePad->isButtonPressed(HKG_PAD_BUTTON_R2)
		)
	{
		m_vehicles[0].m_vehicle->getChassis()->activate();
	}

	// 	 
	// Reorient the vehicle if it has flipped 	 
	//
	if( m_reorientAction && m_world )
	{
		VehicleApiUtils::reorient( m_env->m_gamePad->isButtonPressed( HKG_PAD_BUTTON_R2 ), m_reorientAction, m_world );
	}

	// Steer the vehicle.
	VehicleApiUtils::steer( m_env->m_gamePad, m_inputXPosition, m_inputYPosition, *m_vehicles[0].m_vehicle, m_timestep);
}




void VehicleManagerDemo::setUpWorld()
{
	m_tag = 0;

	// Initially "controller" is at (0,0), ie. neither pointing left/right nor up/down.
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
		info.setBroadPhaseWorldSize(2050.0f) ;
		info.setupSolverInfo(hkpWorldCinfo::SOLVER_TYPE_4ITERS_MEDIUM);
		info.m_simulationType = hkpWorldCinfo::SIMULATION_TYPE_MULTITHREADED;
		m_world = new hkpWorld( info );
		m_world->lock();

		// Register all agents.
		hkpAgentRegisterUtil::registerAllAgents(m_world->getCollisionDispatcher());
		// Graphics.
		setupGraphics();
	}

	//
	// Create a filter, so that the ray casts of car do not collide with the ragdolls
	//
	{
		hkpGroupFilter* filter = new hkpGroupFilter();
		//filter->disableCollisionsBetween( WHEEL_LAYER, RAGDOLL_LAYER );

		m_world->setCollisionFilter( filter );
		filter->removeReference();
	}

	// Build the landscape to drive on and add it to m_world.
	buildLandscape();

	m_reorientAction = HK_NULL;
	m_world->unlock();
}

void VehicleManagerDemo::buildLandscape()
{

	if (1)
	{
		//
		// Create the ground we'll drive on.
		//
		{
			hkpRigidBodyCinfo groundInfo;

			//
			//	Set the if condition to 0 if you want to test the heightfield
			//
			if ( 1 )
			{
				FlatLand* fl = new FlatLand();
				m_track = fl;
				groundInfo.m_shape = fl->createMoppShapeForSpu();
				groundInfo.m_position.set(5.0f, -2.0f, 5.0f);
				groundInfo.m_collisionFilterInfo = hkpGroupFilter::calcFilterInfo( GROUND_LAYER, 0 );
			}

			{
				groundInfo.m_motionType = hkpMotion::MOTION_FIXED;
				groundInfo.m_friction = 0.5f;
				hkpRigidBody* groundbody = new hkpRigidBody(groundInfo);
				m_world->addEntity(groundbody);
				groundbody->removeReference();
			}

			groundInfo.m_shape->removeReference();
		}
	}

	if (1)
	{
		hkVector4 halfExtents(10.0f, 0.1f, 10.0f);
		hkVector4 startPos(-240.0f, -7.8f, 0.0f);
		hkVector4 diffPos (30.0f, 0.0f, 0.0f);
		createDodgeBoxes(5, halfExtents, startPos, diffPos);
	}

	if (1)
	{
		hkVector4 halfExtents(10.0f, 0.05f, 10.0f);
		hkVector4 startPos(-240.0f, -7.85f, 30.0f);
		hkVector4 diffPos (30.0f, 0.0f, 0.0f);
		createDodgeBoxes(5, halfExtents, startPos, diffPos);
	}

	if (1)
	{
		int gridSize = 1 + int(hkMath::sqrt( hkReal(m_env->m_cpuMhz/100) ));
		createRagdollGrid( m_world, gridSize, gridSize, 4.0f, 4.0f, m_ragdolls );
	}
}

void VehicleManagerDemo::createDodgeBoxes(hkUint16 num, hkVector4& halfExtents, hkVector4& startPos, hkVector4& diffPos)
{
	for(int i = 0; i < num; i++)
	{
		/////////////////// SHAPE CONSTRUCTION ////////////////
		hkpBoxShape* shape = new hkpBoxShape(halfExtents);
		///////////////////////////////////////////////////////

		hkVector4 gapp;
		gapp.setMul4((hkReal)i, diffPos);

		// To illustrate using the shape, create a rigid body by first defining a template.
		hkpRigidBodyCinfo rigidBodyInfo;

		rigidBodyInfo.m_shape = shape;
		rigidBodyInfo.m_position.setAdd4(startPos, gapp);
		rigidBodyInfo.m_angularDamping = 0.0f;
		rigidBodyInfo.m_linearDamping = 0.0f;

		rigidBodyInfo.m_motionType = hkpMotion::MOTION_FIXED;

		// If we set this to true, the body is fixed, and no mass properties need to be computed.
		//rigidBodyInfo.m_motionType = hkpMotion::MOTION_BOX_INERTIA;

		// If we need to compute mass properties, we'll do this using the hkpInertiaTensorComputer.
		if (rigidBodyInfo.m_motionType != hkpMotion::MOTION_FIXED)
		{
			hkReal mass = 10.0f;
			hkpMassProperties massProperties;
			hkpInertiaTensorComputer::computeBoxVolumeMassProperties(halfExtents, mass, massProperties);

			rigidBodyInfo.m_inertiaTensor = massProperties.m_inertiaTensor;
			rigidBodyInfo.m_centerOfMass = massProperties.m_centerOfMass;
			rigidBodyInfo.m_mass = massProperties.m_mass;			
		}	


		// Create a rigid body (using the template above).
		hkpRigidBody* rigidBody = new hkpRigidBody(rigidBodyInfo);

		// Remove reference since the body now "owns" the Shape.
		shape->removeReference();

		// Finally add body so we can see it, and remove reference since the world now "owns" it.
		m_world->addEntity(rigidBody);
		rigidBody->removeReference();
	}

}

//
// Create a grid of ragdolls
//
void VehicleManagerDemo::createRagdollGrid( hkpWorld* world, int x_size, int y_size, hkReal xStep, hkReal yStep, hkArray<hkRagdoll*>&	ragdollsOut)
{
	int systemGroup = 2;
	hkReal ragdollHeight = 2.50f;

	for( int x = 0; x < x_size; x++ )
	{
		for( int y = 0; y < y_size; y++ )
		{
			hkVector4 position; 
			// do a raycast to place the ragdoll
			{
				hkpWorldRayCastInput ray;
				ray.m_from.set( x * xStep,  10, y * yStep );
				ray.m_to.  set( x * xStep, -10, y * yStep );
				hkpWorldRayCastOutput result;
				world->castRay( ray, result );
				position.setInterpolate4( ray.m_from, ray.m_to, result.m_hitFraction );
				position(1) += ragdollHeight* 0.5f;
			}

			hkQuaternion	rotation; rotation.setIdentity();

			rotation.setAxisAngle( hkTransform::getIdentity().getColumn(0), HK_REAL_PI  * -0.5f );

			hkpPhysicsSystem* ragdoll = GameUtils::createRagdoll( ragdollHeight, position, rotation, systemGroup, GameUtils::RPT_CAPSULE );
			{
				for ( int i = 0; i < ragdoll->getRigidBodies().getSize(); i++)
				{
					hkpRigidBody* rb = ragdoll->getRigidBodies()[i];
					rb->setCollisionFilterInfo( hkpGroupFilter::calcFilterInfo( RAGDOLL_LAYER, systemGroup ) );
				}
			}
			systemGroup++;

			world->addPhysicsSystem(ragdoll);
			{
				// Give the ragdolls some personality
				int color = hkColor::getRandomColor();
				for (hkInt32 i = 0; i < ragdoll->getRigidBodies().getSize(); i++)
				{
					hkpRigidBody* rb = ragdoll->getRigidBodies()[i];
					HK_SET_OBJECT_COLOR((hkUlong)rb->getCollidable(), color);	
				}
			}
			ragdoll->getRigidBodies()[0]->deactivate();
			ragdoll->removeReference();
		}
	}
}

void VehicleManagerDemo::createDisplayWheels(hkReal radius, hkReal thickness)
{
	//
	// Create the wheel display geometries. Note: we use a Havok hkDisplayGeometry here, to
	// make binding to the Havok demo framework and Visual Debugger graphics engine easier.
	// However you can use whatever you want!
	//

	// The id for the wheel displayGeometry is an odd number. This prevents it conflicting
	// with hkpCollidable pointers which are used as ids for rigid bodies by convention in 
	// the Visual Debugger.
	int displayId = 1;

	m_displayWheelId.setSize( m_vehicles.getSize() );

	for (int vehicleId = 0; vehicleId < m_vehicles.getSize(); vehicleId++)
	{
		m_displayWheelId[vehicleId].setSize( m_numWheels );

		// Create a display wheel for each wheel on the vehicle.
		for(int i = 0; i < m_numWheels; i++)
		{
			VehicleApiUtils::createDisplayWheels(m_env, m_tag, displayId, radius, thickness);

			m_displayWheelId[vehicleId][i] = displayId;

			displayId += 2;
		}
	}
}


#if defined(HK_COMPILER_MWERKS)
#	pragma force_active on
#	pragma fullpath_file on
#endif

HK_DECLARE_DEMO_VARIANT_USING_STRUCT(VehicleManagerDemo, HK_DEMO_TYPE_PHYSICS, MTVehicleRayCastDemoVariant, g_MTVehicleRayCastDemoVariants, helpString);

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
