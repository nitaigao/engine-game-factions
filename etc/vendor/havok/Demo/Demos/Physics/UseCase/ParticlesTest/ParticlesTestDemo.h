/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_PARTICLES_TEST_DEMO_H
#define HK_PARTICLES_TEST_DEMO_H

#include <Demos/DemoCommon/DemoFramework/hkDefaultPhysicsDemo.h>
#include <Demos/DemoCommon/Utilities/Particles/Utilities/ContinuousEmissionUtil.h>
#include <Demos/DemoCommon/Utilities/Particles/Utilities/ChimneyEmissionUtil.h>

class HkgSmokeParticleSystem;
class HkgDebrisParticleSystem;
class HkgSparksParticleSystem;
class HkgDustParticleSystem;
class HkgExplosionParticleSystem;
class ScrapeParticleListener;

class ParticlesTestDemo : public hkDefaultPhysicsDemo
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO);

		ParticlesTestDemo(hkDemoEnvironment* env);
		~ParticlesTestDemo();

		hkDemo::Result stepDemo();

		int resetParticles();
		int emissionAtMouse(hkBool32 isDust);

	private:

		HkgSmokeParticleSystem*		m_smokeParticleSystem1;
		HkgSmokeParticleSystem*		m_smokeParticleSystem2;
		ContinuousEmissionUtil		m_smokeContinuousEmissionUtil;
		ChimneyEmissionUtil			m_smokeChimneyEmissionUtil1;
		ChimneyEmissionUtil			m_smokeChimneyEmissionUtil2;
		hkpRigidBody*				m_smokeBox;

		HkgDebrisParticleSystem*	m_debrisParticleSystem1;
		HkgDebrisParticleSystem*	m_debrisParticleSystem2;
		ContinuousEmissionUtil		m_debrisContinuousEmissionUtil;

		HkgSparksParticleSystem*	m_sparksParticleSystem;
		ContinuousEmissionUtil		m_sparksContinuousEmissionUtil;
		ScrapeParticleListener*		m_sparksListener;
		hkpRigidBody*				m_sparksBox;

		HkgDustParticleSystem*		m_dustParticleSystem;

		HkgExplosionParticleSystem*	m_explosionParticleSystem;
};

#endif // HK_PARTICLES_TEST_DEMO_H

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
