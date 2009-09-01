/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SOUND_SYSTEM_INC_H
#define HK_SOUND_SYSTEM_INC_H

class hksBuffer;
class hksSource;

class hksSystem : public hkReferencedObject
{
public:

	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO);
	
	// If this returns false, then no need for quit, and the system is not functioning (missing dlls etc)
	// Can call init() / quit() as many times as you like. It should be clean.
	// Quit will force all buffers etc to be invalid, so do not use buffers etc after quit(), before init().
	virtual bool init() = 0;

	virtual void pause(bool paused) = 0;
	
	virtual void recalc() = 0; // call every couple of frames at least. No need for every frame

	virtual void quit() = 0;

	virtual int	getActiveSources()=0;

	virtual void	setMasterVolume(hkReal volume)=0;

	virtual void setMasterPitchFactor(hkReal pitch)=0;
	virtual hkReal getMasterPitchFactor()=0;
	

	// Where we are listening from (the camera normaly). In world space.
	virtual void setListener( const hkVector4& pos, const hkVector4& front, const hkVector4& up ) = 0;
	
	virtual hksBuffer* createBuffer() = 0;
	virtual hksSource* createSource( hkBool global = false ) = 0;
	
};

#endif // HK_SOUND_BUFFER_INC_H

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
