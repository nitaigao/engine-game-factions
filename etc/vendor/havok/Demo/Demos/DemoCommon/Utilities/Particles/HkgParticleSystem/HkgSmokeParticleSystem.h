/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_HKG_SMOKE_PARTICLE_SYSTEM_H
#define HK_HKG_SMOKE_PARTICLE_SYSTEM_H

#include <Demos/DemoCommon/Utilities/Particles/ParticleSystem/SmokeParticleSystem.h>

class hkDemoEnvironment;
class hkgParticleDisplayObject;

// A smoke particle system that uses HKG for rendering.
// Note that this class imposes a cap on the number of particles, even though SmokeParticleSystem does not.
// Depth-sorting is optional and is disabled by default.
class HkgSmokeParticleSystem : public SmokeParticleSystem
{
	public:

		HkgSmokeParticleSystem( int randomSeed, hkDemoEnvironment* env, hkgMaterial* material,
			int maxNumParticlesDrawn, int particleStride = sizeof(HkgParticle) );

		virtual ~HkgSmokeParticleSystem();

		virtual void clear();

		virtual void draw();

	public:

		struct HkgParticle : public Particle
		{
			hkReal	m_spriteIndex;
		};

		struct HkgEmitParams : public EmitParams
		{
			HkgEmitParams();	// sets defaults

			hkUint8	m_minSpriteIndex;
			hkUint8	m_maxSpriteIndex;
		};

		hkBool	m_depthSortEnabled;

	protected:

		virtual void initParticles(int numParticles, void* particleData, hkReal timestep, const void* emitParams);

	protected:

		hkDemoEnvironment*			m_demoEnvironment;
		hkgParticleDisplayObject*	m_particleDisplayObject;
		int							m_maxNumParticlesDrawn;
};

#endif	// HK_HKG_SMOKE_PARTICLE_SYSTEM_H

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
