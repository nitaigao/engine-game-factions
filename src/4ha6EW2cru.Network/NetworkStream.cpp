#include "NetworkStream.h"

namespace Network
{
	static char TERMINATOR = '#';

	void NetworkStream::Write( const float& data )
	{
		MemoryStream::Write( ( void* ) &data, sizeof( float ) );
		MemoryStream::Write( &TERMINATOR, sizeof( TERMINATOR ) );
	}

	void NetworkStream::Read( float& data )
	{
		MemoryStream::Read( ( void* ) &data, sizeof( float ), m_readPosition );	
		m_readPosition += sizeof( float );
		m_readPosition += strlen( &TERMINATOR );
	}

	void NetworkStream::Write( const std::string& data )
	{
		MemoryStream::Write( ( void* ) data.c_str( ), data.length( ) );
		MemoryStream::Write( &TERMINATOR, sizeof( TERMINATOR ) );
	}

	void NetworkStream::Read( std::string& data )
	{
		char* endCharacter = strchr( ( char*& )*m_currentData + m_readPosition, TERMINATOR );

		int readLength = endCharacter - ( ( char*& )*m_currentData + m_readPosition );

		char* buffer = new char[ readLength + sizeof( TERMINATOR ) ];

		MemoryStream::Read( buffer, readLength, m_readPosition );
		m_readPosition += readLength;

		buffer[ readLength ] = '\0';

		if ( readLength > 0 )
		{
			m_readPosition += strlen( &TERMINATOR );
		}

		data.append( buffer );

		delete[ ] buffer;
	}

	void NetworkStream::Write( const Maths::MathVector3& data )
	{
		this->Write( data.X );
		this->Write( data.Y );
		this->Write( data.Z );
	}


	void NetworkStream::Read( Maths::MathVector3& data )
	{
		this->Read( data.X );
		this->Read( data.Y );
		this->Read( data.Z );
	}
}