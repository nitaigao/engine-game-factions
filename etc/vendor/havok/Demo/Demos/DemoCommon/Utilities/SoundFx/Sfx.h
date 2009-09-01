/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// Prototype sound effect system
#ifndef _SFX_SYSTEM_
#define	_SFX_SYSTEM_

#include <Physics/Dynamics/Constraint/hkpConstraintListener.h>
#include <Physics/Dynamics/World/Listener/hkpIslandActivationListener.h>
#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>

class SfxManager;
class SfxHandler;
class SfxSource;
class SfxContactManifoldSource;

//
// SfxHandler
//
class SfxHandler : public hkReferencedObject
{
public:
	HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DEMO);

	/* virtual ~SfxHandler( ) */

	virtual void		attachManager(SfxManager* manager) {}
	virtual SfxSource*	attachSource(hkpConstraintInstance* constraint) { return(0); }
	virtual SfxSource*	attachSource(hkpRigidBody* body) { return(0); }
	virtual bool		doTracking(hkpRigidBody* body) { return(false); }
	virtual void		setCamera(const hkVector4& from,const hkVector4& dir,const hkVector4& up)=0;
	virtual void		preStep(hkReal dt)	{}
	virtual void		postStep(hkReal dt)	{}
	virtual void		reset() {}
};

//
// SfxFade
//
class SfxFade
{
public:

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO, SfxFade);

	SfxFade(hkReal delay=1) : m_fadein(0),m_fadeout(0),m_delay(delay) {}

	HK_FORCE_INLINE hkReal	update(hkReal dt,bool out)
	{
		if(out)
		{
			m_fadeout=hkMath::min2(m_fadeout+dt,m_delay);
		}
		else
		{
			m_fadeout=0;
			m_fadein=hkMath::min2(m_fadein+dt,m_delay);
		}
		return(evaluate());
	}
	HK_FORCE_INLINE hkReal	evaluate() const
	{
		return((m_fadein*(m_delay-m_fadeout))/(m_delay*m_delay));
	}
	HK_FORCE_INLINE hkReal	finished() const
	{
		return(m_fadeout>=m_delay);
	}
	hkReal	m_fadein;
	hkReal	m_fadeout;
	hkReal	m_delay;
};

//
// SfxEffectMap
//
struct	SfxEffectMap
{
public:
	
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO, SfxEffectMap);

	SfxEffectMap(const hkVector4& volmap=hkVector4(0,1,1,1),const hkVector4& pitchmap=hkVector4(0,1,1,1)) : m_volumeMap(volmap),m_pitchMap(pitchmap) {}
	HK_FORCE_INLINE hkReal	evaluatePitch(hkReal relvelocity) const		{ return(remapclamp(relvelocity,m_pitchMap(0),m_pitchMap(1),m_pitchMap(2),m_pitchMap(3))); }
	HK_FORCE_INLINE hkReal	evaluateVolume(hkReal relvelocity) const	{ return(remapclamp(relvelocity,m_volumeMap(0),m_volumeMap(1),m_volumeMap(2),m_volumeMap(3))); }
public:
	hkVector4	m_volumeMap;
	hkVector4	m_pitchMap;
private:
	static HK_FORCE_INLINE hkReal	lerp(hkReal a,hkReal b,hkReal t)										{ return(a+(b-a)*t); }
	static HK_FORCE_INLINE hkReal	clamp(hkReal x,hkReal minv,hkReal maxv)									{ return(x<minv?minv:x>maxv?maxv:x); }
	static HK_FORCE_INLINE hkReal	remap(hkReal x,hkReal imin,hkReal imax,hkReal omin,hkReal omax)			{ return(lerp(omin,omax,(x-imin)/(imax-imin))); }
	static HK_FORCE_INLINE hkReal	remapclamp(hkReal x,hkReal imin,hkReal imax,hkReal omin,hkReal omax)	{ return(clamp(remap(x,imin,imax,omin,omax),omin,omax)); }
};

//
// SfxSource
//
class SfxSource : public hkReferencedObject
{
public:
	HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DEMO);

	hkpConstraintInstance*	m_constraint;
	hkpRigidBody*			m_bodies[2];
	hkVector4				m_position;
	hkVector4				m_velocity;
	hkReal					m_lifeTime;
	hkReal					m_fade;
	void*					m_userData;
	bool					m_active;
	bool					m_global;
							SfxSource(hkpConstraintInstance*);
							SfxSource(hkpRigidBody*);
							SfxSource();
	virtual					~SfxSource()	{}
	virtual bool			update(hkReal);
	virtual void			activate(bool doa)	{ m_active=doa; }
	virtual bool			detach()			{ m_constraint=0;return(true); }
	virtual void			release() 			{ delete this; }
};

//
// SfxContactManifoldSource
//
class SfxContactManifoldSource : public SfxSource
{
public:
	hkReal					m_relLinearSpeed;
	hkReal					m_relAngularSpeed;
	hkReal					m_impactSpeed;
	int						m_pContacts;
	int						m_cContacts;
							SfxContactManifoldSource(hkpConstraintInstance*);
	virtual					~SfxContactManifoldSource() {}
	virtual bool			update(hkReal dt);
};

//
// SfxManager
//
class SfxManager :	public hkReferencedObject,
					public hkpConstraintListener,
					public hkpEntityListener,
					public hkpIslandActivationListener
{	
public:
	HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DEMO);
	class	Probe : public hkpAabbPhantom
	{
	public:
		Probe() : hkpAabbPhantom(hkAabb(hkVector4(-1,-1,-1),hkVector4(+1,+1,+1))),m_manager(0) {}
		// =>hkpAabbPhantom
		void	addOverlappingCollidable( hkpCollidable* handle ) { m_manager->addOverlappingCollidable(handle); }
		void	removeOverlappingCollidable( hkpCollidable* handle ) { m_manager->removeOverlappingCollidable(handle); }
		SfxManager*	m_manager;
	};
	
	// Methods
	SfxManager(hkpWorld*,SfxHandler*);
	virtual ~SfxManager();

	void	step();
	void	setCamera(const hkVector4& from,const hkVector4& dir,const hkVector4& up);
	void	appendSource(SfxSource* source);
	bool	releaseTracking(SfxSource* source);
	void	releaseAllSources();	
private:	
	void	releaseSource(SfxSource* source);
	void	releaseSource(int index);
	void	activateIsland(hkpSimulationIsland* island,bool activate);
	// =>hkpEntityListener
	void	entityRemovedCallback(hkpEntity* entity);
	// =>hkpConstraintListener
	void	constraintAddedCallback(hkpConstraintInstance* constraint);
	void	constraintRemovedCallback(hkpConstraintInstance* constraint);
	// =>hkpIslandActivationListener
	void	islandActivatedCallback(hkpSimulationIsland* island);
	void	islandDeactivatedCallback(hkpSimulationIsland* island);
	// =>Probe
	void	addOverlappingCollidable( hkpCollidable* handle );
	void	removeOverlappingCollidable( hkpCollidable* handle );
	// Fields
public:
	hkpWorld*					m_world;
	hkArray<SfxSource*>			m_sources;
	SfxHandler*					m_handler;
	hkArray<hkpRigidBody*>		m_tracking;
	hkArray<hkpRigidBody*>		m_tracked;
	hkVector4					m_position;
	Probe						m_probe;
	hkReal						m_probeRange;
	hkReal						m_listenerRange;	
	int							m_maxSources;
	hkCriticalSection			m_cs;

};

#endif

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
