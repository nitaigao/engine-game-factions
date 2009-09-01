/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Demos/demos.h>

#include "Sfx.h"

#include <Common/Visualize/hkDebugDisplay.h>

//XX Take these physics deps out of the general cross product parts
#include <Physics/Dynamics/Constraint/Contact/hkpSimpleContactConstraintData.h>
#include <Physics/Dynamics/World/hkpSimulationIsland.h>

//
// SfxSource
//

//
SfxSource::SfxSource(hkpConstraintInstance* constraint) : m_constraint(constraint),m_position(0,0,0,0),m_velocity(0,0,0,0),m_lifeTime(0),m_fade(1),m_userData(0),m_active(true), m_global(false)
{
	m_bodies[0]	=	m_constraint->getRigidBodyA();
	m_bodies[1]	=	m_constraint->getRigidBodyB();
}

//
SfxSource::SfxSource(hkpRigidBody* body) : m_constraint(0),m_position(0,0,0,0),m_velocity(0,0,0,0),m_lifeTime(0),m_fade(1),m_userData(0),m_active(true), m_global(false)
{
	m_bodies[0]	=	body;
	m_bodies[1]	=	0;
}

//
SfxSource::SfxSource() : m_constraint(0),m_position(0,0,0,0),m_velocity(0,0,0,0),m_lifeTime(0),m_fade(1),m_userData(0),m_active(true), m_global(false)
{
	m_bodies[0]	=	0;
	m_bodies[1]	=	0;
}

//
bool		SfxSource::update(hkReal dt)
{
	m_lifeTime			+=	dt;
	return(true);
}

//
// SfxContactManifoldSource
//

//
SfxContactManifoldSource::SfxContactManifoldSource(hkpConstraintInstance* constraint) : SfxSource(constraint)
{
	m_relLinearSpeed	=	0;
	m_relAngularSpeed	=	0;
	m_impactSpeed		=	0;
	m_pContacts			=	-1;
	m_cContacts			=	0;
	update(0);
}

//
bool		SfxContactManifoldSource::update(hkReal dt)
{	
	const hkVector4	prevPos(m_position);
	const hkVector4	prevVel(m_velocity);
	m_relLinearSpeed	=	0;
	m_relAngularSpeed	=	0;
	m_impactSpeed		=	0;
	m_position			=	hkVector4(0,0,0);
	m_velocity			=	hkVector4(0,0,0);
	m_pContacts			=	m_cContacts;
	m_cContacts			=	0;
	if(m_constraint)
	{
		hkpSimpleContactConstraintData*	md = (hkpSimpleContactConstraintData*)m_constraint->getData();
		m_cContacts=md->getNumContactPoints();
		if(m_cContacts>0)
		{
			hkVector4		normal(0,0,0);
			/* Calculate our average sound source position	*/ 
			for(int i=0;i<m_cContacts;++i)
			{
				const hkContactPoint&	cp(md->getContactPoint(md->getContactPointIdAt(i)));
				m_position.add4(cp.getPosition());
				normal.add4(cp.getNormal());
			}
			m_position.mul4(1/(hkReal)m_cContacts);
			/* Evaluate velocities from there				*/ 
			hkVector4		v0,v1,v2;
			m_bodies[0]->getPointVelocity(m_position,v0);
			m_bodies[1]->getPointVelocity(m_position,v1);
			v2.setSub4(v0,v1);
			m_impactSpeed		=	hkMath::fabs(normal.dot3(v2));
			m_relLinearSpeed	=	((hkReal)v2.length3())-m_impactSpeed;
			if(dt>0)
			{
				m_velocity=m_position;
				m_velocity.sub4(prevPos);
				m_velocity.mul4(1/dt);				
				m_velocity.sub4(prevVel);
				m_velocity.mul4(0.01f);
				m_velocity.add4(prevVel);
			}

			v0.setSub4(m_bodies[0]->getAngularVelocity(),m_bodies[1]->getAngularVelocity());
			m_relAngularSpeed	=	v0.length3();
		}
	}
	return(SfxSource::update(dt));
}

//
// SfxManager implementation
//

//
SfxManager::SfxManager(hkpWorld* world,SfxHandler* handler)
{
	m_world				=	world;
	m_handler			=	handler;
	m_position			=	hkVector4(0,0,0,0);
	m_probeRange		=	20;
	m_listenerRange		=	100;
	m_maxSources		=	512;
	m_probe.m_manager	=	this;
	m_world->lock();
	m_world->addConstraintListener(this);
	m_world->addEntityListener(this);
	m_world->addIslandActivationListener(this);
	m_world->addPhantom(&m_probe);
	m_world->unlock();
	m_handler->attachManager(this);
	HK_REPORT("SfxManager initialized");
}

//
SfxManager::~SfxManager()
{
	releaseAllSources();
	m_world->lock();
	m_world->removeConstraintListener(this);
	m_world->removeEntityListener(this);
	m_world->removeIslandActivationListener(this);
	m_world->removePhantom(&m_probe);
	m_world->unlock();
	HK_REPORT("SfxManager released");
}

//
void		SfxManager::step()
{
	hkCriticalSectionLock	lock(&m_cs);
	HK_TIMER_BEGIN("SfxManager::step",this);
	const hkReal			invrange(1/(m_listenerRange*m_listenerRange));
	hkReal					dt(1);
	m_world->lock();
	dt=m_world->getSolverInfo()->m_deltaTime;
	m_world->unlock();
	/* PreStep												*/ 
	HK_TIMER_BEGIN("preStep",this);	
	m_handler->preStep(dt);
	HK_TIMER_END();

	/* Update tracking										*/ 
	HK_MONITOR_ADD_VALUE("Num Tracked", (float) m_tracking.getSize(), HK_MONITOR_TYPE_INT);
	for(int i=0;i<m_tracking.getSize();++i)
	{
		hkpRigidBody*	body(m_tracking[i]);
		SfxSource*	source(m_handler->attachSource(body));
		if(source)
		{		
			m_tracking.removeAt(i--);
			m_tracked.pushBack(body);
			m_sources.pushBack(source);		
		}
	}
	/* Update sources	*/ 
	HK_MONITOR_ADD_VALUE("Num Sources", (float) m_sources.getSize(), HK_MONITOR_TYPE_INT);
	
	for(int i=0,ni=m_sources.getSize();i<ni;++i)
	{
		SfxSource*	ps(m_sources[i]);
		hkVector4	x(ps->m_position);
		x.sub4(m_position);
		ps->m_fade=1-hkMath::min2(1.0f,hkReal(x.lengthSquared3())*invrange);
		if(ps->m_active)
		{
			if(!ps->update(dt))
			{
				releaseSource(i--);
				--ni;
			}
		}
	}
	/* PostStep												*/ 
	HK_TIMER_BEGIN("postStep",this);
	m_handler->postStep(dt);
	HK_TIMER_END();

	HK_TIMER_END();
}

//
void		SfxManager::setCamera(const hkVector4& from,const hkVector4& dir,const hkVector4& up)
{
	m_handler->setCamera(from,dir,up);
	m_position=from;
	m_world->lock();
	hkAabb	bounds;
	bounds.m_min=m_position;
	bounds.m_max=m_position;
	bounds.m_min.sub4(hkVector4(m_probeRange,m_probeRange,m_probeRange));
	bounds.m_max.add4(hkVector4(m_probeRange,m_probeRange,m_probeRange));
	m_probe.setAabb(bounds);

	// Update the environmental source position
	for ( hkInt32 i = 0; i < m_sources.getSize(); i++ )
	{
		if (m_sources[i]->m_global)
		{
			m_sources[i]->m_position = from;
		}
	}
	m_world->unlock();
}

//
void		SfxManager::appendSource(SfxSource* source)
{
	m_sources.pushBack(source);
	source->addReference();
}

//
bool		SfxManager::releaseTracking(SfxSource* source)
{
	hkpRigidBody*	body(source->m_bodies[0]);
	const int		index(m_tracked.indexOf(body));
	if(index>=0)
	{
		m_tracked.removeAt(index);
		if(m_handler->doTracking(body))
		{
			m_tracking.pushBack(body);
		}
		return(true);
	}
	return(false);
}

//
void		SfxManager::releaseAllSources()
{
	hkCriticalSectionLock	lock(&m_cs);
	m_handler->reset();
	for(int i=m_sources.getSize()-1;i >= 0;--i)
	{
		releaseSource(m_sources[i]);
	}
	m_sources.clear();
}

//
void		SfxManager::releaseSource(SfxSource* source)
{
	hkCriticalSectionLock	lock(&m_cs);
	source->removeReference();
}

//
void		SfxManager::releaseSource(int index)
{
	hkCriticalSectionLock	lock(&m_cs);
	releaseSource(m_sources[index]);
	m_sources.removeAt(index); // does not preserve order
}

//
void		SfxManager::activateIsland(hkpSimulationIsland* island,bool activate)
{
	hkCriticalSectionLock		lock(&m_cs);
	const hkArray<hkpEntity*>&	entities(island->getEntities());
	for(int i=0,ni=m_sources.getSize();i<ni;++i)
	{
		SfxSource*	ps = m_sources[i];
		if(ps->m_active==activate) continue;
		if(	(entities.indexOf(ps->m_bodies[0])!=-1)||
			(entities.indexOf(ps->m_bodies[1])!=-1))
		{
			ps->activate(activate);
		}
	}
}

//
void		SfxManager::entityRemovedCallback(hkpEntity* entity)
{
	hkCriticalSectionLock	lock(&m_cs);
	/* Remove sources with references to 'entity'	*/ 	
	for(int i=m_sources.getSize()-1; i >= 0; --i)
	{
		SfxSource*	source = m_sources[i];
		if(	(source->m_bodies[0]==entity)||
			(source->m_bodies[1]==entity))
		{
			releaseSource(i);
		}
	}
}

//
void		SfxManager::constraintAddedCallback(hkpConstraintInstance* constraint)
{		
	hkCriticalSectionLock	lock(&m_cs);
	if(m_sources.getSize()<m_maxSources)
	{
		SfxSource*			source = m_handler->attachSource(constraint);
		if(source)
		{
			m_sources.pushBack(source);
		}
	}
}

//
void		SfxManager::constraintRemovedCallback(hkpConstraintInstance* constraint)
{
	/* NOTE: Perhaps we need to be smarter here, this called ALOT	*/ 
	hkCriticalSectionLock	lock(&m_cs);
	for(int i=0,ni=m_sources.getSize();i<ni;++i)
	{
		if(m_sources[i]->m_constraint==constraint)
		{
			if(m_sources[i]->detach()) 
			{
				releaseSource(i); //else printf("Orphan source %p\r\n",m_sources[i]);
			}
			break;
		}
	}	
}

//
void		SfxManager::islandActivatedCallback(hkpSimulationIsland* island)
{
	activateIsland(island,true);
}

//
void		SfxManager::islandDeactivatedCallback(hkpSimulationIsland* island)
{
	activateIsland(island,false);
}

//
void		SfxManager::addOverlappingCollidable( hkpCollidable* handle )
{	
	if ( handle->getType() != hkpWorldObject::BROAD_PHASE_ENTITY )
	{
		return;
	}
	hkCriticalSectionLock	lock(&m_cs);
	hkpRigidBody*	body(static_cast<hkpRigidBody*>(handle->getOwner()));
	if(m_handler->doTracking(body))
	{
		m_tracking.pushBack(body);
	}
}

//
void		SfxManager::removeOverlappingCollidable( hkpCollidable* handle )
{
	if ( handle->getType() != hkpWorldObject::BROAD_PHASE_ENTITY )
	{
		return;
	}
	hkCriticalSectionLock	lock(&m_cs);
	hkpRigidBody*	body(static_cast<hkpRigidBody*>(handle->getOwner()));
	int				index;
	index=m_tracking.indexOf(body);
	if(index>=0) m_tracking.removeAt(index);
	index=m_tracked.indexOf(body);
	if(index>=0) m_tracked.removeAt(index);
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
