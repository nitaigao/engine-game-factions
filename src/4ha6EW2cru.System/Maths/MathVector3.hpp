/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MathVector3.hpp
*  @date   2009/04/26
*/
#pragma once
#ifndef MATHVECTOR3_H
#define MATHVECTOR3_H

#include "MathUnits.hpp"
#include "MathMatrix.h"

namespace Maths
{
  /*! 
   *  A Representation of a 3 Dimensional Maths Vector
   */
  class MathVector3
  {

  public:

    typedef std::deque<MathVector3> MathVector3List;

    float X, Y, Z;

    /*! Default Constructor, returns a Zero Vector
     *
     *  @return ()
     */
    MathVector3()
      : X(0)
      , Y(0)
      , Z(0)
    {

    }


    /*! Constructs from input values
     *
     *  @param[in] float x
     *  @param[in] float y
     *  @param[in] float z
     *  @return ()
     */
    MathVector3(float x, float y, float z)
      : X(x)
      , Y(y)
      , Z(z)
    {

    }


    /*! Returns the Dot Product of the Vector and the specified input
     *
     *  @param[in] const MathVector3 & input
     *  @return (float)
     */
    inline float DotProduct(const MathVector3& input) const
    {
      return X * input.X + Y * input.Y + Z * input.Z;
    }

    
    /*! Returns the length of the Vector
     *
     *  @return (float)
     */
    inline float Length() const
    {
      return sqrt(X * X + Y * Y + Z * Z);
    }


    /*! Returns a version of this vector that has been interpolated with the given input by the given amount
    *
    *  @param[in] const MathVector3 & input
    *  @param[in] float amount
    *  @return (MathVector3)
    */
    inline MathVector3 Interpolate(const MathVector3& input, float amount)
    {
      MathVector3 positionDifference = input - *this;
      return *this + (positionDifference * amount);
    }


    /*! Returns the Cross Product of the Vector and the specified input
     *
     *  @param[in] const MathVector3 & input
     *  @return (Maths::MathVector3)
     */
    inline MathVector3 CrossProduct(const MathVector3& input) const
    {
      return MathVector3(
        Y * input.Z - Z * input.Y,
        Z * input.X - X * input.Z,
        X * input.Y - Y * input.X
        );
    }


    /*! Returns a Normalized version of the Vector
     *
     *  @return (Maths::MathVector3)
     */
    inline MathVector3 Normalize() const
    {
      float length = sqrt(X * X + Y * Y + Z * Z );

      return (length> 0.0f) 
        ? MathVector3(X, Y, Z) / length
        : MathVector3(X, Y, Z);
    }


    /*! Rounds the Vector Values to the nearest whole number
    *
    * @return (Maths::MathVector3)
    */
    inline MathVector3 Round() const
    {
      return MathVector3(
        MathUnits::Round(X),
        MathUnits::Round(Y),
        MathUnits::Round(Z)
        );
    }


    /*! Divides the Vector by the specified input
     *
     *  @param[in] const float & input
     *  @return (Maths::MathVector3)
     */
    inline MathVector3 operator / (float input) const
    {
      return MathVector3(
        X / input,
        Y / input,
        Z / input
        );
    }


    /*! Returns a version of the Vector that has been added to the input
     *
     *  @param[in] const MathVector3 & input
     *  @return (Maths::MathVector3)
     */
    inline MathVector3 operator + (const MathVector3& input) const
    {
      return MathVector3(
        input.X + X,
        input.Y + Y,
        input.Z + Z
        );
    };


    /*! Returns a version of the Vector that has been added to the input
     *
     *  @param[in] const MathVector3 & input
     *  @return (Maths::MathVector3)
     */
    inline MathVector3 operator += (const MathVector3& input) const
    {
      return *this + input;
    };


    /*! Returns a version of the Vector that has been subtracted from the input
     *
     *  @param[in] const MathVector3 & input
     *  @return (Maths::MathVector3)
     */
    inline MathVector3 operator - (const MathVector3& input) const
    {
      return MathVector3(
        X - input.X,
        Y - input.Y,
        Z - input.Z
        );
    };


    /*! Returns a version of the Vector that has been multiplied by the input scalar
     *
     *  @param[in] const float & input
     *  @return (Maths::MathVector3)
     */
    inline MathVector3 operator * (float input) const
    {
      return MathVector3(
        input * X,
        input * Y,
        input * Z
        );
    };


    /*! Returns a version of the Vector that has been multiplied by the input Vector
     *
     *  @param[in] const MathVector3 & input
     *  @return (Maths::MathVector3)
     */
    inline MathVector3 operator * (const MathVector3& input) const
    {
      return MathVector3(
        X * input.X,
        Y * input.Y,
        Z * input.Z
        );
    };


    /*! Returns whether the vector values match the input vector values
    *
    * @param[in] const MathVector3 & input
    * @return (bool)
    */
    inline bool operator == (const MathVector3& input) const
    {
      return (
        X == input.X && 
        Y == input.Y &&
        Z == input.Z);
    }


    /*! Returns whether the vector values do not match the input vector values
    *
    * @param[in] const MathVector3 & input
    * @return (bool)
    */
    inline bool operator != (const MathVector3& input) const
    {
      return !(* this == input);
    }


    /*! Converts the vector to text values
     *
     * @param[in] std::ostream & stream
     * @param[in] const MathVector3 & vector
     * @return (friend std::ostream&)
     */
    friend std::ostream& operator <<(std::ostream& stream, const MathVector3& input) 
    {
      stream <<"X:" <<input.X <<" Y:" <<input.Y <<" Z:" <<input.Z;
      return stream;
    }


    /*! Returns a version of the Vector that has been multiplied by the input Matrix
     *
     *  @param[in] const MathMatrix & input
     *  @return (Maths::MathVector3)
     */
    /*inline MathVector3 operator * (const MathMatrix& input) const
    {
      return MathTools::AsOgreVector3(this) * input;
    }*/


    /*! Returns a Vector pointing UP
     *
     *  @return (Maths::MathVector3)
     */
    static inline MathVector3 Up() { return MathVector3(0.0f, 1.0f, 0.0f); };


    /*! Returns a Vector pointing FORWARD
     *
     *  @return (Maths::MathVector3)
     */
    static inline MathVector3 Forward() { return MathVector3(0.0f, 0.0f, -1.0f); };


    /*! Returns a Zero Vector
     *
     *  @return (Maths::MathVector3)
     */
    static inline MathVector3 Zero() { return MathVector3(0.0f, 0.0f, 0.0f); };

  };
};

#endif
