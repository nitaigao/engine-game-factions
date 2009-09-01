/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SPARKS_PARTICLE_SYSTEM_H
#define HK_SPARKS_PARTICLE_SYSTEM_H

#include <Demos/DemoCommon/Utilities/Particles/ParticleSystem.h>
#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>

class DiskEmissionUtil;

// A sparks particle system whose particles are affected by gravity and die after a certain time.
// Raycast-based collision handling can optionally be enabled.
class SparksParticleSystem : public ParticleSystem
{
	public:

		enum Flags
		{
			NO_FLAGS = 0,
			ENABLE_COLLISIONS = 1
		};

		SparksParticleSystem(int randomSeed, int flags, hkpWorld* world, int particleStride = sizeof(Particle));
		virtual ~SparksParticleSystem();

		virtual void draw();

	public:

		struct Particle
		{
			enum
			{
				POS_OFFSET = 0,
				VEL_OFFSET = 16,
				AGE_OFFSET = 32,
				LIFETIME_OFFSET = 36
			};

			hkVector4	m_position;
			hkVector4	m_velocity;
			hkReal		m_age;
			hkReal		m_lifeTime;
		};

		struct EmitParams
		{
			EmitParams();	// sets defaults

			DiskEmissionUtil*	m_diskEmissionUtil;
			hkReal				m_minSpeed;
			hkReal				m_maxSpeed;
			hkReal				m_minLifeTime;
			hkReal				m_maxLifeTime;
		};

	public:

		hkVector4	m_acceleration;

		// The following are only used if collisions are enabled.
		hkReal		m_friction;
		hkReal		m_restitution;

	protected:

		virtual void initParticles(int numParticles, void* particleData, hkReal timestep, const void* emitParams);
		virtual void updateParticles(int& numParticlesRef, void* particleData, hkReal timestep);

	protected:

		hkPseudoRandomGenerator	m_pseudoRandomGenerator;
		hkBool					m_enableCollisions;
		hkpWorld*				m_world;
};

#endif	// HK_SPARKS_PARTICLE_SYSTEM_H

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
