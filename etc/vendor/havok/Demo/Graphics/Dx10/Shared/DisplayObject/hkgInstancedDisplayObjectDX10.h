/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_GRAPHICS_INSTANCED_DISPLAY_OBJECT_DX10__H
#define HK_GRAPHICS_INSTANCED_DISPLAY_OBJECT_DX10__H

#include <Graphics/Common/DisplayObject/hkgInstancedDisplayObject.h>

#include <Graphics/Dx10/hkGraphicsDX10.h>
#include <Graphics/Dx10/Shared/DisplayContext/hkgDisplayContextDX10.h>
#include <Graphics/Dx10/Shared/Window/hkgWindowDX10.h>

class hkgInstancedDisplayObjectDX10 : public hkgInstancedDisplayObject
{
	public:

		inline static hkgInstancedDisplayObject* HK_CALL createInstancedDisplayObjectDX10( hkgDisplayContext* ctx );

			/// special render call to make use of DirectX hardware instancing support in Shader Specification 3.0
		virtual void render( hkgDisplayContext* context ) const;

			/// special picking support
		virtual int intersect( const hkgRay& ray, bool ignoreBackfaces, hkgDisplayObjectPickData& data) const;

			/// set the total number of instanced objects, must be called BEFORE cloning or rendering ( finalises the VBO )
			/// No need to call if you are going to use replace buffers anyway
		virtual void setMaxNumObjects( int numObjects, bool allocateBuffers = true );

		virtual void setRenderMode(HKG_INSTANCED_DISPLAY_MODE mode);
		
			/// adds a shallow copy (shares hkgGeometry down) with the same transform and same flags to m_displayObjects
		virtual hkgDisplayObject* clone( float* transform = HK_NULL );

		virtual void setTransform( const float* transform, int objectIdx );

		virtual void setTransforms( const float* allTransforms, int numTransforms, int startTransform );

		virtual const float* getTransform( int objectIdx ) const;

			// take the transforms form an externaly created vertex buf source.
			// Will resize m_numObjects etc to suit size of rows.
		void replaceTransformBuffer( ID3D10Buffer* trans );

		inline bool doingHwInstancedRendering() const { return m_instanceTransforms[0] && m_enableHardwareInstancing; }

	protected:

		inline hkgInstancedDisplayObjectDX10( hkgDisplayContextDX10* ctx );
		inline virtual ~hkgInstancedDisplayObjectDX10();

		mutable bool m_cpuTransformsDirty;
		hkArray<float> m_cpuTransforms;
		mutable float m_tempTransform[16];
		
		ID3D10Device* m_device;
		class hkgWindowDX10* m_ownerWindow;

		// an array of floats representing the per instance ( 4 x 4 ) transforms ( gathered from the clones )
		bool m_createdOwnBuffers;
		bool m_enableHardwareInstancing;
		mutable int m_curBuffer;
		mutable ID3D10Buffer* m_instanceTransforms[2]; // 2 for ping pong usuage
};

#include <Graphics/Dx10/Shared/DisplayObject/hkgInstancedDisplayObjectDX10.inl>

#endif // HK_GRAPHICS_INSTANCED_DISPLAY_OBJECT_DX10__H


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
