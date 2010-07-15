/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file  MathQuaternion.hpp
*  @date   2009/04/26
*/
#pragma once
#ifndef MATHQUATERNION_H
#define MATHQUATERNION_H

#include "MathVector3.hpp"

namespace Maths
{
  /*! 
   *  Representation of a Maths Quaternion
   */
  class MathQuaternion
  {

  public:

    float X, Y, Z, W;

    /*! Default Constructor returning an IDENTITY Quaternion
     *
     *  @return ()
     */
    MathQuaternion()
      : X(0)
      , Y(0)
      , Z(0)
      , W(1)
    {

    }


    /*! Constructs from an Angle / Axis pair
     *
     *  @param[in] MathVector3 axis
     *  @param[in] float angle
     *  @return ()
     */
    MathQuaternion(const MathVector3& axis, float angle)
    {
      W = cos(0.5 * angle);
      X = sin(0.5 * angle) * axis.X; 
      Y = sin(0.5 * angle) * axis.Y; 
      Z = sin(0.5 * angle) * axis.Z; 

    }


    /*! Constructs from real values 
     *
     *  @param[in] float x
     *  @param[in] float y
     *  @param[in] float z
     *  @param[in] float w
     *  @return ()
     */
    MathQuaternion(float x, float y, float z, float w)
      : X(x)
      , Y(y)
      , Z(z)
      , W(w)
    {

    }
    

    /*! Returns a Normalized version of the Quaternion
     *
     *  @return (Maths::MathQuaternion)
     */
    inline MathQuaternion Normalize() const 
    {
      float length = sqrt(
        X * X + Y * Y +
        Z * Z + W * W
       );

      return MathQuaternion(
        X / length,
        Y / length,
        Z / length,
        W / length
       );
    };


    /*! Fills the specified angle / axis pair with the Angle / Axis representation of
     * the Quaternion
     *
     *  @param[out] float & angle
     *  @param[out] MathVector3 & axis
     *  @return (void)
     */
    inline void ToAngleAxis(float& angle, MathVector3& axis) const
    {
      float squaredLength = X * X + Y * Y + Z * Z;

      if(squaredLength> 0.0f)
      {
        angle = 2.0f * acos(W);
        float inverseLength = 1.0f / sqrt(squaredLength);
        
        axis = MathVector3(
          X * inverseLength,
          Y * inverseLength,
          Z * inverseLength
         );
      }
      else
      {
        angle = 0.0f;
        axis = MathVector3(1.0f, 0.0f, 0.0f);
      }
    }

    /*! Returns whether or not the input Quaternion does matches this Quaternion
    *
    * @param[in] const MathQuaternion & input
    * @return (bool)
    */
    inline bool operator == (const MathQuaternion& input) const
    {
      return (
        input.X == X,
        input.Y == Y,
        input.Z == Z,
        input.W == W
       );
    }

    
    /*! Returns whether or not the input Quaternion does not match this Quaternion
    *
    * @param[in] const MathQuaternion & input
    * @return (bool)
    */
    inline bool operator != (const MathQuaternion& input) const
    {
      return !(*this == input);
    }


    /*! Returns the Dot Product of the Quaternion and the specified input
     *
     *  @param[in] const MathQuaternion & input
     *  @return (Maths::MathQuaternion)
     */
    inline MathQuaternion operator * (const MathQuaternion& input) const
    {
      return MathQuaternion(
        W * input.X + X * input.W + Y * input.Z - Z * input.Y,
        W * input.Y + Y * input.W + Z * input.X - X * input.Z,
        W * input.Z + Z * input.W + X * input.Y - Y * input.X,
        W * input.W - X * input.X - Y * input.Y - Z * input.Z
     );
    };


    /*! Returns a version of the Vector that has been multiplies by the input Quaternion
    *
    *  @param[in] const MathQuaternion & input
    *  @return (Maths::MathVector3)
    */
    inline MathVector3 operator * (const MathVector3& input) const
    {
      MathVector3 qVector(X, Y, Z);

      MathVector3 uv = qVector.CrossProduct(input) * (2.0f * W);
      MathVector3 uuv = qVector.CrossProduct(uv) * 2.0f;

      return input + uv + uuv;
    }


    
    /*! Converts the quaternion to text values
     *
     * @param[in] std::ostream & stream
     * @param[in] const MathQuaternion & input
     * @return (friend std::ostream&)
     */
    friend std::ostream& operator <<(std::ostream& stream, const MathQuaternion& input) 
    {
      stream <<"X:" <<input.X <<" Y:" <<input.Y <<" Z:" <<input.Z <<" W:" <<input.W;
      return stream;
    }


    /*! Returns an IDENTITY Quaternion
     *
     *  @return (Maths::MathQuaternion)
     */
    static MathQuaternion Identity() { return MathQuaternion(); }; 

  };
};

#endif
