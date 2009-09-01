/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
 
#include <Demos/demos.h>

#include <Demos/Physics/Api/Vehicle/LinearCastVehicle/LinearCastVehicle.h>
#include <Demos/Physics/Api/Vehicle/VehicleApi/LinearCastVehicleSetup.h>

#include <Physics/Vehicle/hkpVehicleInstance.h>
#include <Physics/Utilities/Actions/Reorient/hkpReorientAction.h>

// Various demo facilities for setting up the vehicle or the world

#include <Demos/Physics/Api/Vehicle/VehicleApi/VehicleApiUtils.h>
#include <Demos/DemoCommon/Utilities/GameUtils/Landscape/FlatLand.h>

// Graphics

#include <Graphics/Common/Material/hkgMaterial.h>
#include <Graphics/Common/DisplayObject/hkgDisplayObject.h>
#include <Graphics/Bridge/DisplayHandler/hkgDisplayHandler.h>

// Debug display

#include <Common/Visualize/hkDebugDisplay.h>

// Used for setting up the ragdolls

#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastInput.h>
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>
#include <Demos/DemoCommon/Utilities/GameUtils/GameUtils.h>
#include <Physics/Dynamics/World/hkpPhysicsSystem.h>


enum {
	GROUND_LAYER,
	CHASSIS_LAYER,
	WHEEL_LAYER,
	RAGDOLL_LAYER
};


LinearCastVehicleDemo::LinearCastVehicleDemo( hkDemoEnvironment* env, hkBool createWorld )
:	hkDefaultPhysicsDemo(env)
{
	m_bootstrapIterations = 150;

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
		m_world = new hkpWorld( info );
	}

	m_world->lock();

	{
		// Register all agents.
		hkpAgentRegisterUtil::registerAllAgents(m_world->getCollisionDispatcher());
		// Graphics.
		setupGraphics();
	}

	//
	// Create a filter, so that the wheels of the car do not collide with the chassis.
	//
	{
		hkpGroupFilter* filter = new hkpGroupFilter();
		filter->disableCollisionsBetween( CHASSIS_LAYER, WHEEL_LAYER );

		m_world->setCollisionFilter( filter );
		filter->removeReference();
	}

	// Build the landscape to drive on and add it to m_world.
	{
		hkpRigidBodyCinfo groundInfo;
		{
			FlatLand* fl = new FlatLand();
			m_track = fl;
			groundInfo.m_shape = fl->createMoppShapeForSpu();
			groundInfo.m_position.set(5.0f, -2.0f, 5.0f);
			groundInfo.m_motionType = hkpMotion::MOTION_FIXED;
			groundInfo.m_friction = 0.5f;
			groundInfo.m_collisionFilterInfo = hkpGroupFilter::calcFilterInfo( GROUND_LAYER, 0 );
		}
		hkpRigidBody* groundbody = new hkpRigidBody(groundInfo);
		m_world->addEntity(groundbody);
		groundbody->removeReference();
		groundInfo.m_shape->removeReference();
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

	{
		// Create the chassis body.
		hkpRigidBody* chassisRigidBody;
		{
			//
			// Create vehicle's chassis shape.
			//
			hkpConvexVerticesShape* chassisShape = VehicleApiUtils::createCarChassisShape(); 

			hkpRigidBodyCinfo chassisInfo;
			chassisInfo.m_mass = 750.0f;	
			chassisInfo.m_shape = chassisShape;
			chassisInfo.m_friction = 0.8f;
			chassisInfo.m_motionType = hkpMotion::MOTION_BOX_INERTIA;
			// Position chassis on the ground.

			// Inertia tensor will be set by VehicleSetup.
			chassisInfo.m_position.set(-40.0f, -4.5f, 0.0f);
			chassisInfo.m_inertiaTensor.setDiagonal(1.0f, 1.0f, 1.0f);

			chassisInfo.m_centerOfMass.set( -0.037f, 0.143f, 0.0f);
			chassisInfo.m_collisionFilterInfo = hkpGroupFilter::calcFilterInfo( CHASSIS_LAYER, 0 );

			chassisRigidBody = new hkpRigidBody(chassisInfo);
			chassisShape->removeReference();
		}

		// This hkpAction flips the car upright if it turns over. 	 
		{
			hkVector4 rotationAxis(1.0f, 0.0f, 0.0f); 	 
			hkVector4 upAxis(0.0f, 1.0f, 0.0f); 	 
			m_reorientAction = new hkpReorientAction(chassisRigidBody, rotationAxis, upAxis); 	 
		}
		
		m_vehicle = new hkpVehicleInstance( chassisRigidBody );
		LinearCastVehicleSetup setup;
		setup.buildVehicle( m_world, *m_vehicle );

		m_vehicle->addToWorld( m_world );

		HK_SET_OBJECT_COLOR( hkUlong( chassisRigidBody->getCollidable() ), hkColor::rgbFromChars( 255, 0, 0, 100 ) );

		chassisRigidBody->removeReference();

		m_vehicle->m_wheelCollide->setCollisionFilterInfo( hkpGroupFilter::calcFilterInfo( WHEEL_LAYER, 0 ) );
	
		m_world->addAction( m_vehicle );
	}

	{
		int displayId = 1;

		const int numWheels = m_vehicle->getNumWheels();
		m_displayWheelId.setSize( numWheels );

		// Create a display wheel for each wheel on the vehicle.
		for(int i = 0; i < numWheels; ++i)
		{
			// We'll use wheel 0 to define the display wheel parameters.
			const hkReal radius = m_vehicle->m_data->m_wheelParams[i].m_radius;
			const hkReal thickness = m_vehicle->m_data->m_wheelParams[i].m_width;

			VehicleApiUtils::createDisplayWheels( m_env, m_tag, displayId, radius, thickness );
			m_displayWheelId[i] = displayId;
			displayId += 2;
		}
	}

	//
	// Create the camera.
	//
	{
		VehicleApiUtils::createCamera( m_camera );
	}

	m_world->unlock();
}

void LinearCastVehicleDemo::createDodgeBoxes(hkUint16 num, hkVector4& halfExtents, hkVector4& startPos, hkVector4& diffPos)
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

void LinearCastVehicleDemo::createRagdollGrid( hkpWorld* world, int x_size, int y_size, hkReal xStep, hkReal yStep, hkArray<hkRagdoll*>& ragdollsOut)
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
			ragdoll->getRigidBodies()[0]->deactivate();
			ragdoll->removeReference();
		}
	}
}



LinearCastVehicleDemo::~LinearCastVehicleDemo( )
{
	m_world->lock();

	// Remove display wheels.
	for ( int wheelNum = 0; wheelNum < m_vehicle->getNumWheels(); ++wheelNum )
	{
		m_env->m_displayHandler->removeGeometry( m_displayWheelId[wheelNum], m_tag, 0 );
	}

	m_vehicle->removeFromWorld();
	m_vehicle->removeReference();

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


hkDemo::Result LinearCastVehicleDemo::stepDemo()
{
	{
		m_world->markForWrite();

		// Keep the vehicle activated.
		m_vehicle->getChassis()->activate();
		
		// Steer the vehicle from user input.
		VehicleApiUtils::steer( m_env->m_gamePad, m_inputXPosition, m_inputYPosition, *m_vehicle, m_timestep);

		m_world->unmarkForWrite();
	}

	//
	// Step the world.
	//
	{
		hkDefaultPhysicsDemo::stepDemo();
	}

	VehicleApiUtils::syncDisplayWheels( m_env, *m_vehicle, m_displayWheelId, m_tag );
	
	{
		m_world->markForWrite();

		VehicleApiUtils::updateCamera( m_env, *m_vehicle->getChassis(), m_timestep, m_camera);

		m_world->unmarkForWrite();
	}

	return DEMO_OK;
}


#if defined(HK_COMPILER_MWERKS)
#	pragma force_active on
#	pragma fullpath_file on
#endif

static const char helpString[] = "Help string here...";

HK_DECLARE_DEMO( LinearCastVehicleDemo, HK_DEMO_TYPE_PHYSICS, "A car which uses linear shape casts for wheel collision detection", helpString);

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
