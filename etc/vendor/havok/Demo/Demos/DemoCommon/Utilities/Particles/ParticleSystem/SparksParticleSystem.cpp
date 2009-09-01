/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Demos/DemoCommon/Utilities/Particles/ParticleSystem/SparksParticleSystem.h>
#include <Demos/DemoCommon/Utilities/Particles/Utilities/DiskEmissionUtil.h>
#include <Demos/DemoCommon/Utilities/Particles/Utilities/ParticleUtils.h>
#include <Common/Visualize/hkDebugDisplay.h>

SparksParticleSystem::EmitParams::EmitParams()
	: m_diskEmissionUtil(HK_NULL),
	  m_minSpeed(0.f),
	  m_maxSpeed(0.f),
	  m_minLifeTime(1.f),
	  m_maxLifeTime(4.f)
{
}

SparksParticleSystem::SparksParticleSystem(int randomSeed, int flags, hkpWorld* world, int particleStride)
	: ParticleSystem(particleStride),
	  m_acceleration(0.f, -9.81f, 0.f),
	  m_friction(0.5f),
	  m_restitution(0.5f),
	  m_pseudoRandomGenerator(randomSeed),
	  m_world(world)
{
	m_enableCollisions = (flags & ENABLE_COLLISIONS) != 0;
}

SparksParticleSystem::~SparksParticleSystem()
{
}

void SparksParticleSystem::draw()
{
	const char* data = static_cast<const char*>(m_particleData);

	ParticleUtils::debugDrawParticles(m_numParticles, data+Particle::POS_OFFSET, m_particleStride, 0.025f, hkColor::RED);
}

void SparksParticleSystem::initParticles(int numParticles, void* particleData, hkReal timestep, const void* emitParams)
{
	HK_ASSERT(0x54521c04, emitParams);
	const EmitParams* params = static_cast<const EmitParams*>(emitParams);
	HK_ASSERT(0x5773de1f, params->m_diskEmissionUtil);

	for(int i = 0; i < numParticles; ++i)
	{
		Particle& p = *reinterpret_cast<Particle*>(static_cast<char*>(particleData) + i*m_particleStride);

		params->m_diskEmissionUtil->samplePosition(p.m_position, &m_pseudoRandomGenerator);
		params->m_diskEmissionUtil->sampleDirection(p.m_velocity, &m_pseudoRandomGenerator);
		p.m_velocity.mul4(m_pseudoRandomGenerator.getRandRange(params->m_minSpeed, params->m_maxSpeed));
		p.m_lifeTime = m_pseudoRandomGenerator.getRandRange(params->m_minLifeTime, params->m_maxLifeTime);
		p.m_age = m_pseudoRandomGenerator.getRandReal01() * timestep;

		// Particle positions are initially integrated by a random amount to make it seem as
		// though they are emitted continuously over time instead of at discrete time steps.
		p.m_position.addMul4(p.m_age, p.m_velocity);
	}
}

void SparksParticleSystem::updateParticles(int& numParticlesRef, void* particleData, hkReal timestep)
{
	char* data = static_cast<char*>(particleData);

	ParticleUtils::ageParticles(numParticlesRef, data, data+Particle::AGE_OFFSET, data+Particle::LIFETIME_OFFSET, m_particleStride, timestep);

	if(!m_enableCollisions)
	{
		ParticleUtils::moveParticles( numParticlesRef, data+Particle::POS_OFFSET, data+Particle::VEL_OFFSET,
			m_particleStride, timestep, m_acceleration );
	}
	else
	{
		ParticleUtils::moveParticlesWithRaycastCollisions( numParticlesRef, data+Particle::POS_OFFSET, data+Particle::VEL_OFFSET,
			m_particleStride, timestep, m_acceleration, m_friction, m_restitution, m_world );
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
