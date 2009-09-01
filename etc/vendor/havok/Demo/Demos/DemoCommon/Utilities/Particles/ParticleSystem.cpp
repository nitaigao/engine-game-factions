/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Demos/DemoCommon/Utilities/Particles/ParticleSystem.h>

ParticleSystem::ParticleSystem(int particleStride)
	: m_particleStride(particleStride),
	  m_numParticles(0),
	  m_maxNumParticles(0),
	  m_particleData(HK_NULL)
{
}

ParticleSystem::~ParticleSystem()
{
	hkThreadMemory::getInstance().deallocateChunk(m_particleData, m_maxNumParticles*m_particleStride, HK_MEMORY_CLASS_DEMO);
}

int ParticleSystem::getNumParticles() const
{
	return m_numParticles;
}

const void* ParticleSystem::getParticleData() const
{
	return m_particleData;
}

void ParticleSystem::clear()
{
	m_numParticles = 0;
}

void ParticleSystem::emit(int numParticlesToEmit, hkReal timestep, const void* emitParams)
{
	if(numParticlesToEmit > 0)
	{
		int numParticlesAvailable = m_maxNumParticles - m_numParticles;
		if(numParticlesToEmit > numParticlesAvailable)
		{
			int numParticlesRequired = numParticlesToEmit - numParticlesAvailable;
			increaseCapacity(numParticlesRequired);
		}

		char* data = static_cast<char*>(m_particleData) + m_numParticles*m_particleStride;
		initParticles(numParticlesToEmit, data, timestep, emitParams);

		m_numParticles += numParticlesToEmit;
	}
}

void ParticleSystem::update(hkReal timestep)
{
	updateParticles(m_numParticles, m_particleData, timestep);
}

void ParticleSystem::draw()
{
}

void ParticleSystem::increaseCapacity(int numParticlesRequired)
{
	int max1 = m_numParticles + numParticlesRequired;
	int max2 = m_maxNumParticles * 2;
	int newMaxNumParticles = (max1 > max2) ? max1 : max2;

	changeCapacity(newMaxNumParticles);
}

void ParticleSystem::optimizeCapacity(int numFreeParticlesLeft, bool shrinkExact)
{
	int newMaxNumParticles = m_numParticles + numFreeParticlesLeft;
	if(!shrinkExact)
	{
		newMaxNumParticles = hkNextPowerOf2(newMaxNumParticles);
	}

	if(newMaxNumParticles < m_maxNumParticles)
	{
		changeCapacity(newMaxNumParticles);
	}
}

void ParticleSystem::changeCapacity(int newMaxNumParticles)
{
	char* newData = static_cast<char*>(hkThreadMemory::getInstance().allocateChunk(newMaxNumParticles*m_particleStride, HK_MEMORY_CLASS_DEMO));
	hkString::memCpy(newData, m_particleData, m_numParticles*m_particleStride);
	hkThreadMemory::getInstance().deallocateChunk(m_particleData, m_maxNumParticles*m_particleStride, HK_MEMORY_CLASS_DEMO);

	m_maxNumParticles = newMaxNumParticles;
	m_particleData = newData;
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
