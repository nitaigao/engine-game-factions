/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Demos/DemoCommon/Utilities/Particles/HkgParticleSystem/HkgDebrisParticleSystem.h>
#include <Demos/DemoCommon/Utilities/Particles/Utilities/DiskEmissionUtil.h>
#include <Demos/DemoCommon/Utilities/Particles/Utilities/ParticleUtils.h>
#include <Demos/DemoCommon/Utilities/Particles/Utilities/ParticleCollisionUtil.h>
#include <Common/Base/Container/LocalArray/hkLocalArray.h>
#include <Graphics/Common/DisplayWorld/hkgDisplayWorld.h>
#include <Graphics/Common/DisplayObject/hkgParticleDisplayObject.h>
#include <Demos/DemoCommon/Utilities/Particles/Utilities/DepthSortParticlesUtil.h>

HkgDebrisParticleSystem::HkgEmitParams::HkgEmitParams()
	: m_minSpriteIndex(0),
	  m_maxSpriteIndex(0)
{
}

HkgDebrisParticleSystem::HkgDebrisParticleSystem( int randomSeed, int flags, hkpWorld* world,
	hkDemoEnvironment* env, hkgMaterial* material, int maxNumParticlesDrawn, int particleStride )
	: DebrisParticleSystem(randomSeed, flags, world, particleStride),
	  m_depthSortEnabled(false),
	  m_demoEnvironment(env),
	  m_maxNumParticlesDrawn(maxNumParticlesDrawn)
{
	m_demoEnvironment->m_window->getContext()->lock();

	m_particleDisplayObject = hkgParticleDisplayObject::create(m_demoEnvironment->m_window->getContext());
	m_particleDisplayObject->setMaterial(material);
	m_particleDisplayObject->setRenderMode(HKG_PARTICLE_DISPLAY_POINTSPRITE);
	m_particleDisplayObject->setBlendMode(HKG_PARTICLE_BLEND_MODULATE);
	m_particleDisplayObject->setStatusFlags(m_particleDisplayObject->getStatusFlags() | HKG_DISPLAY_OBJECT_FINALRENDERPASS);
	m_particleDisplayObject->setMaxNumParticles(m_maxNumParticlesDrawn, true);
	m_demoEnvironment->m_displayWorld->addDisplayObject(m_particleDisplayObject);

	m_demoEnvironment->m_window->getContext()->unlock();
}

HkgDebrisParticleSystem::~HkgDebrisParticleSystem()
{
	m_demoEnvironment->m_window->getContext()->lock();

	m_demoEnvironment->m_displayWorld->removeDisplayObject(m_particleDisplayObject);
	m_particleDisplayObject->release(); // HKG upon remove from world passes back the ref for the object, instead of decr it. (HKG quirk)
	m_particleDisplayObject->release(); // our ref

	m_demoEnvironment->m_window->getContext()->unlock();
}

void HkgDebrisParticleSystem::clear()
{
	DebrisParticleSystem::clear();

	m_particleDisplayObject->setNumParticles(0);
}

void HkgDebrisParticleSystem::draw()
{
	m_demoEnvironment->m_window->getContext()->lock();

	// Limit the number of particles drawn to m_maxNumParticlesDrawn
	int numParticles = (m_numParticles > m_maxNumParticlesDrawn) ? m_maxNumParticlesDrawn : m_numParticles;
	m_particleDisplayObject->setNumParticles(numParticles);

	const HkgParticle* particles = static_cast<const HkgParticle*>(m_particleData);

	if(!m_depthSortEnabled)
	{
		for(int i = 0; i < numParticles; ++i)
		{
			const HkgParticle& p = particles[i];

			m_particleDisplayObject->setPosition((float*)&p.m_position, i);

			float userData[4] = { p.m_spriteIndex, p.m_size, p.m_age/p.m_lifeTime };
			m_particleDisplayObject->setUserData(userData, i);
		}
	}
	else if(numParticles != 0)
	{
		float camDir[3];
		m_demoEnvironment->m_window->getCurrentViewport()->getCamera()->getDir(camDir);
		hkVector4 sortDir(camDir[0], camDir[1], camDir[2]);

		const char* posPtr = static_cast<const char*>(m_particleData) + HkgParticle::POS_OFFSET;
		DepthSortParticlesUtil sortUtil(numParticles, posPtr, m_particleStride, sortDir);

		int numDone = 0;
		for(int i = numParticles-1; i >= 0; --i)
		{
			const HkgParticle& p = particles[sortUtil.getSortedIndex(i)];

			m_particleDisplayObject->setPosition((float*)&p.m_position, numDone);

			float userData[4] = { p.m_spriteIndex, p.m_size, p.m_age/p.m_lifeTime };
			m_particleDisplayObject->setUserData(userData, numDone);

			++numDone;
		}
	}

	m_demoEnvironment->m_window->getContext()->unlock();
}

void HkgDebrisParticleSystem::initParticles(int numParticles, void* particleData, hkReal timestep, const void* emitParams)
{
	DebrisParticleSystem::initParticles(numParticles, particleData, timestep, emitParams);

	HK_ASSERT(0x1acb8069, emitParams);
	const HkgEmitParams* params = static_cast<const HkgEmitParams*>(emitParams);

	HkgParticle* particles = static_cast<HkgParticle*>(particleData);
	int range = params->m_maxSpriteIndex - params->m_minSpriteIndex + 1;
	for(int i = 0; i < numParticles; ++i)
	{
		particles[i].m_spriteIndex = static_cast<hkReal>(params->m_minSpriteIndex + m_pseudoRandomGenerator.getRandChar(range));
	}
}

void HkgDebrisParticleSystem::updateParticles(int& numParticlesRef, void* particleData, hkReal timestep)
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
				HkgParticle* parentParticle = reinterpret_cast<HkgParticle*>(data + parentIndex*m_particleStride);

				HkgEmitParams params;
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
				params.m_minSpriteIndex = static_cast<hkUint8>(parentParticle->m_spriteIndex);
				params.m_maxSpriteIndex = params.m_minSpriteIndex;
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
