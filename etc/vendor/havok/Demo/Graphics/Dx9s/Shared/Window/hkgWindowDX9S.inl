/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

hkgWindowDX9S::hkgWindowDX9S()
: hkgWindow(), m_pd3dDevice(HK_NULL), m_pD3D(NULL), m_dwCreateFlags(0), 
    m_supportsHWShadowMaps(false), m_supportsR32F(false), m_supports16F(false),
	m_supportsGR32F(false), m_supports32F(false), m_supportsVSM(false), 
	m_supports32FBlending(false), m_supports16FBlending(false),
	m_shadowMapSize(0),m_shadowMapQuality(HKG_SHADOWMAP_QUALITY_UNKNOWN), m_shadowMultsampled(false),
	m_shadowMapSupport(HKG_SHADOWMAP_NOTKNOWN),m_shadowNoClearPass(false),
	m_pShadowZSurfaceEDRAM(HK_NULL), m_pShadowColorSurfaceEDRAM(HK_NULL),
	m_pShadowZMap(HK_NULL),
	m_pShadowColorMapBlur(HK_NULL), 
	m_pShadowZSurface(HK_NULL), 
	m_pShadowColorSurfaceBlur(HK_NULL), 
	m_pShadowColorSurfaceAA(HK_NULL),
	m_debugShadowMaps(false),
	m_debugShadowMapVShader(HK_NULL),m_debugShadowMapPShader(HK_NULL),
	m_blurShadowMapVShader(HK_NULL), m_blurShadowMapPShader(HK_NULL),
	m_xboxCopyShadowMapPShader(HK_NULL), m_xboxCopyShadowMapVShader(HK_NULL),
	m_framebuffer(HK_NULL), m_framebufferSize(0)
{
	for (int s=0; s <= HKG_SHADOWMAP_PSVSM_MAX_NUM_SPLITS; ++s )
	{
		m_pShadowColorMap[s] = HK_NULL;
		m_pShadowColorSurface[s] = HK_NULL;
	}

	m_msaa = false;
	m_msaaSamples = 4;
	m_msaaQuality = 0;

	m_vsync = false;
	m_vsyncInterval = 1;

	m_pLinearDepthRT= HK_NULL;
	m_pSceneColorRT= HK_NULL;
	m_pBackBufferRT= HK_NULL;
	m_pLinearDepthRTAA= HK_NULL;
	m_pSceneColorRTAA= HK_NULL;
	m_pSceneColorRTTemp= HK_NULL;
	m_pSceneDS= HK_NULL;

	m_pLinearDepthTex= HK_NULL;
	m_pSceneColorTex= HK_NULL;
	m_pSceneColorTexTemp= HK_NULL;

	m_supportsLinearDepth = true;
	m_supportsColorTex = true;

}

inline const LPDIRECT3DDEVICE9 hkgWindowDX9S::getDevice() const
{
	return m_pd3dDevice;
}

inline LPDIRECT3DDEVICE9 hkgWindowDX9S::getDevice()
{
	return m_pd3dDevice;
}

inline const D3DCAPS9& hkgWindowDX9S::getCaps() const
{ 
	return m_d3dCaps; 
}

inline DWORD hkgWindowDX9S::getCreateFlags() const
{
	return m_dwCreateFlags;
}

inline LPDIRECT3DTEXTURE9 hkgWindowDX9S::getShadowMap()
{
	return m_pShadowZMap;
}

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
