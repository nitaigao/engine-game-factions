/**/
#pragma once
#ifndef MATHMATRIX_H
#define MATHMATRIX_H

#include <OgreMatrix3.h>
#include <OgreMatrix4.h>

namespace Maths
{
	class MathVector3;

	class MathMatrix : public Ogre::Matrix3
	{

	public:

		MathMatrix( float angle, const MathVector3& axis );

	};

	class MathMatrix4 : public Ogre::Matrix4
	{

	};
};

#endif
