/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SCRAPE_PARTICLE_LISTENER_H
#define HK_SCRAPE_PARTICLE_LISTENER_H

#include <Physics/Dynamics/Collide/hkpCollisionListener.h>

// A collision listener that records information about persistent contacts over a specified speed.
// This is useful when you want to emit particles in response to rigid bodies rubbing against each other, e.g. sparks.
class ScrapeParticleListener : public hkReferencedObject, public hkpCollisionListener
{
	public:

		struct ContactInfo
		{
			hkVector4		m_position;			// contact point
			hkVector4		m_direction;		// suggested direction for particle emission
			hkReal			m_relativeSpeed;	// speed at contact point (useful scale factor)
		};

   	public:

		ScrapeParticleListener(hkUint32 emitPropertyKey, hkReal relativeSpeedThreshold);
		virtual ~ScrapeParticleListener();

		// Returns an array of recorded ContactInfo objects.
		// Note that it is the users responsibility to clear this array after processing.
		hkArray<ContactInfo>& getContacts();

	protected:

		virtual void contactPointAddedCallback(hkpContactPointAddedEvent& event);
		virtual void contactPointConfirmedCallback(hkpContactPointConfirmedEvent& event);
		virtual void contactPointRemovedCallback(hkpContactPointRemovedEvent& event);
		virtual void contactProcessCallback(hkpContactProcessEvent& event);

	protected:

		// Only contacts between rigid bodies that both have this property will be recorded.
		hkUint32				m_emitPropertyKey;

		// Contacts are only saved if the relative speed at the contact point exceeds this threshold.
		hkReal					m_relativeSpeedThreshold;

		hkCriticalSection		m_criticalSection;	// a lock used to protect access to m_contacts
		hkArray<ContactInfo>	m_contacts;			// the recorded contacts
};

#endif	// HK_SCRAPE_PARTICLE_LISTENER_H

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
