/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SOUND_SOURCE_XA2_INC_H
#define HK_SOUND_SOURCE_XA2_INC_H

#include <Sound/Common/hksSource.h>

#define HKS_MAX_NUM_XA2_OUTPUTCHANNELS 8 // support up to 7.1
#define HKS_NUM_XA2_INPUTCHANNELS 1 // mono sources for the moment

class hksSourceXA2 : public hksSource, public IXAudio2VoiceCallback
{
public:
	virtual ~hksSourceXA2();

	virtual bool attachBuffer( hksBuffer* buf, bool isLoop=true );
	virtual bool detachBuffers();	

	virtual void setPosition( const hkVector4& p );
	virtual void setVelocity( const hkVector4& v );
	virtual void setPitch( hkReal pitch);
	virtual void setVolume( hkReal volume);
	virtual void setInnerRadius( hkReal radius);
	virtual void setDistanceScale(hkReal scale);
	virtual void setVelocityScale(hkReal scale);
	
	virtual void start(PlayMode mode = HKS_PLAY_LOOP);
	virtual void pause();
	
	virtual void stop();

	virtual PlayState	getState() const;
	virtual int			loopCount() const;

	void update();

	inline IXAudio2SourceVoice* getVoice() { return m_voice; }
	inline X3DAUDIO_EMITTER* getEmitter() { return &m_emitter; } 
	inline X3DAUDIO_DSP_SETTINGS* getDspSettings() { return &m_dspSettings; }

	virtual hkBool isGlobal() { return m_global; }

private:
	void __stdcall 	OnVoiceProcessingPassStart(UINT32 BytesRequired)	{}
	void __stdcall	OnVoiceProcessingPassEnd()							{}
	void __stdcall	OnStreamEnd()										{ ++m_loops; }
	void __stdcall	OnBufferStart(void* pBufferContext)					{}
	void __stdcall	OnBufferEnd(void* pBufferContext)					{ m_playState = hksSource::HKS_STOPPED; }
	void __stdcall	OnLoopEnd(void* pBufferContext)						{ ++m_loops;if(m_once) stop(); }
	void __stdcall	OnVoiceError(void* pBufferContext,HRESULT Error)	{}
protected: 

	friend class hksSystemXA2;
	hksSourceXA2(hksSystemXA2* owner, hkBool global=false);

	hksSystemXA2* m_owner;

	IXAudio2SourceVoice* m_voice;
	PlayState m_playState;
	hkUint32 m_attachedBuffers;

	FLOAT32 m_emitterAzimuths[HKS_NUM_XA2_INPUTCHANNELS];
	FLOAT32 m_matrixCoefficients[HKS_MAX_NUM_XA2_OUTPUTCHANNELS];
	hkReal	m_pitch;
	hkReal	m_volume;
	int		m_loops;
	bool	m_once;
	bool	m_global;
	
	X3DAUDIO_DSP_SETTINGS m_dspSettings;
	X3DAUDIO_EMITTER m_emitter;
	X3DAUDIO_CONE m_emitterCone;
};

#endif // HK_SOUND_SOURCE_XA2_INC_H

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
