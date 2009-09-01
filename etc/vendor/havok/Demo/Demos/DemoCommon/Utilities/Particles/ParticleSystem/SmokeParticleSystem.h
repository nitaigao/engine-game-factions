/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SMOKE_PARTICLE_SYSTEM_H
#define HK_SMOKE_PARTICLE_SYSTEM_H

#include <Demos/DemoCommon/Utilities/Particles/ParticleSystem.h>
#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>

// A smoke particle system whose particles are affected by wind and drag and die after a certain time.
class SmokeParticleSystem : public ParticleSystem
{
	public:

		SmokeParticleSystem(int randomSeed, int particleStride = sizeof(Particle));
		virtual ~SmokeParticleSystem();

		virtual void draw();

	public:

		struct Particle
		{
			enum
			{
				POS_OFFSET = 0,
				VEL_OFFSET = 16,
				AGE_OFFSET = 32,
				LIFETIME_OFFSET = 36,
				SIZE_OFFSET = 40
			};

			hkVector4	m_position;	// angle is in .w component
			hkVector4	m_velocity;	// spin rate is in .w component
			hkReal		m_age;
			hkReal		m_lifeTime;
			hkReal		m_size;
		};

		struct EmitParams
		{
			EmitParams();	// sets defaults

			hkVector4	m_emitPosition;
			hkVector4	m_emitDirection;
			hkReal		m_minSpeed;
			hkReal		m_maxSpeed;
			hkVector4	m_attachmentVelocity;
			hkReal		m_minLifeTime;
			hkReal		m_maxLifeTime;
			hkReal		m_minSize;
			hkReal		m_maxSize;
		};

		hkVector4	m_windVelocity;
		hkVector4	m_drag;

	protected:

		virtual void initParticles(int numParticles, void* particleData, hkReal timestep, const void* emitParams);
		virtual void updateParticles(int& numParticlesRef, void* particleData, hkReal timestep);

	protected:

		hkPseudoRandomGenerator	m_pseudoRandomGenerator;
};

#endif	// HK_SMOKE_PARTICLE_SYSTEM_H

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
