/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MathTools.hpp
*  @date   2009/07/28
*/
#pragma once
#ifndef MATHTOOLS_HPP
#define MATHTOOLS_HPP

#include <Common/Base/hkBase.h>

#include <OgreVector3.h>
#include <fmod.hpp>
#include <OgreQuaternion.h>

#include "MathQuaternion.hpp"

namespace Maths
{
	/*! 
	 *  Tools for Conversion between Maths Types
	 */
	class MathTools
	{

	public:


		/*! Returns a Vector created from an Ogre Vector
		*
		* @param[in] const Ogre::Vector3 & vector
		* @return ( Maths::MathVector3 )
		*/
		inline static MathVector3 FromOgreVector3( const Ogre::Vector3& vector )
		{
			return Maths::MathVector3( vector.x, vector.y, vector.z );
		};


		/*! Returns a Vector Created from a Havok Vector
		*
		* @param[in] const hkVector4 & vector
		* @return ( Maths::MathVector3 )
		*/
		inline static MathVector3 FromhkVector4( const hkVector4& vector )
		{
			return Maths::MathVector3( vector( 0 ), vector( 1 ), vector( 2 ) );
		};


		/*! Returns Ogre's representation of a 3 dimensional Vector for convenience
		*
		*  @return (Ogre::Vector3)
		*/
		inline static Ogre::Vector3 AsOgreVector3( const MathVector3& vector )
		{ 
			return Ogre::Vector3( vector.X, vector.Y, vector.Z ); 
		};


		/*! Returns Havok's representation of a 3 dimensional Vector for convenience
		*
		*  @return (hkVector4)
		*/
		inline static hkVector4 AshkVector4( const MathVector3& vector )
		{ 
			return hkVector4( vector.X, vector.Y, vector.Z );
		};


		/*! Returns FMOD's representation of a 3 dimensional Vector for convenience
		*
		*  @return (FMOD_VECTOR)
		*/
		inline static FMOD_VECTOR AsFMODVector( const MathVector3& vector )
		{ 
			FMOD_VECTOR returnValue; 
			returnValue.x = vector.X; 
			returnValue.y = vector.Y; 
			returnValue.z = vector.Z; 
			return returnValue; 
		};


		/*! Returns a Quaternion created from an Ogre::Quaternion
		*
		*  @param[in] const Ogre::Quaternion & quaternion
		*  @return (MathQuaternion)
		*/
		inline static Maths::MathQuaternion FromOgreQuaternion( const Ogre::Quaternion& quaternion )
		{
			return Maths::MathQuaternion( quaternion.x, quaternion.y, quaternion.z, quaternion.w );
		}


		/*! Returns a Quaternion created from a Havoks Quaternion
		*
		*  @param[in] const hkQuaternion & quaternion
		*  @return (MathQuaternion)
		*/
		inline static Maths::MathQuaternion FromhkQuaternion( const hkQuaternion& quaternion )
		{
			return Maths::MathQuaternion( quaternion( 0 ), quaternion( 1 ), quaternion( 2 ), quaternion( 3 ) );
		}


		/*! Returns an Ogre representation the Quaternion for convenience
		*
		*  @return (Ogre::Quaternion)
		*/
		inline static Ogre::Quaternion AsOgreQuaternion( Maths::MathQuaternion& quternion )
		{ 
			return Ogre::Quaternion( quternion.W, quternion.X, quternion.Y, quternion.Z ); 
		};


		/*!  Returns a Havok representation the Quaternion for convenience
		*
		*  @return (hkQuaternion)
		*/
		inline static hkQuaternion AshkQuaternion( Maths::MathQuaternion& quternion )
		{ 
			return hkQuaternion( quternion.X, quternion.Y, quternion.Z, quternion.W ); 
		};

	private:

		~MathTools( ) { };
		MathTools( ) { };
		MathTools( const MathTools & copy ) { };
		MathTools & operator = ( const MathTools & copy ) { return *this; };
		
	};
};

#endif