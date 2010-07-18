/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IStream.hpp
*  @date   2009/08/13
*/
#pragma once
#ifndef ISTREAM_HPP
#define ISTREAM_HPP

#include <string>

//#include "../Maths/MathVector3.hpp"
//#include "../Maths/MathQuaternion.hpp"

#include "../Export.hpp"

namespace IO
{
  /*! 
   *  A Stream interface for storing data
   */
  class GAMEAPI IStream
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~IStream() { };


    /*! Writes a string to the Stream
     *
     * @param[in] const std::string & data
     * @return (void)
     */
    virtual void Write(const std::string& data) = 0;


    /*! Reads a string from the Stream
    *
    * @param[in] const std::string & data
    * @return (void)
    */
    virtual void Read(std::string& data) = 0;


    /*! Writes an integer to the Stream
     *
     * @param[in] int data
     * @return (void)
     */
    virtual void Write(int data) = 0;


    /*! Reads an integer to the Stream
    *
    * @param[in] int data
    * @return (void)
    */
    virtual void Read(int& data) = 0;


    /*! Writes a Vector to the Stream
    *
    * @param[in] const Maths::MathVector3 & data
    * @return (void)
    */
    //virtual void Write(const Maths::MathVector3& data) = 0;


    /*! Reads a Vector from the Stream
     *
     * @param[in] Maths::MathVector3 & data
     * @return (void)
     */
  //  virtual void Read(Maths::MathVector3& data) = 0;


    /*! Writes a Quaternion to the Stream
     *
     * @param[in] const Maths::MathQuaternion & data
     * @return (void)
     */
    //virtual void Write(const Maths::MathQuaternion& data) = 0;


    /*! Reads a Quaternion from the Stream
     *
     * @param[in] Maths::MathQuaternion & data
     * @return (void)
     */
    //virtual void Read(Maths::MathQuaternion& data) = 0;

    
  };
};

#endif