/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SOUND_BUFFER_INC_H
#define HK_SOUND_BUFFER_INC_H

class hksBuffer : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO);
		
		// By default this will just understand .wav and forward that.
		// For XMA/WMA/etc, override this and deal with them accordingly.
		// We will come up with a master set of support files once we have
		// more platforms impls
		virtual hkResult loadFromFile( const char* file );

		// PC and 360 support both PCM wav files. PC supports ADPCM too.
		// Other platforms may vary.
		virtual hkResult loadWav( class hkIstream& wstream ) = 0;		
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
