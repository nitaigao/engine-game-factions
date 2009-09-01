/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Demos/demos.h>

#include "SfxHandler.h"
#include <Common/Base/Algorithm/Sort/hkSort.h>

hksSystem* HK_CALL hksSystemCreateXA2();

//
// SfxBaseHandler
//

//
bool SfxBaseHandler::initialize()
{
	m_manager		=	0;
	m_speedTreshold	=	50;
	m_maxOmnis		=	128;
	m_listener		=	hkVector4(0,0,0,0);
	m_listenerDir	=	hkVector4(0,0,0,0);
	m_disableAutomaticAirFriction = false;

	m_system		=	hksSystemCreateXA2();

	if( m_system && m_system->init())
	{		
		loadBufferFromFile("./Resources/Common/Sound/Internal/object_crash01.wav");
		loadBufferFromFile("./Resources/Common/Sound/Internal/metal_friction01.wav");
		loadBufferFromFile("./Resources/Common/Sound/Internal/air_friction02.wav");
		loadBufferFromFile("./Resources/Common/Sound/Internal/birds01.wav");
		return(true);
	}
	return(false);
}

//
void	SfxBaseHandler::reset()
{
	
	for(int i=0;i<m_omniSources.getSize();++i)
	{
		m_omniSources[i]->removeReference();
	}
	m_tracked.clear();
	m_omniSlots.clear();
	m_omniSources.clear();	
}

//
SfxBaseHandler::~SfxBaseHandler()
{	
	reset();
	
	for(int i=0;i<m_buffers.getSize();++i)
	{
		m_buffers[i]->removeReference();
	}

	if (m_system)
	{
		m_system->removeReference();
		m_system=HK_NULL;	
	}
}

//
int				SfxBaseHandler::loadBufferFromFile(const char* fname)
{
	printf("Loading %s\r\n",fname);
	hksBuffer*	buffer(m_system->createBuffer());
	if(buffer->loadFromFile(fname)==HK_SUCCESS)
	{
		m_buffers.pushBack(buffer);
		return(m_buffers.getSize()-1);
	}
	else
	{
		HK_WARN_ALWAYS(0x0, "Could not find sounds file, " << fname << ", demo will not work as expected.");
		buffer->removeReference();
		return(-1);
	}
}

//
void			SfxBaseHandler::attachManager(SfxManager* manager)
{
	m_manager=manager;
}

//
SfxSource*		SfxBaseHandler::attachSource(hkpConstraintInstance* constraint)
{
	SfxSource*	source(0);
	if(!isExcluded(constraint))
	{		
		switch(constraint->getData()->getType())
		{
		case	hkpConstraintData::CONSTRAINT_TYPE_CONTACT:
			{
			const int ibuffer(lookupImpactBuffer(constraint));
			const int fbuffer(lookupFrictionBuffer(constraint));
			if((ibuffer>=0)||(fbuffer>=0))
				{
				if(fbuffer)
					source=new SfxBaseEffects::FrictionImpact(this,constraint,ibuffer,fbuffer);
				else
					source=new SfxBaseEffects::Impact(this,constraint,ibuffer);
				}
			}
		break;
		}		
	}
	return(source);
}

//
SfxSource*		SfxBaseHandler::attachSource(hkpRigidBody* body)
{	
	if(!isExcluded(body) && !m_disableAutomaticAirFriction)
	{
		const hkReal	sqspeed(m_speedTreshold*m_speedTreshold);
		if(body->getLinearVelocity().lengthSquared3()>sqspeed)
		{
			if(m_tracked.indexOf(body)==-1)
			{
				const int buffer(lookupAirFrictionBuffer(body));
				if(buffer>=0) return(new SfxBaseEffects::Fmo(this,body,buffer,m_speedTreshold));
			}
		}
	}
	return(0);
}

//
bool			SfxBaseHandler::doTracking(hkpRigidBody* body)
{
	return(true);
}

//
bool			SfxBaseHandler::isExcluded(hkpConstraintInstance* constraint)
{
	return(	isExcluded(constraint->getRigidBodyA())||
			isExcluded(constraint->getRigidBodyB()));
}

//
bool			SfxBaseHandler::isExcluded(hkpRigidBody* body)
{
	return(m_excluded.indexOf(body)!=-1);
}

//
void			SfxBaseHandler::appendOmniSource(int buffer,const hkVector4& pos,const hkVector4& vel,hkReal pitch,hkReal volume, hkReal radius, hkReal distanceScale, hkBool global )
{
	if ( buffer >= m_buffers.getSize() )
	{
		HK_WARN( 0xf02de45, "SfxBaseHandler::appendOmniSource: Uknown sound source");
		return;
	}
	if((volume>0)&&(pitch>0))
	{
		while(m_omniSources.getSize()>=m_maxOmnis)
		{
			hksSource* src = m_omniSources.back();
			src->removeReference();
			m_omniSources.popBack();
		}
		hksSource*	ps = m_system->createSource( global );
		m_omniSources.pushBack(ps);
		ps->attachBuffer(m_buffers[buffer],false);
		if(radius>0) ps->setInnerRadius(radius);
		ps->setPosition(pos);
		ps->setVelocity(vel);
		ps->setPitch(pitch);
		ps->setVolume(volume);
		if ( distanceScale >= 0 ) ps->setDistanceScale( distanceScale );
		ps->start(hksSource::HKS_PLAY_ONCE);
	}
}

//
void			SfxBaseHandler::pushOmniSource(int buffer,const hkVector4& pos,const hkVector4& vel,hkReal pitch,hkReal volume,hkReal range,int lag)
{
	if((volume>0)&&(pitch>0))
	{
		const hkReal	sqrange(range*range);
		for(int i=0,ni=m_omniSlots.getSize();i<ni;++i)
		{
			OmniSlot&	s(m_omniSlots[i]);
			if((s.m_buffer==buffer)&&(s.m_lag==lag))
			{
				hkVector4	x(s.m_position);
				x.sub4(pos);
				if(x.lengthSquared3()<sqrange)
				{
					s.m_position.add4(pos);
					s.m_velocity.add4(vel);
					s.m_pitch+=pitch;
					s.m_volume+=volume;
					s.m_position.mul4(0.5f);
					s.m_velocity.mul4(0.5f);
					s.m_pitch*=0.4f;
					s.m_volume*=0.7f;
					return;
				}
			}
		}
		OmniSlot&	s(m_omniSlots.expandOne());
		s.m_buffer		=	buffer;
		s.m_delay		=	0;
		s.m_pitch		=	pitch;
		s.m_volume		=	volume;
		s.m_position	=	pos;
		s.m_velocity	=	vel;
		s.m_lag			=	lag;
	}
}

//
void			SfxBaseHandler::setCamera(const hkVector4& from,const hkVector4& dir,const hkVector4& up)
{
	m_listener=from;
	m_listenerDir=dir;
	m_system->setListener(from,dir,up);
	m_system->recalc();
}

//
void			SfxBaseHandler::postStep(hkReal dt)
{
	for(int i=m_omniSources.getSize()-1; i >= 0; --i)
	{
		if(m_omniSources[i]->loopCount()>0)
		{
			m_omniSources[i]->removeReference();
			m_omniSources.removeAt(i);			
		}
	}
	for(int i=m_omniSlots.getSize()-1; i >= 0; --i)
	{
		OmniSlot&	s(m_omniSlots[i]);
		if((++m_omniSlots[i].m_delay)>m_omniSlots[i].m_lag)
		{
			appendOmniSource(s.m_buffer,s.m_position,s.m_velocity,s.m_pitch,s.m_volume);
			m_omniSlots.removeAt(i);
		}
	}
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
