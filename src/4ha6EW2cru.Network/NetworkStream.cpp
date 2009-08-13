#include "NetworkStream.h"

#include <RakString.h>
using namespace RakNet;

namespace Network
{
	void NetworkStream::Write( const std::string& data )
	{ 
		 m_bitStream->Write( RakString( data ) ); 
	}

	void NetworkStream::Write( int data )
	{
		m_bitStream->Write( data );
	}

	void NetworkStream::Read( std::string& data )
	{
		RakString returnValue;
		m_bitStream->Read( returnValue );
		data = returnValue.C_String( );
	}

	void NetworkStream::Read( int& data )
	{
		m_bitStream->Read( data );
	}
}