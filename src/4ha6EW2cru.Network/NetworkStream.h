/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkStream.h
*  @date   2009/08/13
*/
#pragma once
#ifndef NETWORKSTREAM_H
#define NETWORKSTREAM_H

#include "IO/IStream.hpp"
#include <BitStream.h>

#include "Export.hpp"

namespace Network
{


  /*! 
   *  A Stream that can cross the Network
   */
  class GAMEAPI NetworkStream : public IO::IStream
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    ~NetworkStream( ) { };


    /*! Default Constructor
    *
    * @return (  )
    */
    NetworkStream( RakNet::BitStream* bitStream )
      : m_bitStream( bitStream )
    {

    }


    /*! Writes an integer to the Stream
    *
    * @param[in] int data
    * @return ( void )
    */
    void Write( int data );


    /*! Reads an integer to the Stream
    *
    * @param[in] int data
    * @return ( void )
    */
    void Read( int& data );


    /*! Writes a string to the Stream
    *
    * @param[in] const std::string & data
    * @return ( void )
    */
    void Write( const std::string& data );


    /*! Reads a string from the Stream
    *
    * @param[in] const std::string & data
    * @return ( void )
    */
    void Read( std::string& data );


    /*! Writes a Vector to the Stream
    *
    * @param[in] const Maths::MathVector3 & data
    * @return ( void )
    */
    void Write( const Maths::MathVector3& data );


    /*! Reads a Vector from the Stream
    *
    * @param[in] Maths::MathVector3 & data
    * @return ( void )
    */
    void Read( Maths::MathVector3& data );


    /*! Writes a Quaternion to the Stream
    *
    * @param[in] const Maths::MathQuaternion & data
    * @return ( void )
    */
    void Write( const Maths::MathQuaternion& data );


    /*! Reads a Quaternion from the Stream
    *
    * @param[in] Maths::MathQuaternion & data
    * @return ( void )
    */
    void Read( Maths::MathQuaternion& data );

  private:

    NetworkStream( const NetworkStream & copy ) { };
    NetworkStream & operator = ( const NetworkStream & copy ) { return *this; };

    RakNet::BitStream* m_bitStream;
    
  };
};

#endif