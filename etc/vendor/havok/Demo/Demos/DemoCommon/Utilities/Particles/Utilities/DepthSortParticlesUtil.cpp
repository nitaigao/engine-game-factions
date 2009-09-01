/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Demos/DemoCommon/Utilities/Particles/Utilities/DepthSortParticlesUtil.h>

static HK_FORCE_INLINE hkUint32 realToOrderedUint(const hkReal& in)
{
	hkInt32 i = *(hkInt32*)&in;
	return (hkUint32(i >> 31) | hkUint32(0x80000000)) ^ hkUint32(i);
}

DepthSortParticlesUtil::DepthSortParticlesUtil(int numParticles, const char* posPtr, int particleStride, const hkVector4& sortDirection)
	: m_numParticlesPadded((numParticles + 3) & ~3),
	  m_sortArray(m_numParticlesPadded)
{
	int numPaddingParticles = m_numParticlesPadded - numParticles;

	for(int i = m_numParticlesPadded-numPaddingParticles; i < m_numParticlesPadded; ++i)
	{
		hkRadixSort::SortData32& entry = m_sortArray[i];
		entry.m_userData = i;
		entry.m_key = 0x7fffffff;
	}

	for(int i = 0; i < numParticles; ++i)
	{
		const hkVector4& position = *reinterpret_cast<const hkVector4*>(posPtr);

		hkRadixSort::SortData32& entry = m_sortArray[i];
		entry.m_userData = i;
		entry.m_key = realToOrderedUint(sortDirection.dot3(position)) >> 1;

		posPtr += particleStride;
	}

	hkLocalBuffer<hkRadixSort::SortData32> buffer(m_numParticlesPadded);
	hkRadixSort::sort32(m_sortArray.begin(), m_numParticlesPadded, buffer.begin());
}

DepthSortParticlesUtil::~DepthSortParticlesUtil()
{
}

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
