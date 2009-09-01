/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Demos/DemoCommon/Utilities/Particles/Utilities/ParticleCollisionUtil.h>
#include <Physics/Dynamics/Phantom/hkpSimpleShapePhantom.h>
#include <Physics/Collide/Query/Collector/PointCollector/hkpClosestCdPointCollector.h>
#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>

ParticleCollisionUtil::ParticleCollisionUtil(hkpWorld* world, hkReal particleRadius)
	: m_world(world),
	  m_particleRadius(particleRadius)
{
	// Add the sphere phantom to the world.
	m_world->lock();
	hkpSphereShape* sphere = new hkpSphereShape(m_particleRadius);
	hkTransform transform;
	transform.setIdentity();
	m_phantom = new hkpSimpleShapePhantom(sphere, transform);
	sphere->removeReference();
	m_world->addPhantom(m_phantom);
	m_world->unlock();
}

ParticleCollisionUtil::~ParticleCollisionUtil()
{
	m_world->lock();
	m_world->removePhantom(m_phantom);
	m_world->unlock();
	m_phantom->removeReference();
}

void ParticleCollisionUtil::moveParticles( int numParticles, char* posPtr, char* velPtr, int particleStride,
	hkReal timestep, const hkVector4& acceleration, hkReal friction, hkReal restitution )
{
	hkpClosestCdPointCollector collector;

	m_world->lock();

	for(int i = 0; i < numParticles; ++i)
	{
		hkVector4& position = *reinterpret_cast<hkVector4*>(posPtr);
		hkVector4& velocity = *reinterpret_cast<hkVector4*>(velPtr);

		hkVector4 candVel = velocity;
		candVel.addMul4(timestep, acceleration);

		hkVector4 candPos = position;
		candPos.addMul4(timestep, candVel);

		m_phantom->setPosition(candPos);
		collector.reset();
		m_phantom->getClosestPoints(collector);

		if(collector.hasHit() && collector.getHitContact().getDistance() < -m_particleRadius)
		{
			position = collector.getHitContact().getPosition();

			// Compute the velocity of the collided object at the contact point.
			hkVector4 objVel;
			{
				objVel.setZero4();
				const hkpRootCdPoint& hit = collector.getHit();
				const hkpCollidable* target = hit.m_rootCollidableB;	
				if(target->getOwner())
				{
					hkpRigidBody* rb = hkGetRigidBody(target);
					if(rb)
					{
						rb->getPointVelocity(collector.getHitContact().getPosition(), objVel);
					}
				}
			}

			hkVector4 relVel = velocity;
			relVel.sub4(objVel);

			hkVector4 vel_norm = collector.getHitContact().getNormal();
			hkReal dot = relVel.dot3(collector.getHitContact().getNormal());
			vel_norm.mul4(dot);

			hkVector4 vel_tang = relVel;
			vel_tang.sub4(vel_norm);

			velocity = vel_tang;
			velocity.mul4(friction);
			velocity.addMul4(-restitution, vel_norm);
			velocity.add4(objVel);
		}
		else
		{
			position = candPos;
			velocity = candVel;
		}

		posPtr += particleStride;
		velPtr += particleStride;
	}

	m_world->unlock();
}

void ParticleCollisionUtil::moveParticlesAndRecordFractures( int numParticles, char* posPtr, char* velPtr, const char* sizePtr, int particleStride,
	hkReal timestep, const hkVector4& acceleration, hkReal friction, hkReal restitution, hkArray<hkVector4>& fracturePoints, int maxFractures,
	hkReal sizeThreshold, hkReal relativeSpeedThreshold, hkReal fractureProbability, hkPseudoRandomGenerator* pseudoRandomGenerator )
{
	const hkReal relativeSpeedThresholdSquared = relativeSpeedThreshold * relativeSpeedThreshold;

	hkpClosestCdPointCollector collector;

	m_world->lock();

	for(int i = 0; i < numParticles; ++i)
	{
		hkVector4& position = *reinterpret_cast<hkVector4*>(posPtr);
		hkVector4& velocity = *reinterpret_cast<hkVector4*>(velPtr);

		hkVector4 candVel = velocity;
		candVel.addMul4(timestep, acceleration);

		hkVector4 candPos = position;
		candPos.addMul4(timestep, candVel);

		m_phantom->setPosition(candPos);
		collector.reset();
		m_phantom->getClosestPoints(collector);

		if(collector.hasHit() && collector.getHitContact().getDistance() < -m_particleRadius)
		{
			position = collector.getHitContact().getPosition();

			// Compute the velocity of the collided object at the contact point.
			hkVector4 objVel;
			{
				objVel.setZero4();
				const hkpRootCdPoint& hit = collector.getHit();
				const hkpCollidable* target = hit.m_rootCollidableB;	
				if(target->getOwner())
				{
					hkpRigidBody* rb = hkGetRigidBody(target);
					if(rb)
					{
						rb->getPointVelocity(collector.getHitContact().getPosition(), objVel);
					}
				}
			}

			hkVector4 relVel = velocity;
			relVel.sub4(objVel);

			hkVector4 vel_norm = collector.getHitContact().getNormal();
			hkReal dot = relVel.dot3(collector.getHitContact().getNormal());
			vel_norm.mul4(dot);

			hkVector4 vel_tang = relVel;
			vel_tang.sub4(vel_norm);

			velocity = vel_tang;
			velocity.mul4(friction);
			velocity.addMul4(-restitution, vel_norm);
			velocity.add4(objVel);

			const hkReal& size = *reinterpret_cast<const hkReal*>(sizePtr);
			if( fracturePoints.getSize() < maxFractures &&
				size > sizeThreshold &&
				relVel.lengthSquared3() > relativeSpeedThresholdSquared &&
				pseudoRandomGenerator->getRandReal01() < fractureProbability )
			{
				hkVector4 &fp = fracturePoints.expandOne();
				fp = collector.getHitContact().getPosition();
				fp.setInt24W(i);
			}
		}
		else
		{
			position = candPos;
			velocity = candVel;
		}

		posPtr += particleStride;
		velPtr += particleStride;
		sizePtr += particleStride;
	}

	m_world->unlock();
}

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
