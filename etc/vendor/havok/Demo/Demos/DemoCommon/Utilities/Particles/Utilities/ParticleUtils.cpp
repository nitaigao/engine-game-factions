/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Demos/DemoCommon/Utilities/Particles/Utilities/ParticleUtils.h>
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastInput.h>
#include <Physics/Collide/Query/Collector/RayCollector/hkpClosestRayHitCollector.h>
#include <Common/Visualize/hkDebugDisplay.h>

void ParticleUtils::ageParticles(int& numParticlesRef, char* basePtr, char* agePtr, const char* lifeTimePtr, int particleStride, hkReal timestep)
{
	for(int i = 0; i < numParticlesRef; ++i)
	{
		hkReal& age = *reinterpret_cast<hkReal*>(agePtr);
		const hkReal& lifeTime = *reinterpret_cast<const hkReal*>(lifeTimePtr);

		age += timestep;
		if(age >= lifeTime)
		{
			--numParticlesRef;
			char* srcPar = basePtr + numParticlesRef*particleStride;
			char* dstPar = basePtr + i*particleStride;
			hkString::memCpy(dstPar, srcPar, particleStride);
			--i;
		}
		else
		{
			agePtr += particleStride;
			lifeTimePtr += particleStride;
		}
	}
}

void ParticleUtils::moveParticles(int numParticles, char* posPtr, char* velPtr, int particleStride, hkReal timestep, const hkVector4& acceleration)
{
	for(int i = 0; i < numParticles; ++i)
	{
		hkVector4& position = *reinterpret_cast<hkVector4*>(posPtr);
		hkVector4& velocity = *reinterpret_cast<hkVector4*>(velPtr);

		velocity.addMul4(timestep, acceleration);
		position.addMul4(timestep, velocity);

		posPtr += particleStride;
		velPtr += particleStride;
	}
}

void ParticleUtils::moveParticlesWithRaycastCollisions( int numParticles, char* posPtr, char* velPtr, int particleStride,
	hkReal timestep, const hkVector4& acceleration, hkReal friction, hkReal restitution, hkpWorld* world )
{
	hkpWorldRayCastInput rayInput;
	hkpWorldRayCastOutput rayOutput;

	world->lock();

	for(int i = 0; i < numParticles; ++i)
	{
		hkVector4& position = *reinterpret_cast<hkVector4*>(posPtr);
		hkVector4& velocity = *reinterpret_cast<hkVector4*>(velPtr);

		hkVector4 candVel = velocity;
		candVel.addMul4(timestep, acceleration);

		hkVector4 candPos = position;
		candPos.addMul4(timestep, candVel);

		hkpWorldRayCastInput& in = rayInput;
		in.m_from = position;
		in.m_to = candPos;

		hkpWorldRayCastOutput& out = rayOutput;
		out.reset();
		world->castRay(in, out);

		if(out.hasHit())
		{
			position.setInterpolate4(in.m_from, in.m_to, out.m_hitFraction);
			//position.addMul4(0.01f, out.m_normal);

			hkVector4 vel_norm = out.m_normal;
			hkReal dot = velocity.dot3(out.m_normal);
			vel_norm.mul4(dot);

			hkVector4 vel_tang = velocity;
			vel_tang.sub4(vel_norm);

			velocity = vel_tang;
			velocity.mul4(friction);
			velocity.addMul4(-restitution, vel_norm);
		}
		else
		{
			position = candPos;
			velocity = candVel;
		}

		posPtr += particleStride;
		velPtr += particleStride;
	}

	world->unlock();
}

void ParticleUtils::debugDrawParticles(int numParticles, const char* posPtr, int particleStride, hkReal size, int color)
{
	for(int i = 0; i < numParticles; ++i)
	{
		const hkVector4& position = *reinterpret_cast<const hkVector4*>(posPtr);
		HK_DISPLAY_STAR(position, size, color);

		posPtr += particleStride;
	}
}

void ParticleUtils::debugDrawParticles(int numParticles, const char* posPtr, const char* sizePtr, int particleStride, int color)
{
	for(int i = 0; i < numParticles; ++i)
	{
		const hkVector4& position = *reinterpret_cast<const hkVector4*>(posPtr);
		const hkReal& size = *reinterpret_cast<const hkReal*>(sizePtr);
		HK_DISPLAY_STAR(position, size, color);

		posPtr += particleStride;
		sizePtr += particleStride;
	}
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
