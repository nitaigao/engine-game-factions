/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_DEPTH_SORT_PARTICLES_UTIL_H
#define HK_DEPTH_SORT_PARTICLES_UTIL_H

#include <Common/Base/Algorithm/Sort/hkRadixSort.h>
#include <Common/Base/Container/LocalArray/hkLocalBuffer.h>

// Utility for depth-sorting particles. Since this uses hkLocalBuffer, the object should only be constructed and kept in
// scope while it is being used. The constructor itself performs the sorting based on the specified camera direction.
class DepthSortParticlesUtil
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO, DepthSortParticlesUtil);

		DepthSortParticlesUtil(int numParticles, const char* posPtr, int particleStride, const hkVector4& sortDirection);
		~DepthSortParticlesUtil();

		// Returns the i-th sorted index where i is in [0, numParticles]
		int getSortedIndex(int i) const;

	private:

		int m_numParticlesPadded;
		hkLocalBuffer<hkRadixSort::SortData32> m_sortArray;
};

#include <Demos/DemoCommon/Utilities/Particles/Utilities/DepthSortParticlesUtil.inl>

#endif	// HK_DEPTH_SORT_PARTICLES_UTIL_H

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
