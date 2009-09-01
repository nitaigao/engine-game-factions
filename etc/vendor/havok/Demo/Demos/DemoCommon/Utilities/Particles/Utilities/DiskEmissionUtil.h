/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_DISK_EMISSION_UTIL_H
#define HK_DISK_EMISSION_UTIL_H

class hkPseudoRandomGenerator;

// Utility to sample positions and directions from an oriented disk. The position is computed
// by uniformly sampling the disk and optionally adding some random variance. The direction is
// sampled from a cone of directions perpendicular to the disk.
class DiskEmissionUtil
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO, DiskEmissionUtil);

		// Parameters:
		//  - position is the center of the disk
		//  - radius is the disk radius and can be zero
		//  - inPlaneVariance defines the positional variance in the plane of the disk
		//  - outOfPlaneVariance defines the positional variance perpendicular to the disk
		//  - direction is equivalent to the disk normal
		//  - coneAngle defines the directional spread and should be in [0,pi]
		DiskEmissionUtil( const hkVector4& position, hkReal radius, hkReal inPlaneVariance,
			hkReal outOfPlaneVariance, const hkVector4& direction, hkReal coneAngle );

		~DiskEmissionUtil();

		void samplePosition(hkVector4& position, hkPseudoRandomGenerator* pseudoRandomGenerator) const;
		void sampleDirection(hkVector4& direction, hkPseudoRandomGenerator* pseudoRandomGenerator) const;

	private:

		hkVector4	m_position;
		hkMatrix3	m_orthonormalBasis;
		hkReal		m_radius;
		hkReal		m_inPlaneVariance;
		hkReal		m_outOfPlaneVariance;
		hkReal		m_speed;
		hkReal		m_cosConeAngle;
};

#endif	// HK_DISK_EMISSION_UTIL_H

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
