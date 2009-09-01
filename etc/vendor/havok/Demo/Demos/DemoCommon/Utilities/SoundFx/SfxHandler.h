/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// Prototype sound effect system

#include "Sfx.h"
#include <Sound/Common/hksSystem.h>
#include <Sound/Common/hksBuffer.h>
#include <Sound/Common/hksSource.h>

//
// SfxBaseHandler
//
class	SfxBaseHandler : public SfxHandler
{
public:
	enum	eBuffer
	{
		HK_GENERIC_IMPACT		=	0,
		HK_GENERIC_FRICTION		=	1,
		HK_GENERIC_AIRFRICTION	=	2,
		HK_GENERIC_AMBIENT		=	3,
		HK_USER_BASE			=	4,
	};
	struct	OmniSlot
	{
		hkVector4	m_position;
		hkVector4	m_velocity;
		hkReal		m_pitch;
		hkReal		m_volume;
		int			m_delay;
		int			m_lag;
		int			m_buffer;
	};
public:

	virtual ~SfxBaseHandler();

	virtual bool			initialize();
	virtual void			reset();
	int						loadBufferFromFile(const char* fname);
	void					attachManager(SfxManager* manager);
	virtual SfxSource*		attachSource(hkpConstraintInstance* constraint);
	virtual SfxSource*		attachSource(hkpRigidBody* body);
	bool					doTracking(hkpRigidBody* body);
	void					setCamera(const hkVector4& from,const hkVector4& dir,const hkVector4& up);
	void					appendOmniSource(int buffer,const hkVector4& pos,const hkVector4& vel,hkReal pitch,hkReal volume,hkReal radius=0, hkReal distanceScale=-1.f, hkBool global=false );
	void					pushOmniSource(int buffer,const hkVector4& pos,const hkVector4& vel,hkReal pitch,hkReal volume,hkReal radius,int lag);
	virtual void			postStep(hkReal dt);
	bool					isExcluded(hkpConstraintInstance* constraint);
	bool					isExcluded(hkpRigidBody* body);
	virtual int				lookupImpactBuffer(hkpConstraintInstance* constraint)	{ return(HK_GENERIC_IMPACT); }
	virtual int				lookupFrictionBuffer(hkpConstraintInstance* constraint)	{ return(HK_GENERIC_FRICTION); }
	virtual int				lookupAirFrictionBuffer(hkpRigidBody* body)				{ return(HK_GENERIC_AIRFRICTION); }	
	SfxManager*				m_manager;
	hksSystem*				m_system;
	hkVector4				m_listener;
	hkVector4				m_listenerDir;
	int						m_maxOmnis;
	hkArray<hksBuffer*>		m_buffers;
	hkArray<hkpRigidBody*>	m_tracked;
	hkArray<hkpRigidBody*>	m_excluded;
	hkArray<OmniSlot>		m_omniSlots;
	hkArray<hksSource*>		m_omniSources;
	hkReal					m_speedTreshold;
	hkBool					m_disableAutomaticAirFriction;
};

//
// SfxBaseEffects
//
namespace SfxBaseEffects
{
	//
	// Environment : Simple looping sound attached to the listener
	//
	class	Environment : public SfxSource
	{
	public:		
		hksSource*		m_source;
		SfxBaseHandler*	m_handler;
		Environment(SfxBaseHandler* handler,int buffer,hkReal volume) : SfxSource()
		{
			m_handler=handler;
			m_source=handler->m_system->createSource( true );
			if ((buffer >= 0) && (buffer < handler->m_buffers.getSize()) ) 
			{	
				m_source->attachBuffer(handler->m_buffers[buffer]);
			}
			m_source->setVolume(volume);
			m_source->setInnerRadius(100);
			m_source->setDistanceScale( HK_REAL_MAX );
			m_source->start(hksSource::HKS_PLAY_LOOP);
		}
		virtual ~Environment()
		{		
			m_source->removeReference();
		}
		bool	update(hkReal dt)
		{
			hkVector4	org(m_handler->m_listenerDir);
			org.mul4(0.01f);
			org.add4(m_handler->m_listener);
			m_source->setPosition(org);
			return(true);
		}
	};

	//
	// Omni : Simple omni directional source attached to a body
	//
	class	Omni : public SfxSource
	{
	public:		
		hksSource*		m_source;
		SfxBaseHandler*	m_handler;
		Omni(SfxBaseHandler* handler,hkpRigidBody* body,int buffer,hkReal volume) : SfxSource(body)
		{
			m_handler=handler;
			m_source=handler->m_system->createSource();
			if ((buffer >= 0) && (buffer < handler->m_buffers.getSize()) ) 
			{	
				m_source->attachBuffer(handler->m_buffers[buffer]);
			}
			m_source->setVolume(volume);
			m_source->start(hksSource::HKS_PLAY_LOOP);
		}
		virtual ~Omni()
		{		
			m_source->removeReference();
		}
		bool	update(hkReal dt)
		{
			m_source->setPosition(m_bodies[0]->getPosition());
			m_source->setVelocity(m_bodies[0]->getLinearVelocity());
			return(true);
		}
	};

	//
	// Fmo : Fast moving object source
	//
	class	Fmo : public SfxSource
	{
	public:
		hksSource*		m_source;
		SfxBaseHandler*	m_handler;
		SfxEffectMap	m_effectmap;
		hkReal			m_speed;
		Fmo(SfxBaseHandler* handler,hkpRigidBody* body,int buffer,hkReal speed) : SfxSource(body)
		{
			m_handler=handler;
			m_speed=speed;
			m_effectmap=SfxEffectMap(	hkVector4(m_speed,m_speed*3,0,1.5f),
										hkVector4(m_speed,m_speed*20,1,2));
			m_handler->m_tracked.pushBack(body);
			m_source=handler->m_system->createSource();
			if ((buffer >= 0) && (buffer < handler->m_buffers.getSize()) ) 
			{	
				m_source->attachBuffer(handler->m_buffers[buffer]);
			}
			m_source->setVolume(0);
			m_source->setInnerRadius(5);
			m_source->start(hksSource::HKS_PLAY_LOOP);
		}
		virtual ~Fmo()
		{		
			int index = m_handler->m_tracked.indexOf(m_bodies[0]);
			if ( index >=0 )
			{
				m_handler->m_tracked.removeAt(index);
			}
			m_handler->m_manager->releaseTracking(this);
			m_source->removeReference();
		}
		bool			update(hkReal dt)
		{
			const hkReal	cspeed(m_bodies[0]->getLinearVelocity().length3());
			const hkReal	volume(m_effectmap.evaluateVolume(cspeed));
			const hkReal	pitch(m_effectmap.evaluatePitch(cspeed));
			const bool		abovethreshold(cspeed>(m_speed*0.9f));
			m_source->setPosition(m_bodies[0]->getPosition());
			m_source->setVelocity(m_bodies[0]->getLinearVelocity());
			m_source->setPitch(pitch);
			m_source->setVolume(volume/**m_fade*/);
			return(abovethreshold);
		}
	};

	//
	// Impact : Impact source
	//
	class	Impact : public SfxContactManifoldSource
	{
	public:
		SfxBaseHandler*	m_handler;
		int				m_ibuffer;
		hkReal			m_impactTimeout;
		Impact(SfxBaseHandler* handler,hkpConstraintInstance* constraint,int ibuffer) : SfxContactManifoldSource(constraint)
		{
			m_handler			=	handler;
			m_ibuffer			=	ibuffer;
			m_impactTimeout		=	1;
			updateSourceParameters(0);
		}
		virtual ~Impact()
		{
		}
		void				updateSourceParameters(hkReal dt)
		{
			const int		type(hkMath::min2(m_cContacts,3)-1);
			const hkReal	pitch[]={1,0.8f,0.6f};
			const hkReal	volume[]={0.6f,0.8f,1};
			m_impactTimeout+=dt;
			if(	(m_fade>0)				&&
				(m_impactTimeout>0.5f)	&&
				(m_ibuffer>=0)			&&
				(m_cContacts>m_pContacts))
			{			
				m_impactTimeout=0;
				m_handler->pushOmniSource(	m_ibuffer,
											m_position,
											m_velocity,
											pitch[type],
											volume[type]*SfxEffectMap(hkVector4(100,150,0.05f,0.3f)).evaluateVolume(m_impactSpeed),
											10,8);
			}
		}
		virtual bool		update(hkReal dt)
		{
			if(SfxContactManifoldSource::update(dt))
			{
				updateSourceParameters(dt);
				return(m_lifeTime<1);
			}
			return(false);
		}
	};


	//
	// FrictionImpact : Friction+Impact source
	//
	class	FrictionImpact : public Impact
	{
	public:
		hksSource*		m_friction_source;
		SfxEffectMap	m_friction_map;
		SfxFade			m_fader;
		int				m_fbuffer;
		
		FrictionImpact(SfxBaseHandler* handler,hkpConstraintInstance* constraint,int ibuffer,int fbuffer) : Impact(handler,constraint,ibuffer)
		{
			m_fbuffer			=	fbuffer;
			m_fader				=	SfxFade(0.5f);
			m_friction_map		=	SfxEffectMap(	hkVector4(0.1f,50,0,5.0f),
													hkVector4(0.1f,500,0.8f,1.2f));
			m_friction_source	=	0;
			if(m_fbuffer>=0)
			{
				m_friction_source	=	handler->m_system->createSource();
				if ((fbuffer >= 0) && (fbuffer < handler->m_buffers.getSize()) ) 
				{	
					m_friction_source->attachBuffer(handler->m_buffers[fbuffer]);
//					m_friction_source->setDistanceScale(1);
					m_friction_source->setInnerRadius(150);
				}
				m_friction_source->start(hksSource::HKS_PLAY_LOOP);
			}
			updateSourceParameters(0);
		}
		virtual ~FrictionImpact()
		{
			if(m_friction_source) m_friction_source->removeReference();
		}
		void				updateSourceParameters(hkReal dt)
		{
			const int		type(hkMath::min2(m_cContacts,3)-1);
			const hkReal	pitch[]={1,0.8f,0.6f};
			const hkReal	volume[]={0.6f,0.8f,1};
			if(m_friction_source)
			{
				const hkReal	fade(m_fader.update(dt,false));
				const hkReal	rvel(fade*m_relLinearSpeed);
				const hkReal	rvolume(m_friction_map.evaluateVolume(rvel)*volume[type]);
				m_friction_source->setInnerRadius(10);
				m_friction_source->setPosition(m_position);
				m_friction_source->setVelocity(m_velocity);
				m_friction_source->setVolume(rvolume);
				m_friction_source->setPitch(m_friction_map.evaluatePitch(rvel)*pitch[type]);
				if(rvolume>0) m_lifeTime=0;
			}
		}
		virtual bool		update(hkReal dt)
		{
			if(Impact::update(dt))
			{
				updateSourceParameters(dt);
				return(true);
			}
			return(false);
		}
	};
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
