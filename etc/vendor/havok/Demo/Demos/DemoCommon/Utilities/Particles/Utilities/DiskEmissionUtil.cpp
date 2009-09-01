/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Demos/DemoCommon/Utilities/Particles/Utilities/DiskEmissionUtil.h>
#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>

DiskEmissionUtil::DiskEmissionUtil( const hkVector4& position, hkReal radius, hkReal inPlaneVariance,
	hkReal outOfPlaneVariance, const hkVector4& direction, hkReal coneAngle )
	: m_position(position),
	  m_radius(radius),
	  m_inPlaneVariance(inPlaneVariance),
	  m_outOfPlaneVariance(outOfPlaneVariance),
	  m_cosConeAngle(hkMath::cos(coneAngle))
{
	// Note that this call sets the first matrix column equal to direction.
	hkVector4Util::buildOrthonormal(direction, m_orthonormalBasis);
}

DiskEmissionUtil::~DiskEmissionUtil()
{
}

void DiskEmissionUtil::samplePosition(hkVector4& position, hkPseudoRandomGenerator* pseudoRandomGenerator) const
{
	// Pick a random point on the disk (see http://mathworld.wolfram.com/DiskPointPicking.html)
	hkReal radius = m_radius * hkMath::sqrt(pseudoRandomGenerator->getRandReal01());
	hkReal theta = pseudoRandomGenerator->getRandReal01() * 2.f * HK_REAL_PI;
	hkReal diskX = radius * hkMath::cos(theta);
	hkReal diskY = radius * hkMath::sin(theta);

	hkReal offsetX = pseudoRandomGenerator->getRandRange(-m_outOfPlaneVariance, m_outOfPlaneVariance);
	hkReal offsetY = diskY + pseudoRandomGenerator->getRandRange(-m_inPlaneVariance, m_inPlaneVariance);
	hkReal offsetZ = diskX + pseudoRandomGenerator->getRandRange(-m_inPlaneVariance, m_inPlaneVariance);
	hkVector4 localOffset(offsetX, offsetY, offsetZ);

	m_orthonormalBasis.multiplyVector(localOffset, position);
	position.add4(m_position);
}

void DiskEmissionUtil::sampleDirection(hkVector4& direction, hkPseudoRandomGenerator* pseudoRandomGenerator) const
{
	// Theta is a random value in [0,ConeAngle], phi is a random value in [0,2*pi]
	hkReal cosTheta = m_cosConeAngle + pseudoRandomGenerator->getRandReal01()*(1.f-m_cosConeAngle);
	hkReal sinTheta = hkMath::sqrt(1.f - cosTheta*cosTheta);
	hkReal phi = pseudoRandomGenerator->getRandReal01() * 2.f * HK_REAL_PI;

	hkReal dirX = cosTheta;
	hkReal dirY = sinTheta * hkMath::sin(phi);
	hkReal dirZ = sinTheta * hkMath::cos(phi);
	hkVector4 localDirection(dirX, dirY, dirZ);

	m_orthonormalBasis.multiplyVector(localDirection, direction);
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
