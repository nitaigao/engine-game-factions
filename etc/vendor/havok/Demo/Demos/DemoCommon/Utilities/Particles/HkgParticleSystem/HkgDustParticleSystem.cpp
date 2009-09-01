/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Demos/DemoCommon/Utilities/Particles/HkgParticleSystem/HkgDustParticleSystem.h>
#include <Graphics/Common/DisplayWorld/hkgDisplayWorld.h>
#include <Graphics/Common/DisplayObject/hkgParticleDisplayObject.h>
#include <Demos/DemoCommon/Utilities/Particles/Utilities/DepthSortParticlesUtil.h>

HkgDustParticleSystem::HkgDustParticleSystem( int randomSeed, hkDemoEnvironment* env,
	hkgMaterial* material, int maxNumParticlesDrawn, int particleStride )
	: DustParticleSystem(randomSeed, particleStride),
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

HkgDustParticleSystem::~HkgDustParticleSystem()
{
	m_demoEnvironment->m_window->getContext()->lock();

	m_demoEnvironment->m_displayWorld->removeDisplayObject(m_particleDisplayObject);
	m_particleDisplayObject->release(); // HKG upon remove from world passes back the ref for the object, instead of decr it. (HKG quirk)
	m_particleDisplayObject->release(); // our ref

	m_demoEnvironment->m_window->getContext()->unlock();
}

void HkgDustParticleSystem::clear()
{
	DustParticleSystem::clear();

	m_particleDisplayObject->setNumParticles(0);
}

void HkgDustParticleSystem::draw()
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

			float userData[4] = { p.m_spriteIndex, p.m_size, p.m_age/p.m_lifeTime, p.m_textureCoord };
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

			float userData[4] = { p.m_spriteIndex, p.m_size, p.m_age/p.m_lifeTime, p.m_textureCoord };
			m_particleDisplayObject->setUserData(userData, numDone);

			++numDone;
		}
	}

	m_demoEnvironment->m_window->getContext()->unlock();
}

void HkgDustParticleSystem::initParticles(int numParticles, void* particleData, hkReal timestep, const void* emitParams)
{
	DustParticleSystem::initParticles(numParticles, particleData, timestep, emitParams);

	HkgParticle* particles = static_cast<HkgParticle*>(particleData);
	for(int i = 0; i < numParticles; ++i)
	{
		particles[i].m_textureCoord = m_pseudoRandomGenerator.getRandReal01();
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
