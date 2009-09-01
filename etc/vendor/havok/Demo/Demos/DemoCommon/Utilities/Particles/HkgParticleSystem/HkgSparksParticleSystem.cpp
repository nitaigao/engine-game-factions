/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Demos/DemoCommon/Utilities/Particles/HkgParticleSystem/HkgSparksParticleSystem.h>
#include <Graphics/Common/DisplayWorld/hkgDisplayWorld.h>
#include <Graphics/Common/DisplayObject/hkgParticleDisplayObject.h>

HkgSparksParticleSystem::HkgSparksParticleSystem(int randomSeed, int flags, hkpWorld* world,
	hkDemoEnvironment* env, hkgMaterial* material, int maxNumParticlesDrawn, int particleStride )
	: SparksParticleSystem(randomSeed, flags, world, particleStride),
	  m_demoEnvironment(env),
	  m_maxNumParticlesDrawn(maxNumParticlesDrawn)
{
	m_demoEnvironment->m_window->getContext()->lock();

	m_particleDisplayObject = hkgParticleDisplayObject::create(m_demoEnvironment->m_window->getContext());
	m_particleDisplayObject->setMaterial(material);
	m_particleDisplayObject->setRenderMode(HKG_PARTICLE_DISPLAY_POINTSPRITE);
	m_particleDisplayObject->setBlendMode(HKG_PARTICLE_BLEND_ADDITIVE);
	m_particleDisplayObject->setStatusFlags(m_particleDisplayObject->getStatusFlags() | HKG_DISPLAY_OBJECT_FINALRENDERPASS);
	m_particleDisplayObject->setMaxNumParticles(m_maxNumParticlesDrawn, true);
	m_demoEnvironment->m_displayWorld->addDisplayObject(m_particleDisplayObject);

	m_demoEnvironment->m_window->getContext()->unlock();
}

HkgSparksParticleSystem::~HkgSparksParticleSystem()
{
	m_demoEnvironment->m_window->getContext()->lock();

	m_demoEnvironment->m_displayWorld->removeDisplayObject(m_particleDisplayObject);
	m_particleDisplayObject->release(); // HKG upon remove from world passes back the ref for the object, instead of decr it. (HKG quirk)
	m_particleDisplayObject->release(); // our ref

	m_demoEnvironment->m_window->getContext()->unlock();
}

void HkgSparksParticleSystem::clear()
{
	SparksParticleSystem::clear();

	m_particleDisplayObject->setNumParticles(0);
}

void HkgSparksParticleSystem::draw()
{
	m_demoEnvironment->m_window->getContext()->lock();

	// Limit the number of particles drawn to m_maxNumParticlesDrawn
	int numParticles = (m_numParticles > m_maxNumParticlesDrawn) ? m_maxNumParticlesDrawn : m_numParticles;
	m_particleDisplayObject->setNumParticles(numParticles);

	const Particle* particles = static_cast<const Particle*>(m_particleData);

	for(int i = 0; i < numParticles; ++i)
	{
		const Particle& p = particles[i];

		m_particleDisplayObject->setPosition((float*)&p.m_position, i);

		hkVector4 userData = p.m_velocity;
		userData(3) = p.m_age / p.m_lifeTime;
		m_particleDisplayObject->setUserData((float*)&userData, i);
	}

	m_demoEnvironment->m_window->getContext()->unlock();
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
