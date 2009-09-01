/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_GRAPHICS_SKINNEDINSTANCED_DISPLAY_OBJECT_H
#define HK_GRAPHICS_SKINNEDINSTANCED_DISPLAY_OBJECT_H

#include <Graphics/Common/DisplayObject/hkgInstancedDisplayObject.h>

class hkgSkinnedInstancedDisplayObject : public hkgInstancedDisplayObject 
{
	public:

		static hkgSkinnedInstancedDisplayObject* (HK_CALL *create)( hkgDisplayContext* ctx );

		
		virtual void setBlendMatrices( int instance, int subFaceSetPrim, hkgBlendMatrixSet* matrices ) = 0; // all sub faces cal share the same set or combo of sets
		virtual hkgBlendMatrixSet* getBlendMatrices( int instance, int subFaceSet ) = 0;

		virtual void onGeometryChange(); 

			// As instance 0 may have blend matrices implicitly setup already, 
			// it can be handy just to copy that setup to all the other instances
			// will only do up to current num objects
		void copyBlendMatrices( hkgDisplayContext* ctx, int sourceInstance );

		int getNumSubFaceSetPrims() const { return m_numSubFaceSetPrims; }
		hkgFaceSetPrimitive* getSubFacePrimitive( int index );

	protected:

		inline hkgSkinnedInstancedDisplayObject( )
			: hkgInstancedDisplayObject(), m_numSubFaceSetPrims(0)
		{
			setStatusFlags( getStatusFlags() | HKG_DISPLAY_OBJECT_SKINNEDINSTANCED );
		}
		
		int m_numSubFaceSetPrims;
};

#endif // HK_GRAPHICS_INSTANCED_DISPLAY_OBJECT_H


/*
* Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20090704)
* 
* Confidential Information of Havok.  (C) Copyright 1999-2009
* Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
* Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
* rights, and intellectual property rights in the Havok software remain in
* Havok and/or its suppliers.
* 
* Use of this software for evaluation purposes is subject to and indicates
* acceptance of the End User licence Agreement for this product. A copy of
* the license is included with this software and is also available at www.havok.com/tryhavok.
* 
*/
