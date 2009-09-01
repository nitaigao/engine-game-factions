/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_CONTINUOUS_EMISSION_UTIL_H
#define HK_CONTINUOUS_EMISSION_UTIL_H

// This is a simple utility that, given an arbitrarily small emission rate,
// will tell you how many particles should be emitted each time step.
class ContinuousEmissionUtil
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO, ContinuousEmissionUtil);

		ContinuousEmissionUtil();
		ContinuousEmissionUtil(hkReal emissionRate);
		~ContinuousEmissionUtil();

		// Updates the internal state and returns the number of particles that should be emitted.
		int update(hkReal timestep);

		hkReal getEmissionRate() const;
		void setEmissionRate(hkReal emissionRate);

	private:

		hkReal	m_emissionRate;
		hkReal	m_numParticlesRequested;
};

#endif	// HK_CONTINUOUS_EMISSION_UTIL_H

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
