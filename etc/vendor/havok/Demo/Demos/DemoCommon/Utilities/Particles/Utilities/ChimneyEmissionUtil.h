/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_CHIMNEY_EMISSION_UTIL_H
#define HK_CHIMNEY_EMISSION_UTIL_H

// Simple utility that maintains a position and time-varying direction that can be used as
// emission parameters for smoke particles to achieve a realistic smoking chimney effect.
class ChimneyEmissionUtil
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO, ChimneyEmissionUtil);

		// Emission directions (m_direction) lie within a cone of angle coneAngle radians to the axis.
		ChimneyEmissionUtil(const hkVector4& position, hkReal coneAngle, hkReal angularSpeed, hkReal phase = 0.f);

		~ChimneyEmissionUtil();

		// Updates the emission direction over a time step.
		void update(hkReal timestep);

		// Updates the emission direction over a time step and then alters the position and direction to
		// match the specified transform. This version is useful if you want the emitter to be attached
		// to an object such as a point on a rigid body.
		void update(hkReal timestep, const hkTransform& transform, const hkVector4& localAttachmentPoint);

		const hkVector4& getPosition() const;
		const hkVector4& getDirection() const;

	private:

		hkVector4	m_position;
		hkVector4	m_direction;
		hkReal		m_cotanConeAngle;
		hkReal		m_angle;
		hkReal		m_angularSpeed;
};

#endif	// HK_CHIMNEY_EMISSION_UTIL_H

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
