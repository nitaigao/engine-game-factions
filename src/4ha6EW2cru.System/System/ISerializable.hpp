/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ISerializable.hpp
*  @date   2009/08/25
*/
#pragma once
#ifndef ISERIALIZABLE_HPP
#define ISERIALIZABLE_HPP

#include "../IO/IStream.hpp"

#include "../Export.hpp"

namespace System
{
  /*! 
   *  A class that can Serialize / Deserialize itself
   */
  class GAMEAPI ISerializable
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~ISerializable() { };


    /*! Writes the contents of the object to the given stream
    *
    * @param[in] IStream * stream
    * @return (void)
    */
    virtual void Serialize(IO::IStream* stream) = 0;


    /*! Reads the contents of the object from the stream
    *
    * @param[in] IStream * stream
    * @return (void)
    */
    virtual void DeSerialize(IO::IStream* stream) = 0;
    
  };
};

#endif