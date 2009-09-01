/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#ifndef HK_GRAPHICS_PARTICLE_DISPLAY_OBJECT_DX10__H
#define HK_GRAPHICS_PARTICLE_DISPLAY_OBJECT_DX10__H

#include <Graphics/Common/DisplayObject/hkgParticleDisplayObject.h>
#include <Graphics/Dx10/Shared/DisplayContext/hkgDisplayContextDX10.h>

class hkgVertexShaderDX10;
class hkgGeometryShaderDX10;
class hkgPixelShaderDX10;

class hkgParticleDisplayObjectDX10 : public hkgParticleDisplayObject
{
	public:

		static hkgParticleDisplayObject* HK_CALL createParticleDisplayObjectDX10( hkgDisplayContext* ctx );

		hkgParticleDisplayObjectDX10( hkgDisplayContext* ctx );

		virtual ~hkgParticleDisplayObjectDX10();

		virtual void setMaxNumParticles( int numParticles, bool allocateBuffers = true );
		
		virtual void setPosition( const float* position, int objectIdx );
		virtual const float* getPosition( int objectIdx ) const;

		virtual void setVelocity( const float* vel, int objectIdx );
		virtual const float* getVelocity( int objectIdx ) const;

		virtual void setUserData( const float* data, int objectIdx );
		virtual const float* getUserData( int objectIdx ) const;

		virtual void render(hkgDisplayContext* context) const;

			// If you provide a Texture aswell as a VB, the renderer will assume
			// you want to do ATI style R2B (stream from the texture)
		void setPositionArray( ID3D10Buffer* vb );
		void setVelocityArray( ID3D10Buffer* vb ); 
		void setUserDataArray( ID3D10Buffer* vb ); 
	
	protected:

		void renderParticlesPoints( hkgDisplayContext* context, hkgVertexShaderDX10* currentVertexProgram, hkgGeometryShaderDX10* currentGeomProgram, hkgPixelShaderDX10* currentFragmentProgram) const;
		
		ID3D10Device* m_device;

		mutable bool m_cpuPosDirty;
		mutable hkArray<float> m_cpuPositions;
		mutable bool m_cpuVelDirty;
		mutable hkArray<float> m_cpuVelocities;
		mutable bool m_cpuUserDirty;
		mutable hkArray<float> m_cpuUserData;

		bool m_userVBOs;
		ID3D10Buffer* m_buffersVB[3];
		
		hkArray<D3D10_INPUT_ELEMENT_DESC> m_posTexDescArray;
		hkArray<D3D10_INPUT_ELEMENT_DESC> m_posTexVelDescArray;
};

#endif // HK_GRAPHICS_PARTICLE_DISPLAY_OBJECT_DX10__H

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
