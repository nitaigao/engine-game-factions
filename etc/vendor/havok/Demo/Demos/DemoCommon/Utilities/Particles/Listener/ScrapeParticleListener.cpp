/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Demos/DemoCommon/Utilities/Particles/Listener/ScrapeParticleListener.h>

ScrapeParticleListener::ScrapeParticleListener(hkUint32 emitPropertyKey, hkReal relativeSpeedThreshold)
	: m_emitPropertyKey(emitPropertyKey),
	  m_relativeSpeedThreshold(relativeSpeedThreshold),
	  m_criticalSection(1000)
{
}

ScrapeParticleListener::~ScrapeParticleListener()
{
}

hkArray<ScrapeParticleListener::ContactInfo>& ScrapeParticleListener::getContacts()
{
	return m_contacts;
}

void ScrapeParticleListener::contactPointAddedCallback(hkpContactPointAddedEvent& event)
{
	// Request callbacks to be fired every frame.
	if (event.m_callbackFiredFrom)
	{
		event.m_callbackFiredFrom->setProcessContactCallbackDelay(0);
	}
}

void ScrapeParticleListener::contactPointConfirmedCallback(hkpContactPointConfirmedEvent& event)
{
}

void ScrapeParticleListener::contactPointRemovedCallback(hkpContactPointRemovedEvent& event)
{
}

void ScrapeParticleListener::contactProcessCallback(hkpContactProcessEvent& event)
{
	HK_TIMER_BEGIN("ScrapeParticleListener CB", this);

	hkpProcessCollisionData* collisionData = event.m_collisionData;

	for(int i = 0; i < collisionData->getNumContactPoints(); ++i)
	{
		hkpSimpleConstraintContactMgr* mgr = static_cast<hkpSimpleConstraintContactMgr*>(event.m_internalContactMgr);
		hkpRigidBody* rigidBodyA = mgr->getConstraintInstance()->getRigidBodyA();
		hkpRigidBody* rigidBodyB = mgr->getConstraintInstance()->getRigidBodyB();

		if(rigidBodyA->hasProperty(m_emitPropertyKey) && rigidBodyB->hasProperty(m_emitPropertyKey))
		{
			// Compute relative velocity at contact point.
			hkContactPoint& contactPoint = collisionData->getContactPoint(i).m_contact;
			hkVector4 velocityA, velocityB, relativeVelocity;
			rigidBodyA->getPointVelocity(contactPoint.getPosition(), velocityA);
			rigidBodyB->getPointVelocity(contactPoint.getPosition(), velocityB);
			relativeVelocity.setSub4(velocityA, velocityB);
			hkReal relativeSpeed = relativeVelocity.length3();

			if(relativeSpeed > m_relativeSpeedThreshold)
			{
				hkVector4 direction, normal;
				if(velocityA.lengthSquared3() > velocityB.lengthSquared3())
				{
					direction.setNeg4(relativeVelocity);
					normal = contactPoint.getNormal();
				}
				else
				{
					direction = relativeVelocity;
					normal.setNeg4(contactPoint.getNormal());
				}
				direction.normalize3();

				// Bend the velocity towards the contact normal. This looks slightly better but can be commented out if desired.
				const hkReal t = 0.7f;
				direction.mul4(t);
				direction.addMul4(1.f-t, normal);
				direction.normalize3();

				// A critical section has to be used here since listener callbacks can be called from different threads.
				m_criticalSection.enter();
				ContactInfo& contactInfo = m_contacts.expandOne();
				contactInfo.m_position = contactPoint.getPosition();
				contactInfo.m_direction = direction;
				contactInfo.m_relativeSpeed = relativeSpeed;
				m_criticalSection.leave();
			}
		}
	}

	HK_TIMER_END();
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
