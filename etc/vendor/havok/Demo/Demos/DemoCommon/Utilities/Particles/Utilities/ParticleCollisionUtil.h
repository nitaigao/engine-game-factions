/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_PARTICLE_COLLISION_UTIL_H
#define HK_PARTICLE_COLLISION_UTIL_H

class hkpWorld;
class hkpSimpleShapePhantom;
class hkPseudoRandomGenerator;

class ParticleCollisionUtil
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO, ParticleCollisionUtil);

		ParticleCollisionUtil(hkpWorld* world, hkReal particleRadius = 0.0001f);
		~ParticleCollisionUtil();

		// Advances the positions and velocities of particles over a time step while processing collisions.
		// Collision detection is performed using a shared sphere phantom which is repositioned for each particle.
		// Collision resolution is done by modifying the particle velocity while taking friction, restitution and
		// the velocity of the collided object into account.
		void moveParticles( int numParticles, char* posPtr, char* velPtr, int particleStride, hkReal timestep,
			const hkVector4& acceleration, hkReal friction, hkReal restitution );

		// This function behaves the same as above, but in addition, every time a particle collision occurs,
		// we evaluate some criteria to decide if the collision should be recorded in the fracturePoints array.
		// The recorded information is the collision point (a hkVector4) and the index of the colliding particle
		// (encoded as an integer in the .w component of the hkVector4). This index is required if we wish to
		// kill the colliding particle upon collision. These fracture points can then be used as positions from
		// which to emit further particles, giving the impression of particles fracturing upon collision.
		// The criteria used to decide if a collision should result in fracture are:
		//  - the number of fracture points added so far is less than maxFractures
		//  - the particle size is greater than sizeThreshold (avoids fracturing into too fine a piece)
		//  - the relative speed at the point of collision is greater than relativeSpeedThreshold (avoids
		//    fracturing for weak collisions)
		//  - a random number is less than fractureProbability (stochastic processes tend to look better)
		void moveParticlesAndRecordFractures( int numParticles, char* posPtr, char* velPtr, const char* sizePtr,
			int particleStride, hkReal timestep, const hkVector4& acceleration, hkReal friction, hkReal restitution,
			hkArray<hkVector4>& fracturePoints, int maxFractures, hkReal sizeThreshold, hkReal relativeSpeedThreshold,
			hkReal fractureProbability, hkPseudoRandomGenerator* pseudoRandomGenerator );

	private:

		hkpWorld*				m_world;
		hkpSimpleShapePhantom*	m_phantom;
		hkReal					m_particleRadius;
};

#endif	// HK_PARTICLE_COLLISION_UTIL_H

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
