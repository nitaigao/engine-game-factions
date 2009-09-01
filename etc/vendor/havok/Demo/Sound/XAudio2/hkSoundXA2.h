/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SOUND_XAUDIO2_H
#define HK_SOUND_XAUDIO2_H

#include <Sound/Common/hkSound.h>

#include <xaudio2.h> // 360 + PC DX
#include <xaudio2fx.h>

#include <x3daudio.h>

// May return NULL, or hksSystem->init() may still fail. Remove ref when done with it.
class hksSystem* HK_CALL hksSystemCreateXA2();

#define HKS_XA2_SAFE_RELEASE(x) if (x) { x->Release(); x = HK_NULL; }
#define HKS_XA2_SAFE_DELETE(x) if (x) { delete x; x = HK_NULL; }
#define HKS_XA2_SAFE_DELETE_ARRAY(x) if (x) { delete [] x; x = HK_NULL; }
#define HKS_XA2_SAFE_RELEASE_VOICE(x) if (x) { x->DestroyVoice(); x = HK_NULL; }
#define HKS_XA2_SET_VECTOR( V, X, Y, Z ) do { V.x = X; V.y = Y; V.z = Z; } while (0)  

#endif // HK_SOUND_XAUDIO2_H

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
