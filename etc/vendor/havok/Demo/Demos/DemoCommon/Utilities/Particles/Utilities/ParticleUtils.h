/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_PARTICLE_UTILS_H
#define HK_PARTICLE_UTILS_H

namespace ParticleUtils
{
	// Updates the ages of particles and kills those particles that have exceeded their lifetime
	// by filling the hole left by a dead particle with the last particle in the batch.
	void ageParticles(int& numParticlesRef, char* basePtr, char* agePtr, const char* lifeTimePtr, int particleStride, hkReal timestep);

	// Uses Euler integration to advance the positions and velocities of particles over a time step.
	void moveParticles(int numParticles, char* posPtr, char* velPtr, int particleStride, hkReal timestep, const hkVector4& acceleration);
	
	// Advances the positions and velocities of particles over a time step while processing collisions using one
	// world raycast per particle. Collisions are simply resolved by moving the particle position to the ray hit
	// point and adjusting the particle velocity according to the supplied friction and restitution parameters -
	// the velocity of the collided object is not taken into account.
	// Note that sometimes particle collisions will go undetected when using raycasts since rays in Havok that
	// start inside an object will not register hits. For this reason, this function does not always work well
	// when particles are colliding against moving geometry, but it does work well for static geometry.
	void moveParticlesWithRaycastCollisions( int numParticles, char* posPtr, char* velPtr, int particleStride,
		hkReal timestep, const hkVector4& acceleration, hkReal friction, hkReal restitution, hkpWorld* world );

	// Draws particles as fixed-sized stars.
	void debugDrawParticles(int numParticles, const char* posPtr, int particleStride, hkReal size, int color);

	// Draws particles as variable-sized stars.
	void debugDrawParticles(int numParticles, const char* posPtr, const char* sizePtr, int particleStride, int color);
}

#endif	// HK_PARTICLE_UTILS_H

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
