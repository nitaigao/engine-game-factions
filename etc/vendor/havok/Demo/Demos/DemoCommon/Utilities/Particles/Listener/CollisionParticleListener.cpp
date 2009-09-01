/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Demos/DemoCommon/Utilities/Particles/Listener/CollisionParticleListener.h>

CollisionParticleListener::CollisionParticleListener( hkUint32 emitPropertyKey,
	hkUint32 multiplierPropertyKey, hkReal relativeProjectedSpeedThreshold )
	: m_emitPropertyKey(emitPropertyKey),
	  m_multiplierPropertyKey(multiplierPropertyKey),
	  m_relativeProjectedSpeedThreshold(relativeProjectedSpeedThreshold),
	  m_criticalSection(1000)
{
}

CollisionParticleListener::~CollisionParticleListener()
{
}

hkArray<CollisionParticleListener::ContactInfo>& CollisionParticleListener::getContacts()
{
	return m_contacts;
}

void CollisionParticleListener::contactPointAddedCallback(hkpContactPointAddedEvent& event)
{
}

void CollisionParticleListener::contactPointConfirmedCallback(hkpContactPointConfirmedEvent& event)
{
	HK_TIMER_BEGIN("CollisionParticleListener CB", this);

	hkpRigidBody* rigidBodyA = hkGetRigidBody(event.m_collidableA->getRootCollidable());
	hkpRigidBody* rigidBodyB = hkGetRigidBody(event.m_collidableB->getRootCollidable());

	if(rigidBodyA->hasProperty(m_emitPropertyKey) || rigidBodyB->hasProperty(m_emitPropertyKey))
	{
		hkReal relativeProjectedSpeed = hkMath::fabs(event.m_projectedVelocity);
		
		if(rigidBodyA->hasProperty(m_multiplierPropertyKey))
		{
			relativeProjectedSpeed *= rigidBodyA->getProperty(m_multiplierPropertyKey).getReal();
		}

		if(rigidBodyB->hasProperty(m_multiplierPropertyKey))
		{
			relativeProjectedSpeed *= rigidBodyB->getProperty(m_multiplierPropertyKey).getReal();
		}
		
		if(relativeProjectedSpeed > m_relativeProjectedSpeedThreshold)
		{
			// A critical section has to be used here since listener callbacks can be called from different threads.
			m_criticalSection.enter();
			ContactInfo& contactInfo = m_contacts.expandOne();
			contactInfo.m_position = event.m_contactPoint->getPosition();
			contactInfo.m_normal = event.m_contactPoint->getNormal();
			contactInfo.m_relativeProjectedSpeed = relativeProjectedSpeed;
			m_criticalSection.leave();
		}
	}

	HK_TIMER_END();
}

void CollisionParticleListener::contactPointRemovedCallback(hkpContactPointRemovedEvent& event)
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
