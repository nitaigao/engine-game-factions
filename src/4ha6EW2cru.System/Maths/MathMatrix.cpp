#include "precompiled.h"
/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MathMatrix.cpp
*  @date   2009/04/26
*/
#include "MathMatrix.h"
#include "MathVector3.hpp"
#include "MathTools.hpp"

namespace Maths
{
  /*! 
   *  Representation of a Maths Matrix
   */
  MathMatrix::MathMatrix(float angle, const MathVector3& axis)
  {
    MathVector3 ax = const_cast<MathVector3&>(axis);
    this->FromAxisAngle(MathTools::AsOgreVector3(ax), Ogre::Radian(angle));
  }
}