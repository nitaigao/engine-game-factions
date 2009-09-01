/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HKBASE_ARRAY_STREAMWRITER_H
#define HKBASE_ARRAY_STREAMWRITER_H

#include <Common/Base/System/Io/Writer/hkStreamWriter.h>


/// Class which handles large memory streams in memory
class hkMemoryTrack
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkMemoryTrack );

		/// Ctor
		hkMemoryTrack( int numBytesPerSector = 512 );

		~hkMemoryTrack();

		/// clear the stream
		void clear();

		/// append numBytes to the stream
		void write ( const void* data, int numBytes );

		/// Append other stream to this one, will free the memory used in the other track
		void appendByMove( hkMemoryTrack* other );

		// returns the number of bytes
		int getSize() const 
		{
			return (m_sectors.getSize() - 1) * m_numBytesPerSector + m_numBytesLastSector;
		}

		/// read numBytes from offset
		void read( void* data, int numBytes, int offset ) const ;


		//
		//	Member variables
		//
	public:
		int m_numBytesPerSector;	///
		int m_numBytesLastSector;	///

		hkArray<hkUint8*> m_sectors;	///
};


/// Writer which uses an hkMemoryTrack as its storage.
class hkMemoryTrackStreamWriter : public hkStreamWriter
{
	public:

		enum TrackOwnership
		{
			TRACK_TAKE,
			TRACK_BORROW
		};


		/// Create an hkMemoryTrackStreamWriter which writes in to the memory track m_track.
		/// If o is TRACK_TAKE, this object owns the array and will destroy
		/// it in this objects destructor. If o is TRACK_BORROW, the track
		/// will not be deleted.
		hkMemoryTrackStreamWriter(hkMemoryTrack* track, TrackOwnership o)
			: m_track(track), m_ownerShip(o)
		{
		}


		~hkMemoryTrackStreamWriter()
		{
			if( m_ownerShip == TRACK_TAKE )
			{
				delete m_track;
			}
		}

		virtual void clear();

		virtual int write(const void* mem, int size);

		virtual hkBool isOk() const
		{
			return true;
		}

		virtual hkBool seekTellSupported() const {	return false;	}
		virtual hkResult seek(int offset, SeekWhence whence){ return HK_FAILURE; }
		virtual int tell() const{	return m_track->getSize();	}

	protected:

		hkMemoryTrack* m_track;
		TrackOwnership m_ownerShip;
};



#include <Common/Base/System/Io/Reader/hkStreamReader.h>

/// Wraps a reader around a memory track.
class hkMemoryTrackStreamReader : public hkStreamReader
	{
	public:

		///
		enum MemoryType
		{
			MEMORY_COPY,
			MEMORY_TAKE,
			MEMORY_INPLACE
		};

		/// Create a stream from the specified track.
		/// MEMORY_TAKE will take ownership of the memory (which was
		/// allocated with hkAllocate) and hkDeallocate it on destruction.
		/// MEMORY_INPLACE will use the memory in place
		/// and must exist for the lifetime of this object.
		hkMemoryTrackStreamReader(const hkMemoryTrack* track, MemoryType t);

		~hkMemoryTrackStreamReader();

		virtual int read(void* buf, int nbytes);

		virtual int skip( int nbytes){ m_offset += nbytes; return nbytes; }

		virtual hkBool isOk() const{ return m_offset <= m_track->getSize(); }

		/// Marks up to buffer size are supported.
		virtual hkBool markSupported() const{ return false; }

		/// Marks up to buffer size are supported.
		virtual hkResult setMark(int markLimit){ return HK_FAILURE; }

		/// Marks up to buffer size are supported.
		virtual hkResult rewindToMark(){ return HK_FAILURE; }

		/// Seek/tell is supported.
		virtual hkBool seekTellSupported() const{ return false; }

		virtual hkResult seek(int offset, SeekWhence whence){ return HK_FAILURE; }

		virtual int tell() const{ return m_offset; }

	protected:

		const hkMemoryTrack* m_track;
		int m_offset;
		MemoryType m_memType; // owned or referenced
};


/// Writer which uses an hkArray as its storage.
/// The written buffer area is from [0, hkArray.getSize()]
/// This class maintains a single null byte directly after
/// the buffer area so the the buffer may be interpreted
/// as a c style string.
class hkArrayStreamWriter : public hkStreamWriter
{
	public:

		enum ArrayOwnership
		{
			ARRAY_TAKE,
			ARRAY_BORROW
		};

		void nullTerminate()
		{
			m_arr->reserve(m_arr->getSize()+1);
			m_arr->begin()[ m_arr->getSize() ] = 0;
		}

		void* getData() { return m_arr->begin(); }
		int getDataSize() { return m_arr->getSize(); }

			/// Create an hkStreamWriter which writes in to the array *arr.
			/// The write position is initially set to the end of the array.
			/// If o is ARRAY_TAKE, this object owns the array and will destroy
			/// it in this objects destructor. If o is ARRAY_BORROW, the array
			/// will not be deleted.
		hkArrayStreamWriter(hkArray<char>* arr, ArrayOwnership o)
			: m_arr(arr), m_offset(arr->getSize()), m_ownerShip(o)
		{
			nullTerminate();
		}


		~hkArrayStreamWriter()
		{
			if( m_ownerShip == ARRAY_TAKE )
			{
				delete m_arr;
			}
		}

		virtual void clear();

		virtual int write(const void* mem, int size);

		virtual hkBool isOk() const
		{
			return true;
		}

		virtual hkBool seekTellSupported() const
		{
			return true;
		}

		virtual hkResult seek(int offset, SeekWhence whence);

		virtual int tell() const
		{
			return m_offset;
		}

	protected:

		hkArray<char>* m_arr; // written chars always in area 0,getSize()
		int m_offset; // invariant: m_offset <= m_arr.getSize()
		ArrayOwnership m_ownerShip;
};

#endif // HKBASE_ARRAY_STREAMWRITER_H


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
