/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_EXPLOSION_PARTICLE_SYSTEM_H
#define HK_EXPLOSION_PARTICLE_SYSTEM_H

#include <Demos/DemoCommon/Utilities/Particles/ParticleSystem.h>
#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>

// A simple explosion particle system which supports spherical emission or oriented hemispherical emission.
// EmitParams::m_planeNormal should be set appropriately so that the particles spin outwards from the
// explosion source (i.e. counterclockwise if moving leftwards and clockwise if moving rightwards).
// The particles are affected by gravity and drag and die after a certain time.
class ExplosionParticleSystem : public ParticleSystem
{
	public:

		ExplosionParticleSystem(int randomSeed, int particleStride = sizeof(Particle));
		virtual ~ExplosionParticleSystem();

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

			hkVector4	m_position;		// center of explosion
			hkVector4	m_direction;	// direction for hemispherical emission (ignored if m_useDirection is false)
			hkVector4	m_planeNormal;	// normal of vertical plane which goes through the camera position and explosion center
			hkReal		m_minSpeed;
			hkReal		m_maxSpeed;
			hkReal		m_minLifeTime;
			hkReal		m_maxLifeTime;
			hkReal		m_minSize;
			hkReal		m_maxSize;
			hkBool		m_useDirection;	// chooses between spherical emission (if false) and hemispherical emission (if true)
		};

	public:

		hkVector4	m_acceleration;
		hkVector4	m_drag;

	protected:

		virtual void initParticles(int numParticles, void* particleData, hkReal timestep, const void* emitParams);
		virtual void updateParticles(int& numParticlesRef, void* particleData, hkReal timestep);

	protected:

		hkPseudoRandomGenerator	m_pseudoRandomGenerator;
};

#endif	// HK_EXPLOSION_PARTICLE_SYSTEM_H

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
