/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SOUND_SYSTEM_XA2_INC_H
#define HK_SOUND_SYSTEM_XA2_INC_H

#include <Sound/Common/hksSystem.h>

class hksBufferXA2;
class hksSourceXA2;

class hksSystemXA2 : public hksSystem
{
public:

	hksSystemXA2();
	virtual ~hksSystemXA2();

	// If this returns false, then no need for quit, and the system is not functioning (missing dlls etc)
	virtual bool init();
	virtual void pause(bool paused);
	virtual void recalc();
	virtual void quit();
	virtual void setMasterVolume(hkReal volume);
	virtual int	 getActiveSources();
	virtual void setListener( const hkVector4& pos, const hkVector4& front, const hkVector4& up );
	virtual void setMasterPitchFactor( hkReal pitchFactor );
	virtual hkReal getMasterPitchFactor();

	virtual hksBuffer* createBuffer();
	virtual hksSource* createSource( hkBool global );

	// Internal

	inline IXAudio2* getXAudioPtr() { return m_xa; }
	inline IXAudio2MasteringVoice* getMasterVoice() { return m_masterVoice; } 
	inline IXAudio2SubmixVoice* getSubMixVoice() { return m_submixVoice; }
	inline const XAUDIO2_DEVICE_DETAILS& getDeviceDetails() const { return m_deviceDetails; } 

	void removeBuffer(hksBufferXA2* b);
	void removeSource(hksSourceXA2* s);

protected:

	IXAudio2* m_xa;
	IXAudio2MasteringVoice* m_masterVoice;
	XAUDIO2_DEVICE_DETAILS m_deviceDetails;
	IUnknown* m_reverbEffect;
	IXAudio2SubmixVoice* m_submixVoice;
	X3DAUDIO_HANDLE m_x3DInstance;
	X3DAUDIO_LISTENER m_listener;
	hkReal m_masterPitchFactor;

	hkArray< hksSourceXA2* > m_sources;
	hkArray< hksBufferXA2* > m_buffers;

	HMODULE   m_x3dDll;
};

#endif // HK_SOUND_SYSTEM_XA2_INC_H

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
