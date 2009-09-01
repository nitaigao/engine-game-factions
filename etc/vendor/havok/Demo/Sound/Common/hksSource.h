/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SOUND_SOURCE_INC_H
#define HK_SOUND_SOURCE_INC_H

class hksSource : public hkReferencedObject
{
public:

	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO);

	virtual bool attachBuffer( class hksBuffer* buf, bool isLoop=true ) = 0;
	virtual bool detachBuffers() = 0;	

	enum PlayState
	{
		HKS_ERROR,
		HKS_ERROR_NOBUFFER,
		HKS_STOPPED,
		HKS_PLAYING,
		HKS_PAUSED
	};

	enum PlayMode
	{
		HKS_PLAY_ONCE,
		HKS_PLAY_LOOP
	};

	// The world space position of the sound
	virtual void setPosition( const hkVector4& p ) = 0;
	// The velocity of the sound source
	virtual void setVelocity( const hkVector4& v ) = 0;
	// The pitch of the sound source (0=stopped, 1=normal speed, ...)
	virtual void setPitch( hkReal pitch) = 0;
	// The volume of the sound source
	virtual void setVolume( hkReal volume)=0;
	// The the inner radius of the sound source
	virtual void setInnerRadius( hkReal radius)=0;
	// The distance curve scale
	virtual void setDistanceScale(hkReal scale)=0;
	// The velocity curve scale (affect doppler)
	virtual void setVelocityScale(hkReal scale)=0;
	// Returns true if the voice is not localized in space
	virtual hkBool isGlobal()=0;

	virtual void start(PlayMode mode = HKS_PLAY_LOOP) = 0;
	virtual void pause() = 0;
	virtual void stop() = 0;
	virtual int  loopCount() const=0;

	virtual PlayState getState() const = 0;

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
