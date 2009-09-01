/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_PARTICLE_SYSTEM_H
#define HK_PARTICLE_SYSTEM_H

// Base class for particle systems which knows nothing about the properties of a particle. Each particle is
// just treated as raw memory. All memory management associated with the particle system is handled by this
// class, including allocating more memory if necessary to accommodate more particles.
//
// Note that in derived class implementations of initParticles() and updateParticles(), when iterating
// through particles, it is better practice to use:
//    Particle& p = *reinterpret_cast<Particle*>(static_cast<char*>(particleData) + i*m_particleStride);
// instead of:
//   Particle* particles = static_cast<Particle*>(particleData);
//   Particle& p = particles[i];
// since the former supports extending the size in memory of a particle.
class ParticleSystem : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO);

		ParticleSystem(int particleStride);
		virtual ~ParticleSystem();

		int getNumParticles() const;
		const void* getParticleData() const;

		// Zeros the particle count.
		virtual void clear();

		// Adds more particles to the particle system, allocating additional memory if necessary and calling
		// initParticles() to initialize the memory. emitParams is passed onto initParticles() where it can
		// optionally be used by the derived class to allow passing of user emission parameters.
		void emit(int numParticlesToEmit, hkReal timestep, const void* emitParams = HK_NULL);

		// Calls updateParticles() to advance the particles over a time step.
		void update(hkReal timestep);

		// Responsible for drawing the particle system (default implementation does nothing).
		virtual void draw();

		// Allocates memory to hold an increased number of particles and moves the current particles to the new
		// memory. This function is automatically called by emit() when necessary, though the user may also call
		// it whenever they like, e.g. to reserve memory for particles before the simulation begins.
		void increaseCapacity(int numParticlesRequired);

		// This can be called to purge unused memory (for example, after clear() is called).
		// Beware that it will potentially shift the location of particles in memory.
		void optimizeCapacity(int numFreeParticlesLeft = 0, bool shrinkExact = false);

	protected:

		// Pure virtual function that defines how the raw memory associated with newly
		// emitted particles is initialized. This is particle system dependent.
		virtual void initParticles(int numParticles, void* particleData, hkReal timestep, const void* emitParams) = 0;

		// Pure virtual function that defines how particles are updated. It is permitted for this function
		// to kill particles but if it does so it must update numParticlesRef accordingly and make sure that
		// the particles remain compacted in memory.
		virtual void updateParticles(int& numParticlesRef, void* particleData, hkReal timestep) = 0;		

		// Moves the particles to newly allocated memory of the desired size and deallocates
		// the old memory. This is called by increaseCapacity() and optimizeCapacity().
		void changeCapacity(int newMaxNumParticles);

	protected:

		int		m_particleStride;	// size of particle structure in bytes
		int		m_numParticles;		// number of particles
		int		m_maxNumParticles;	// number of particles for which memory is allocated
		void*	m_particleData;		// raw memory to hold particles consecutively, i.e. there are no holes
};

#endif	// HK_PARTICLE_SYSTEM_H

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
