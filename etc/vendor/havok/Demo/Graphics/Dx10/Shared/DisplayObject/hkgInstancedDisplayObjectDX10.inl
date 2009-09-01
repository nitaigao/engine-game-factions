/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


inline hkgInstancedDisplayObject* hkgInstancedDisplayObjectDX10::createInstancedDisplayObjectDX10( hkgDisplayContext* ctx )
{
	return new hkgInstancedDisplayObjectDX10( (hkgDisplayContextDX10*)ctx );
}

hkgInstancedDisplayObjectDX10::hkgInstancedDisplayObjectDX10( hkgDisplayContextDX10* ctx )
: hkgInstancedDisplayObject(), m_device( ctx->getDevice() ), m_createdOwnBuffers(false)
{
	// disable DX10 hardware instancing
	m_ownerWindow = (hkgWindowDX10*)( ctx->getOwner() );

	m_enableHardwareInstancing = true;

	m_cpuTransformsDirty = false;
	m_curBuffer = 0;
	m_instanceTransforms[0] = HK_NULL;
	m_instanceTransforms[1] = HK_NULL;

	setStatusFlags( getStatusFlags() | HKG_DISPLAY_OBJECT_DYNAMIC | HKG_DISPLAY_OBJECT_NOT_CULLED | HKG_DISPLAY_OBJECT_USER_AABB);
}

hkgInstancedDisplayObjectDX10::~hkgInstancedDisplayObjectDX10()
{
	SAFE_RELEASE(m_instanceTransforms[0]);
	SAFE_RELEASE(m_instanceTransforms[1]);
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
