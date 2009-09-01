/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Demos/DemoCommon/Utilities/Particles/ParticleSystem/SmokeParticleSystem.h>
#include <Demos/DemoCommon/Utilities/Particles/Utilities/ParticleUtils.h>
#include <Common/Visualize/hkDebugDisplay.h>

SmokeParticleSystem::EmitParams::EmitParams()
	: m_emitPosition(hkVector4::getZero()),
	  m_emitDirection(hkVector4(0.f, 1.f, 0.f)),
	  m_minSpeed(1.9f),
	  m_maxSpeed(2.1f),
	  m_attachmentVelocity(hkVector4::getZero()),
	  m_minLifeTime(2.5f),
	  m_maxLifeTime(5.f),
	  m_minSize(0.5f),
	  m_maxSize(1.5f)
{
}

SmokeParticleSystem::SmokeParticleSystem(int randomSeed, int particleStride)
	: ParticleSystem(particleStride),
	  m_windVelocity(0.f, 0.f, 0.f),
	  m_drag(0.1f, 0.1f, 0.1f, 0.f),
	  m_pseudoRandomGenerator(randomSeed)
{
}

SmokeParticleSystem::~SmokeParticleSystem()
{
}

void SmokeParticleSystem::draw()
{
	const char* data = static_cast<const char*>(m_particleData);

	ParticleUtils::debugDrawParticles(m_numParticles, data+Particle::POS_OFFSET, m_particleStride, 0.025f, hkColor::RED);
}

void SmokeParticleSystem::initParticles(int numParticles, void* particleData, hkReal timestep, const void* emitParams)
{
	HK_ASSERT(0x4582ee85, emitParams);
	const EmitParams* params = static_cast<const EmitParams*>(emitParams);

	for(int i = 0; i < numParticles; ++i)
	{
		Particle& p = *reinterpret_cast<Particle*>(static_cast<char*>(particleData) + i*m_particleStride);

		p.m_position = params->m_emitPosition;
		p.m_position(3) = m_pseudoRandomGenerator.getRandReal01() * 2.f * HK_REAL_PI;
		p.m_velocity = params->m_emitDirection;
		p.m_velocity.mul4(m_pseudoRandomGenerator.getRandRange(params->m_minSpeed, params->m_maxSpeed));
		p.m_velocity.add4(params->m_attachmentVelocity);
		p.m_velocity(3) = m_pseudoRandomGenerator.getRandRange(-30.f*HK_REAL_DEG_TO_RAD, 30.f*HK_REAL_DEG_TO_RAD);
		p.m_lifeTime = m_pseudoRandomGenerator.getRandRange(params->m_minLifeTime, params->m_maxLifeTime);
		p.m_age = m_pseudoRandomGenerator.getRandReal01() * timestep;
		p.m_size = m_pseudoRandomGenerator.getRandRange(params->m_minSize, params->m_maxSize);

		// Particle positions are initially integrated by a random amount to make it seem as
		// though they are emitted continuously over time instead of at discrete time steps.
		p.m_position.addMul4(p.m_age, p.m_velocity);
	}
}

void SmokeParticleSystem::updateParticles(int& numParticlesRef, void* particleData, hkReal timestep)
{
	char* data = static_cast<char*>(particleData);

	ParticleUtils::ageParticles(numParticlesRef, data, data+Particle::AGE_OFFSET, data+Particle::LIFETIME_OFFSET, m_particleStride, timestep);

	for(int i = 0; i < numParticlesRef; ++i)
	{
		Particle& p = *reinterpret_cast<Particle*>(data + i*m_particleStride);

		// Compute acceleration.
		hkVector4 acceleration;
		{
			hkVector4 relVel;
			relVel.setSub4(m_windVelocity, p.m_velocity);
			acceleration.setMul4(relVel, m_drag);
		}

		p.m_velocity.addMul4(timestep, acceleration);
		p.m_position.addMul4(timestep, p.m_velocity);
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
