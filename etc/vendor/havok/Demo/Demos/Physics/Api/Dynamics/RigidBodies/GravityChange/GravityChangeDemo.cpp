/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Demos/Physics/Api/Dynamics/RigidBodies/GravityChange/GravityChangeDemo.h>



GravityChangeDemo::GravityChangeDemo(hkDemoEnvironment* env)
:	hkDefaultPhysicsDemo(env)
{
	//
	// Setup the camera
	//
	{
		hkVector4 from(0.0f, 7.0f, 20.0f);
		hkVector4 to  (0.0f, 3.0f,  0.0f);
		hkVector4 up  (0.0f, 1.0f,  0.0f);
		setupDefaultCameras( env, from, to, up );
	}

		// Create the world
	{
		hkpWorldCinfo info;
		info.setupSolverInfo(hkpWorldCinfo::SOLVER_TYPE_4ITERS_MEDIUM); 
		info.setBroadPhaseWorldSize( 100.0f );
			// we use a rather small collision tolerance, so that we reduce the artefacts in
			// case a contact point is created before the objects actually hit
		info.m_collisionTolerance = 0.04f;
		info.m_contactRestingVelocity = 0.2f;
		m_world = new hkpWorld( info );
		m_world->lock();

		setupGraphics();
	}

	// Register the agent
	{
		hkpAgentRegisterUtil::registerAllAgents(m_world->getCollisionDispatcher());
	}


	// Illustrative parameters for the demo
	unsigned int numObjects = 10; // the number of box/sphere pairs
	hkReal objectStep = 1.2f; // a notional 'width' of a box/sphere pair
	

	// Derived parameters for the demo
	hkReal positionAlongX = - (objectStep * numObjects) / 2.0f;

	// Geometric parameters for the demo
	hkVector4 boxSize(0.5f, 0.1f, 0.5f);
	hkReal sphereRadius = 0.5f;
	hkpBoxShape* boxShape = new hkpBoxShape( boxSize , 0 );
	hkpSphereShape* sphereShape = new hkpSphereShape( sphereRadius );

	// Physical parameters for the demo
	hkReal sphereMass = 1.0f;

	// Create the objects
	for ( unsigned int i = 0; i <= numObjects; i++ )
	{
		{
			// Position of the box
			hkVector4 boxPosition(positionAlongX, 0.0f, 0.0f);

			// Set up the construction info parameters for the box
			hkpRigidBodyCinfo info;
			info.m_motionType = hkpMotion::MOTION_FIXED;
			info.m_restitution = 0.0f;
			info.m_shape = boxShape;
			info.m_position = boxPosition;

			// Create fixed box
			hkpRigidBody* box = new hkpRigidBody(info);
			m_world->addEntity(box);
			box->removeReference();
		}

		{

			// Compute the sphere inertia tensor
			hkpMassProperties massProperties;
			hkpInertiaTensorComputer::computeSphereVolumeMassProperties(sphereRadius, sphereMass, massProperties);

			// Set up the construction info parameters for the sphere
			hkpRigidBodyCinfo info;
			info.m_restitution = 0.0f;
			info.m_mass = sphereMass;
			info.m_shape = sphereShape;
			info.m_inertiaTensor = massProperties.m_inertiaTensor;
			info.m_motionType = hkpMotion::MOTION_SPHERE_INERTIA;
			info.m_position.set(positionAlongX, 5.0f, 0.0f);

			info.m_gravityFactor = -0.9f + 0.2f * i;

			// Create movable sphere
			hkpRigidBody* sphere = new hkpRigidBody(info);
			m_world->addEntity(sphere);
			sphere->removeReference();
		}

		positionAlongX += objectStep;
	}

	// Clean up
	boxShape->removeReference();
	sphereShape->removeReference();

	m_world->unlock();
}

#if defined(HK_COMPILER_MWERKS)
#	pragma force_active on
#	pragma fullpath_file on
#endif

static const char helpString[] = \
"A demo which shows how to change the gravity on a per rigid body basis. " \
"10 spheres with a gravity factor ranging -1 to 1 are created in the world. ";

HK_DECLARE_DEMO(GravityChangeDemo, HK_DEMO_TYPE_PRIME, "Varying restitution values, from soft to bouncy", helpString);

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
