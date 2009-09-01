/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Demos/DemoCommon/Utilities/Particles/Utilities/ChimneyEmissionUtil.h>

ChimneyEmissionUtil::ChimneyEmissionUtil(const hkVector4& position, hkReal coneAngle, hkReal angularSpeed, hkReal phase)
	: m_position(position),
	  m_direction(0.f, 0.f, 0.f),
	  m_angle(phase),
	  m_angularSpeed(angularSpeed)
{
	m_cotanConeAngle = (coneAngle < HK_REAL_EPSILON) ? 0.f : hkMath::cos(coneAngle)/hkMath::sin(coneAngle);

	update(0.f);
}

ChimneyEmissionUtil::~ChimneyEmissionUtil()
{
}

void ChimneyEmissionUtil::update(hkReal timestep)
{
	m_direction.set(hkMath::sin(m_angle), m_cotanConeAngle, hkMath::cos(m_angle));
	m_direction.normalize3();

	m_angle += m_angularSpeed * timestep;
}

void ChimneyEmissionUtil::update(hkReal timestep, const hkTransform& transform, const hkVector4& localAttachmentPoint)
{
	update(timestep);

	m_position.setTransformedPos(transform, localAttachmentPoint);
	m_direction.setRotatedDir(transform.getRotation(), m_direction);
}

const hkVector4& ChimneyEmissionUtil::getPosition() const
{
	return m_position;
}

const hkVector4& ChimneyEmissionUtil::getDirection() const
{
	return m_direction;
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
