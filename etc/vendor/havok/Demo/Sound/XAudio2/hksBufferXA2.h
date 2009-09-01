/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SOUND_BUFFER_XA2_INC_H
#define HK_SOUND_BUFFER_XA2_INC_H

#include <Sound/Common/hksBuffer.h>

#ifdef HK_PLATFORM_XBOX360
typedef hkUint32 FOURCC, *PFOURCC, *LPFOURCC;
#endif

struct RIFFHEADER
{
	FOURCC fccChunkId;
	hkUint32 dwDataSize;
};

#define HKS_RIFFCHUNK_FLAGS_VALID   0x00000001

class hksRiffChunk
{

public:

	hksRiffChunk();

	// Initialization
	VOID    init( FOURCC fccChunkId, const hksRiffChunk* pParentChunk, hkIstream& s);
	
	hkResult open();
	
	inline hkBool isValid() const {	return (m_flags & HKS_RIFFCHUNK_FLAGS_VALID) != 0; }
	
	hkResult readData( hkUint32 offset, void* data, hkUint32 dataSize ) const;

	FOURCC getChunkId() const
	{
		return m_fccChunkId;
	}

	hkUint32 getDataSize() const
	{
		return m_dataSize;
	}

protected:
	
	FOURCC m_fccChunkId;       // Chunk identifier
	const hksRiffChunk* m_parentChunk;     // Parent chunk
	hkIstream* m_stream;
	hkUint32 m_dataOffset;     // Chunk data offset
	hkUint32 m_dataSize;       // Chunk data size
	hkUint32 m_flags;          // Chunk flags

private:

	hksRiffChunk( const hksRiffChunk& );
	hksRiffChunk& operator =( const hksRiffChunk& );
};

class hksBufferXA2 : public hksBuffer
{
public:

	virtual ~hksBufferXA2();

	virtual hkResult loadFromFile( const char* file );

	virtual hkResult loadWav( hkIstream& wstream );

	inline hkUint32 getWaveDataSize() const { return m_waveDataSize; }
	inline const hkUint8* getWaveDataPtr() const { return m_waveData; } 

	inline const WAVEFORMATEXTENSIBLE* getFormat() const { return &m_format; }

protected:

	friend class hksSystemXA2;
	hksBufferXA2(hksSystemXA2* owner);

	hksSystemXA2* m_owner;
	
	hkResult getFormat( WAVEFORMATEXTENSIBLE* pwfxFormat, XMA2WAVEFORMATEX* pXma2Format ) const;
	hkResult readSample( hkUint32 dwPosition, void* pBuffer, hkUint32 dwBufferSize, hkUint32* pdwRead ) const;
	
	hksRiffChunk m_riffChunk;        // RIFF chunk
	hksRiffChunk m_formatChunk;      // Format chunk
	hksRiffChunk m_dataChunk;        // Data chunk
	hksRiffChunk m_waveSampleChunk;  // Wave Sample chunk
	hksRiffChunk m_samplerChunk;     // Sampler chunk

	WAVEFORMATEXTENSIBLE m_format;

	hkUint32 m_waveDataSize;
	hkUint8* m_waveData; 

};
#endif // HK_SOUND_BUFFER_XA2_INC_H

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
