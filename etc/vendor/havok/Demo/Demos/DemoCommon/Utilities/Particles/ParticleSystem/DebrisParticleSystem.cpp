/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Demos/DemoCommon/Utilities/Particles/ParticleSystem/DebrisParticleSystem.h>
#include <Demos/DemoCommon/Utilities/Particles/Utilities/DiskEmissionUtil.h>
#include <Demos/DemoCommon/Utilities/Particles/Utilities/ParticleUtils.h>
#include <Demos/DemoCommon/Utilities/Particles/Utilities/ParticleCollisionUtil.h>
#include <Common/Base/Container/LocalArray/hkLocalArray.h>
#include <Common/Visualize/hkDebugDisplay.h>

DebrisParticleSystem::EmitParams::EmitParams()
	: m_diskEmissionUtil(HK_NULL),
	  m_minSpeed(0.f),
	  m_maxSpeed(0.f),
	  m_minSpinRate(0.f),
	  m_maxSpinRate(0.f),
	  m_minLifeTime(1.f),
	  m_maxLifeTime(1.f),
	  m_minSize(1.f),
	  m_maxSize(1.f)
{
}

DebrisParticleSystem::DebrisParticleSystem(int randomSeed, int flags, hkpWorld* world, int particleStride)
	: ParticleSystem(particleStride),
	  m_acceleration(0.f, -9.81f, 0.f),
	  m_friction(0.75f),
	  m_restitution(0.4f),
	  m_maxFractures(100),
	  m_sizeThreshold(0.1f),
	  m_relativeSpeedThreshold(0.f),
	  m_fractureProbability(1.f),
	  m_pseudoRandomGenerator(randomSeed),
	  m_collisionUtil(HK_NULL),
	  m_enableFractures(false)
{
	if(flags & ENABLE_COLLISIONS)
	{
		m_collisionUtil = new ParticleCollisionUtil(world);
		m_enableFractures = (flags & ENABLE_FRACTURES) != 0;
	}
}

DebrisParticleSystem::~DebrisParticleSystem()
{
	delete m_collisionUtil;
}

void DebrisParticleSystem::draw()
{
	const char* data = static_cast<const char*>(m_particleData);

	ParticleUtils::debugDrawParticles(m_numParticles, data+Particle::POS_OFFSET, m_particleStride, 0.025f, hkColor::RED);
}

void DebrisParticleSystem::initParticles(int numParticles, void* particleData, hkReal timestep, const void* emitParams)
{
	HK_ASSERT(0x1916802a, emitParams);
	const EmitParams* params = static_cast<const EmitParams*>(emitParams);
	HK_ASSERT(0x5e35027b, params->m_diskEmissionUtil);

	for(int i = 0; i < numParticles; ++i)
	{
		Particle& p = *reinterpret_cast<Particle*>(static_cast<char*>(particleData) + i*m_particleStride);

		params->m_diskEmissionUtil->samplePosition(p.m_position, &m_pseudoRandomGenerator);
		p.m_position(3) = m_pseudoRandomGenerator.getRandReal01() * 2.f * HK_REAL_PI;
		params->m_diskEmissionUtil->sampleDirection(p.m_velocity, &m_pseudoRandomGenerator);
		p.m_velocity.mul4(m_pseudoRandomGenerator.getRandRange(params->m_minSpeed, params->m_maxSpeed));
		p.m_velocity(3) = m_pseudoRandomGenerator.getRandRange(params->m_minSpinRate, params->m_maxSpinRate);
		p.m_lifeTime = m_pseudoRandomGenerator.getRandRange(params->m_minLifeTime, params->m_maxLifeTime);
		p.m_age = m_pseudoRandomGenerator.getRandReal01() * timestep;
		p.m_size = m_pseudoRandomGenerator.getRandRange(params->m_minSize, params->m_maxSize);

		// Particle positions are initially integrated by a random amount to make it seem as
		// though they are emitted continuously over time instead of at discrete time steps.
		p.m_position.addMul4(p.m_age, p.m_velocity);
	}
}

void DebrisParticleSystem::updateParticles(int& numParticlesRef, void* particleData, hkReal timestep)
{
	char* data = static_cast<char*>(particleData);

	ParticleUtils::ageParticles(numParticlesRef, data, data+Particle::AGE_OFFSET, data+Particle::LIFETIME_OFFSET, m_particleStride, timestep);

	if(!m_collisionUtil)
	{
		ParticleUtils::moveParticles( numParticlesRef, data+Particle::POS_OFFSET, data+Particle::VEL_OFFSET,
			m_particleStride, timestep, m_acceleration );
	}
	else
	{
		if(!m_enableFractures)
		{
			m_collisionUtil->moveParticles( numParticlesRef, data+Particle::POS_OFFSET, data+Particle::VEL_OFFSET,
				m_particleStride, timestep, m_acceleration, m_friction, m_restitution );
		}
		else
		{
			hkLocalArray<hkVector4> fracturePoints(m_maxFractures);
			m_collisionUtil->moveParticlesAndRecordFractures( numParticlesRef, data+Particle::POS_OFFSET, data+Particle::VEL_OFFSET,
				data+Particle::SIZE_OFFSET, m_particleStride, timestep, m_acceleration, m_friction, m_restitution, fracturePoints,
				m_maxFractures, m_sizeThreshold, m_relativeSpeedThreshold, m_fractureProbability, &m_pseudoRandomGenerator );

			// For each fractured parent particle, emit smaller child particles.
			int numFracturePoints = fracturePoints.getSize();
			for(int i = 0; i < numFracturePoints; ++i)
			{
				int parentIndex = fracturePoints[i].getInt24W();
				Particle* parentParticle = reinterpret_cast<Particle*>(data + parentIndex*m_particleStride);

				EmitParams params;
				hkVector4 direction = parentParticle->m_velocity;
				hkReal speed = direction.normalizeWithLength3();
				DiskEmissionUtil diskEmissionUtil(fracturePoints[i], 0.f, 0.f, 0.f, direction, HK_REAL_PI/6.f);
				params.m_diskEmissionUtil = &diskEmissionUtil;
				params.m_minSpeed = speed * 0.8f;
				params.m_maxSpeed = speed;
				params.m_minSpinRate = parentParticle->m_velocity(3);
				params.m_maxSpinRate = params.m_minSpinRate;
				params.m_minLifeTime = parentParticle->m_lifeTime * 0.5f;
				params.m_maxLifeTime = parentParticle->m_lifeTime;
				int numParticlesToEmit = 2 + m_pseudoRandomGenerator.getRandChar(4);
				params.m_minSize = parentParticle->m_size / hkReal(numParticlesToEmit);
				params.m_maxSize = params.m_minSize;

				emit(numParticlesToEmit, timestep, &params);

				// Since emit() might cause the particle data to be relocated in memory,
				// it is crucial to update the local particle pointer after calling emit()
				data = static_cast<char*>(m_particleData);
			}

			// Kill fractured parent particles.
			// (Note that we don't do this inside the above loop because moving particles around before all fracture points
			// have been processed might result in fracture point indices pointing to incorrect or deleted particles.)
			for(int i = 0; i < numFracturePoints; ++i)
			{
				int parentIndex = fracturePoints[i].getInt24W();
				void* parentParticle = data + parentIndex*m_particleStride;

				--numParticlesRef;
				void* lastParticle = data + numParticlesRef*m_particleStride;
				hkString::memCpy(parentParticle, lastParticle, m_particleStride);
			}
		}
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
