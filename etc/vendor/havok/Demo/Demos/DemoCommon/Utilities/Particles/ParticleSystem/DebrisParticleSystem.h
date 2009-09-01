/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_DEBRIS_PARTICLE_SYSTEM_H
#define HK_DEBRIS_PARTICLE_SYSTEM_H

#include <Demos/DemoCommon/Utilities/Particles/ParticleSystem.h>
#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>

class DiskEmissionUtil;
class ParticleCollisionUtil;

// A debris particle system whose particles are affected by gravity and die after a certain time.
// Collision handling and fracturing can optionally be enabled.
class DebrisParticleSystem : public ParticleSystem
{
	public:

		enum Flags
		{
			NO_FLAGS = 0,
			ENABLE_COLLISIONS = 1,
			ENABLE_FRACTURES = 2
		};

		DebrisParticleSystem(int randomSeed, int flags, hkpWorld* world, int particleStride = sizeof(Particle));
		virtual ~DebrisParticleSystem();

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
			hkVector4	m_velocity;	// spin rate is .w component
			hkReal		m_age;
			hkReal		m_lifeTime;
			hkReal		m_size;
		};

		struct EmitParams
		{
			EmitParams();	// sets defaults

			DiskEmissionUtil*	m_diskEmissionUtil;
			hkReal				m_minSpeed;
			hkReal				m_maxSpeed;
			hkReal				m_minSpinRate;
			hkReal				m_maxSpinRate;
			hkReal				m_minLifeTime;
			hkReal				m_maxLifeTime;
			hkReal				m_minSize;
			hkReal				m_maxSize;
		};

	public:

		hkVector4	m_acceleration;

		// The following are only used if collisions are enabled.
		hkReal		m_friction;
		hkReal		m_restitution;

		// The following are only used if fractures (and collisions) are enabled.
		int			m_maxFractures;
		hkReal		m_sizeThreshold;
		hkReal		m_relativeSpeedThreshold;
		hkReal		m_fractureProbability;

	protected:

		virtual void initParticles(int numParticles, void* particleData, hkReal timestep, const void* emitParams);
		virtual void updateParticles(int& numParticlesRef, void* particleData, hkReal timestep);

	protected:

		hkPseudoRandomGenerator	m_pseudoRandomGenerator;
		ParticleCollisionUtil*	m_collisionUtil;
		hkBool					m_enableFractures;
};

#endif	// HK_DEBRIS_PARTICLE_SYSTEM_H

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
