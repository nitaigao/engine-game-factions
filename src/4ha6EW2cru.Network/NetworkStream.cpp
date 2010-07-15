#include "precompiled.h"

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

  void NetworkStream::Write( const Maths::MathVector3& data )
  {
    m_bitStream->Write( data.X );
    m_bitStream->Write( data.Y );
    m_bitStream->Write( data.Z );
  }

  void NetworkStream::Write( const Maths::MathQuaternion& data )
  {
    m_bitStream->Write( data.X );
    m_bitStream->Write( data.Y );
    m_bitStream->Write( data.Z );
    m_bitStream->Write( data.W );
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

  void NetworkStream::Read( Maths::MathVector3& data )
  {
    m_bitStream->Read( data.X );
    m_bitStream->Read( data.Y );
    m_bitStream->Read( data.Z );
  }

  void NetworkStream::Read( Maths::MathQuaternion& data )
  {
    m_bitStream->Read( data.X );
    m_bitStream->Read( data.Y );
    m_bitStream->Read( data.Z );
    m_bitStream->Read( data.W );
  }
}