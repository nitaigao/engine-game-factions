/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Demos/DemoCommon/Utilities/Particles/ParticleSystem/ExplosionParticleSystem.h>
#include <Demos/DemoCommon/Utilities/Particles/Utilities/ParticleUtils.h>
#include <Common/Visualize/hkDebugDisplay.h>

ExplosionParticleSystem::EmitParams::EmitParams()
	: m_position(hkVector4::getZero()),
	  m_direction(hkVector4(0.f, 1.f, 0.f)),
	  m_planeNormal(hkVector4::getZero()),
	  m_minSpeed(20.f),
	  m_maxSpeed(30.f),
	  m_minLifeTime(0.4f),
	  m_maxLifeTime(4.1f),
	  m_minSize(37.5f),
	  m_maxSize(52.5f),
	  m_useDirection(false)
{
}

ExplosionParticleSystem::ExplosionParticleSystem(int randomSeed, int particleStride)
	: ParticleSystem(particleStride),
	  m_acceleration(0.f, -9.81f, 0.f),
	  m_drag(-1.f, -1.f, -1.f, 0.f),
	  m_pseudoRandomGenerator(randomSeed)
{
}

ExplosionParticleSystem::~ExplosionParticleSystem()
{
}

void ExplosionParticleSystem::draw()
{
	const char* data = static_cast<const char*>(m_particleData);

	ParticleUtils::debugDrawParticles(m_numParticles, data+Particle::POS_OFFSET, m_particleStride, 0.025f, hkColor::RED);
}

void ExplosionParticleSystem::initParticles(int numParticles, void* particleData, hkReal timestep, const void* emitParams)
{
	HK_ASSERT(0x6750a79f, emitParams);
	const EmitParams* params = static_cast<const EmitParams*>(emitParams);

	for(int i = 0; i < numParticles; ++i)
	{
		Particle& p = *reinterpret_cast<Particle*>(static_cast<char*>(particleData) + i*m_particleStride);

		p.m_position = params->m_position;
		p.m_position(3) = m_pseudoRandomGenerator.getRandReal01() * 2.f * HK_REAL_PI;

		// Uniformly sample a particle emission direction from the sphere
		// (see http://mathworld.wolfram.com/SpherePointPicking.html)
		hkReal theta = m_pseudoRandomGenerator.getRandReal01() * 2.f * HK_REAL_PI;
		hkReal u = m_pseudoRandomGenerator.getRandReal11();
		hkReal s = hkMath::sqrt(1.f - u*u);
		p.m_velocity.set(s*cosf(theta), u, s*sinf(theta));

		// Force the particle to be emitted from the hemisphere oriented by m_direction
		hkReal speed = m_pseudoRandomGenerator.getRandRange(params->m_minSpeed, params->m_maxSpeed);
		if(params->m_useDirection && p.m_velocity.dot3(params->m_direction) < 0.f)
		{
			speed = -speed;
		}
		p.m_velocity.mul4(speed);

		// Set the spin direction based on whether the particle is moving towards the left or right.
		hkReal spinRate = m_pseudoRandomGenerator.getRandRange(5.f*HK_REAL_DEG_TO_RAD, 30.f*HK_REAL_DEG_TO_RAD);
		if(params->m_planeNormal.dot3(p.m_velocity) > 0.f)
			spinRate = -spinRate;
		p.m_velocity(3) = spinRate;

		p.m_lifeTime = m_pseudoRandomGenerator.getRandRange(params->m_minLifeTime, params->m_maxLifeTime);
		p.m_age = m_pseudoRandomGenerator.getRandReal01() * timestep;
		p.m_size = m_pseudoRandomGenerator.getRandRange(params->m_minSize, params->m_maxSize);

		// Particle positions are initially integrated by a random amount to make it seem as
		// though they are emitted continuously over time instead of at discrete time steps.
		p.m_position.addMul4(p.m_age, p.m_velocity);
	}
}

void ExplosionParticleSystem::updateParticles(int& numParticlesRef, void* particleData, hkReal timestep)
{
	char* data = static_cast<char*>(particleData);

	ParticleUtils::ageParticles(numParticlesRef, data, data+Particle::AGE_OFFSET, data+Particle::LIFETIME_OFFSET, m_particleStride, timestep);

	for(int i = 0; i < numParticlesRef; ++i)
	{
		Particle& p = *reinterpret_cast<Particle*>(data + i*m_particleStride);

		hkVector4 acceleration;
		acceleration.setAddMul4(m_acceleration, m_drag, p.m_velocity);

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
