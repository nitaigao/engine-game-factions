/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Demos/DemoCommon/Utilities/Particles/ParticleSystem/DustParticleSystem.h>
#include <Demos/DemoCommon/Utilities/Particles/Utilities/ParticleUtils.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>
#include <Common/Visualize/hkDebugDisplay.h>

DustParticleSystem::EmitParams::EmitParams()
	: m_emitPosition(hkVector4::getZero()),
	  m_emitDirection(hkVector4(0.f, 1.f, 0.f)),
	  m_planeNormal(hkVector4::getZero()),
	  m_speedScale(1.f),
	  m_minSpinRate(-90.f*HK_REAL_DEG_TO_RAD),
	  m_maxSpinRate(-120.f*HK_REAL_DEG_TO_RAD),
	  m_minLifeTime(2.f),
	  m_maxLifeTime(3.5f),
	  m_minSize(0.3f),
	  m_maxSize(0.5f)
{
}

DustParticleSystem::DustParticleSystem(int randomSeed, int particleStride)
	: ParticleSystem(particleStride),
	  m_acceleration(0.f, -0.1f, 0.f),
	  m_drag(-0.8f, -0.8f, -0.8f, 0.f),
	  m_pseudoRandomGenerator(randomSeed)
{
}

DustParticleSystem::~DustParticleSystem()
{
}

void DustParticleSystem::draw()
{
	const char* data = static_cast<const char*>(m_particleData);

	ParticleUtils::debugDrawParticles(m_numParticles, data+Particle::POS_OFFSET, m_particleStride, 0.025f, hkColor::RED);
}

void DustParticleSystem::initParticles(int numParticles, void* particleData, hkReal timestep, const void* emitParams)
{
	HK_ASSERT(0x6f68d095, emitParams);
	const EmitParams* params = static_cast<const EmitParams*>(emitParams);

	hkMatrix3 orthonormalBasis;
	hkVector4Util::buildOrthonormal(params->m_emitDirection, orthonormalBasis);

	const hkReal minRadiusFractions[4] = { 2.f, 0.4f, 0.4f, 0.2f };
	const hkReal maxRadiusFractions[4] = { 3.f, 2.f, 2.f, 1.f };
	const hkReal outOfPlaneVarianceScales[4] = { 0.01f, 0.1f, 0.1f, 0.05f };

	for(int i = 0; i < numParticles; ++i)
	{
		Particle& p = *reinterpret_cast<Particle*>(static_cast<char*>(particleData) + i*m_particleStride);

		p.m_position = params->m_emitPosition;
		p.m_position(3) = m_pseudoRandomGenerator.getRandReal01() * 2.f * HK_REAL_PI;

		// Choose a sprite for the particle.
		int spriteIndex;
		hkReal rnd = m_pseudoRandomGenerator.getRandReal01();
		if(rnd < 0.25f)
		{
			spriteIndex = 1;
		}
		else if(rnd < 0.5f)
		{
			spriteIndex = 2;
		}
		else if(rnd < 0.7f)
		{
			spriteIndex = 3;
		}
		else
		{
			spriteIndex = 0;
		}

		hkReal radius =  m_pseudoRandomGenerator.getRandRange(minRadiusFractions[spriteIndex], maxRadiusFractions[spriteIndex]) * params->m_speedScale;
		hkReal theta = m_pseudoRandomGenerator.getRandReal01() * 2.f * HK_REAL_PI;
		hkReal ringX = radius * hkMath::cos(theta);
		hkReal ringY = radius * hkMath::sin(theta);
		hkReal outOfPlaneVariance = outOfPlaneVarianceScales[spriteIndex] * params->m_speedScale;
		hkVector4 localVelocity(m_pseudoRandomGenerator.getRandRange(-outOfPlaneVariance, outOfPlaneVariance), ringY, ringX);
		orthonormalBasis.multiplyVector(localVelocity, p.m_velocity);

		// Set the spin direction based on whether the particle is moving towards the left or right.
		hkReal spinRate = m_pseudoRandomGenerator.getRandRange(params->m_minSpinRate, params->m_maxSpinRate);
		if(params->m_planeNormal.dot3(p.m_velocity) > 0.f)
			spinRate = -spinRate;
		p.m_velocity(3) = spinRate;

		p.m_lifeTime = m_pseudoRandomGenerator.getRandRange(params->m_minLifeTime, params->m_maxLifeTime);
		p.m_age = m_pseudoRandomGenerator.getRandReal01() * timestep;
		p.m_size = m_pseudoRandomGenerator.getRandRange(params->m_minSize, params->m_maxSize);
		p.m_spriteIndex = static_cast<hkReal>(spriteIndex);

		// Particle positions are initially integrated by a random amount to make it seem as
		// though they are emitted continuously over time instead of at discrete time steps.
		p.m_position.addMul4(p.m_age, p.m_velocity);
	}
}

void DustParticleSystem::updateParticles(int& numParticlesRef, void* particleData, hkReal timestep)
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
