#include "MemoryStream.h"

namespace IO
{
	MemoryStream::~MemoryStream()
	{
		if ( 0 != m_data1 )
		{
			delete m_data1;
			m_data1 = 0;
		}

		if ( 0 != m_data2 )
		{
			delete m_data2;
			m_data2 = 0;
		}
	}

	void MemoryStream::Write( void* buffer, const int& count )
	{
		int newSize = m_writePosition + count;

		if ( count > 0 )
		{
			if ( 0 == m_data1 )
			{
				m_data1 = new char[ newSize ];
				m_currentData = &m_data1;

				if ( 0 != m_data2 )
				{
					memcpy_s( m_data1, newSize, m_data2, m_writePosition );
					//memcpy( m_data1, m_data2, m_writePosition );
				}

				delete m_data2;
				m_data2 = 0;
			}
			else
			{
				m_data2 = new char[ newSize ];
				m_currentData = &m_data2;

				if ( 0 != m_data1 )
				{
					memcpy_s( m_data2, newSize, m_data1, m_writePosition );
					//memcpy( m_data2, m_data1, m_writePosition );
				}

				delete m_data1;
				m_data1 = 0;
			}
		}

		memcpy_s( ( char*& ) *m_currentData + m_writePosition, newSize, buffer, count );
		//memcpy( ( char*& ) *m_currentData + m_writePosition, buffer, count );
		m_writePosition += count;
	}

	void MemoryStream::Read( void* buffer, const int& count, const int& offset ) const
	{
		memcpy_s( buffer, count, ( char*& ) *m_currentData + offset, count );
		//memcpy( buffer,( char*& ) *m_currentData + m_readPosition, count );
	}

	int MemoryStream::CopyData( void* buffer ) const
	{
		this->Read( buffer, this->GetLength( ), 0 );
		return this->GetLength( );
	}
}