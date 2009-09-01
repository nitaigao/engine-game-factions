/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_GRAPHICS_SKINNED_INSTANCED_DISPLAY_OBJECT_DX10__H
#define HK_GRAPHICS_SKINNED_INSTANCED_DISPLAY_OBJECT_DX10__H

#include <Graphics/Common/DisplayObject/hkgSkinnedInstancedDisplayObject.h>

#include <Graphics/Dx10/hkGraphicsDX10.h>
#include <Graphics/Dx10/Shared/DisplayContext/hkgDisplayContextDX10.h>
#include <Graphics/Dx10/Shared/Window/hkgWindowDX10.h>

class hkgSkinnedInstancedDisplayObjectDX10 : public hkgSkinnedInstancedDisplayObject
{
	public:

		static hkgSkinnedInstancedDisplayObject* HK_CALL createSkinnedInstancedDisplayObjectDX10( hkgDisplayContext* ctx );

			/// special render call to make use of DirectX hardware instancing support in Shader Specification 3.0
		virtual void render( hkgDisplayContext* context ) const;

			/// special picking support. But will intersect with the displayt object transformed BIND pose, not the proper current SKIN POSE.
		virtual int intersect( const hkgRay& ray, bool ignoreBackfaces, hkgDisplayObjectPickData& data) const;

			/// set the total number of instanced objects, must be called BEFORE cloning or rendering ( finalises the VBO )
			/// No need to call if you are going to use replace buffers anyway
		virtual void setMaxNumObjects( int numObjects, bool allocateBuffers = true );

		virtual void setRenderMode(HKG_INSTANCED_DISPLAY_MODE mode);
		
			/// adds a shallow copy (shares hkgGeometry down) with the same transform and same flags to m_displayObjects
		virtual hkgDisplayObject* clone( float* transform = HK_NULL );

		virtual void setTransform( const float* transform, int objectIdx );

		virtual const float* getTransform( int objectIdx ) const;

		virtual void setBlendMatrices( int instance, int subFaceSetPrim, hkgBlendMatrixSet* matrices );
		virtual hkgBlendMatrixSet* getBlendMatrices( int instance, int subFaceSetPrim );

	protected:

		inline hkgSkinnedInstancedDisplayObjectDX10( hkgDisplayContextDX10* ctx );
		virtual ~hkgSkinnedInstancedDisplayObjectDX10();

		hkArray<float> m_cpuTransforms;
		class hkgWindowDX10* m_ownerWindow;

		hkArray< class hkgInstanceMatrices* > m_perInstanceBlendMatrices;
};

#endif // HK_GRAPHICS_SKINNED_INSTANCED_DISPLAY_OBJECT_DX10__H


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
