/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Physics/Collide/Util/ShapeCutter/hkpShapeCutterUtil.h>
#include <Physics/Collide/Shape/Convex/ConvexTranslate/hkpConvexTranslateShape.h>
#include <Physics/Collide/Shape/Compound/Collection/List/hkpListShape.h>

#include <Demos/Physics/Api/Collide/OfflineGeneration/ShapeSubtract/ShapeSubtractDemo.h>


ShapeSubtractDemo::ShapeSubtractDemo(hkDemoEnvironment* env)
:	hkDefaultPhysicsDemo(env)
{
	// Setup the camera.
	{
		hkVector4 from( 3.0f, 5.0f, 10.0f );
		hkVector4 to( 0.0f, 0.0f, 0.0f );
		hkVector4 up( 0.0f, 1.0f, 0.0f );
		setupDefaultCameras( env, from, to, up, 0.1f, 1000.0f );
	}

	// Create the world.
	{
		hkpWorldCinfo info;
		info.m_gravity.set( 0.0f, 0.0f, 0.0f );
		info.setBroadPhaseWorldSize( 500.0f );
		m_world = new hkpWorld( info );
		m_world->lock();
	}

	
	// Register the agents
	{
		hkpAgentRegisterUtil::registerAllAgents( m_world->getCollisionDispatcher() );
	}

	// Setup graphics
	{
		setupGraphics();
	}


	// create a rigid body (for display only)
	// which will be used to subtract a shape from
	{
		hkpRigidBodyCinfo cinfo;
		cinfo.m_shape = new hkpSphereShape( 0.1f );
		cinfo.m_motionType = hkpMotion::MOTION_FIXED;

		hkpRigidBody* body = new hkpRigidBody(cinfo );
		cinfo.m_shape->removeReference();
		m_world->addEntity( body );
		body->removeReference();

		m_body = body;
	}

	// create a second moveable rigid body, which will be used
	// as a subtract shape
	{
		hkpRigidBodyCinfo cinfo;
		hkpConvexVerticesShape* subtractShape;
		{
			hkpBoxShape smallBox( hkVector4(.3f,.3f,.3f), 0.1f );
			hkAabb aabb; smallBox.getAabb( hkTransform::getIdentity(), 0.0f, aabb );
			subtractShape = hkpShapeCutterUtil::createAabbConvexVerticesShape( aabb, 0.0f );
		}

		cinfo.m_shape = subtractShape;
		cinfo.m_motionType = hkpMotion::MOTION_DYNAMIC;
		cinfo.m_linearDamping = 10.0f;
		cinfo.m_angularDamping = 10.0f;
		cinfo.m_position(0) = 1;

		hkpRigidBody* body = new hkpRigidBody(cinfo );
		body->addProperty( HK_PROPERTY_DEBUG_DISPLAY_COLOR, int(0x804040c0) );
		cinfo.m_shape->removeReference();
		m_world->addEntity( body );
		body->removeReference();

		m_subtractBody = body;
	}
	
	m_world->unlock();
}


hkDemo::Result ShapeSubtractDemo::stepDemo()
{
	{
		m_world->lock();
		// build a box
		hkpBoxShape* bigBox = new hkpBoxShape( hkVector4(1,3,1), 0.02f );
		hkpBoxShape* smallBox = new hkpBoxShape( hkVector4(1,1,1), 0.02f );
		hkpConvexShape* shiftedSmallBox = new hkpConvexTranslateShape( smallBox, hkVector4( -2,0,0 ));
		smallBox->removeReference();
		hkpShape* shapes[] = { bigBox, shiftedSmallBox };
		hkpListShape* shape = new hkpListShape( &shapes[0], 2, hkpShapeContainer::REFERENCE_POLICY_IGNORE );

		hkpShapeCutterUtil::SubtractShapeInput input;
		input.m_dispatcher = m_world->getCollisionDispatcher();
		input.m_transform = m_subtractBody->getTransform();
		input.m_allowedPentration = 0.1f;
		input.m_subtractShape = static_cast<const hkpConvexVerticesShape*>(m_subtractBody->getCollidable()->getShape());

		const hkpShape* cutShape = hkpShapeCutterUtil::subtractConvexShape( shape, input );
		shape->removeReference();

		m_body->setShape( cutShape );
		cutShape->removeReference();

		m_world->unlock();
	}
	return hkDefaultPhysicsDemo::stepDemo();
}


#if defined(HK_COMPILER_MWERKS)
#	pragma force_active on
#	pragma fullpath_file on
#endif

HK_DECLARE_DEMO( ShapeSubtractDemo, HK_DEMO_TYPE_PHYSICS, "Subtract a shape from another shape", "" );

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
