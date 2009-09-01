/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_GRAPHICS_WINDOW_DX9S_H
#define HK_GRAPHICS_WINDOW_DX9S_H

#include <Graphics/Common/Window/hkgWindow.h>

#include <d3dx9.h>

typedef int HKG_WINDOW_DX9S_OPERATING_SYSTEM;
#define HKG_WINDOW_DX9S_OS_UNKNOWN				  0x0
#define HKG_WINDOW_DX9S_OS_CONSOLE				  0x001

#define HKG_WINDOW_DX9S_OS_WINDOWS_9598ME          0x100

#define HKG_WINDOW_DX9S_OS_WINDOWS_VISTA           0x600 // NT 6.0
#define HKG_WINDOW_DX9S_OS_WINDOWS_SERVER_LONGHORN 0x601 // NT 6.0 Server
#define HKG_WINDOW_DX9S_OS_WINDOWS_SERVER_2003_R2  0x522 // NT 5.2 Server2
#define HKG_WINDOW_DX9S_OS_WINDOWS_XP_64           0x520 // NT 5.2
#define HKG_WINDOW_DX9S_OS_WINDOWS_SERVER_2003     0x521 // NT 5.2 Server
#define HKG_WINDOW_DX9S_OS_WINDOWS_XP              0x510 // NT 5.1
#define HKG_WINDOW_DX9S_OS_WINDOWS_2000            0x500 // NT 5.0
#define HKG_WINDOW_DX9S_OS_WINDOWS_NT              0x400 // <= NT 4.0

#define HKG_DIRECTX_SUPPORT_ANISOTROPY 1

// D3DX function poointers (As may not be present in the correct form)

typedef LPCSTR (WINAPI *__D3DXGetVertexShaderProfileFUNC)( LPDIRECT3DDEVICE9 pDevice );
typedef LPCSTR (WINAPI *__D3DXGetPixelShaderProfileFUNC)( LPDIRECT3DDEVICE9 pDevice );

typedef HRESULT (WINAPI *__D3DXCompileShaderFUNC )(
				LPCSTR                          pSrcData,
				UINT                            SrcDataLen,
				CONST D3DXMACRO*                pDefines,
				LPD3DXINCLUDE                   pInclude,
				LPCSTR                          pFunctionName,
				LPCSTR                          pProfile,
				DWORD                           Flags,
				LPD3DXBUFFER*                   ppShader,
				LPD3DXBUFFER*                   ppErrorMsgs,
				LPD3DXCONSTANTTABLE*            ppConstantTable);

typedef HRESULT (WINAPI *__D3DXCompileShaderFromFileAFUNC )( 
				LPCSTR pSrcFile,
				CONST D3DXMACRO*                pDefines,
				LPD3DXINCLUDE                   pInclude,
				LPCSTR                          pFunctionName,
				LPCSTR                          pProfile,
				DWORD                           Flags,
				LPD3DXBUFFER*                   ppShader,
				LPD3DXBUFFER*                   ppErrorMsgs,
				LPD3DXCONSTANTTABLE*            ppConstantTable);


typedef HRESULT (WINAPI *__D3DXCreateEffectFUNC )(
				LPDIRECT3DDEVICE9               pDevice,
				LPCVOID                         pSrcData,
				UINT                            SrcDataLen,
				CONST D3DXMACRO*                pDefines,
				LPD3DXINCLUDE                   pInclude,
				DWORD                           Flags,
				LPD3DXEFFECTPOOL                pPool,
				LPD3DXEFFECT*                   ppEffect,
				LPD3DXBUFFER*                   ppCompilationErrors);

typedef HRESULT (WINAPI *__D3DXCreateCubeTextureFromFileInMemoryFUNC )(
				LPDIRECT3DDEVICE9         pDevice,
				LPCVOID                   pSrcData,
				UINT                      SrcDataSize,
				LPDIRECT3DCUBETEXTURE9*   ppCubeTexture);

typedef HRESULT (WINAPI * __D3DXCreateTextureFromFileInMemoryExFUNC)(
				LPDIRECT3DDEVICE9 pDevice,
				LPCVOID pSrcData,
				UINT SrcDataSize,
				UINT Width,
				UINT Height,
				UINT MipLevels,
				DWORD Usage,
				D3DFORMAT Format,
				D3DPOOL Pool,
				DWORD Filter,
				DWORD MipFilter,
				D3DCOLOR ColorKey,
				D3DXIMAGE_INFO * pSrcInfo,
				PALETTEENTRY * pPalette,
				LPDIRECT3DTEXTURE9 * ppTexture);

typedef HRESULT (WINAPI * __D3DXCreateCubeTextureFromFileInMemoryExFUNC)(
				LPDIRECT3DDEVICE9 pDevice,
				LPCVOID pSrcData,
				UINT SrcDataSize,
				UINT Size,
				UINT MipLevels,
				DWORD Usage,
				D3DFORMAT Format,
				D3DPOOL Pool,
				DWORD Filter,
				DWORD MipFilter,
				D3DCOLOR ColorKey,
				D3DXIMAGE_INFO * pSrcInfo,
				PALETTEENTRY * pPalette,
				LPDIRECT3DCUBETEXTURE9 * ppCubeTexture
				);


typedef HRESULT (WINAPI * __D3DXCreateVolumeTextureFromFileInMemoryExFUNC)(
				LPDIRECT3DDEVICE9 pDevice,
				LPCVOID pSrcData,
				UINT SrcDataSize,
				UINT Width,
				UINT Height,
				UINT Depth,
				UINT MipLevels,
				DWORD Usage,
				D3DFORMAT Format,
				D3DPOOL Pool,
				DWORD Filter,
				DWORD MipFilter,
				D3DCOLOR ColorKey,
				D3DXIMAGE_INFO * pSrcInfo,
				PALETTEENTRY * pPalette,
				LPDIRECT3DVOLUMETEXTURE9 * ppVolumeTexture);

typedef HRESULT (WINAPI * __D3DXLoadSurfaceFromSurfaceFUNC)(
				LPDIRECT3DSURFACE9 pDestSurface,
				CONST PALETTEENTRY * pDestPalette,
				CONST RECT * pDestRect,
				LPDIRECT3DSURFACE9 pSrcSurface,
				CONST PALETTEENTRY * pSrcPalette,
				CONST RECT * pSrcRect,
				DWORD Filter,
				D3DCOLOR ColorKey);

extern __D3DXCompileShaderFUNC			__D3DXCompileShader;
extern __D3DXCompileShaderFromFileAFUNC	__D3DXCompileShaderFromFile;
extern __D3DXCreateEffectFUNC			__D3DXCreateEffect;
extern __D3DXCreateCubeTextureFromFileInMemoryFUNC	__D3DXCreateCubeTextureFromFileInMemory;
extern __D3DXCreateCubeTextureFromFileInMemoryExFUNC __D3DXCreateCubeTextureFromFileInMemoryEx;
extern __D3DXCreateTextureFromFileInMemoryExFUNC	__D3DXCreateTextureFromFileInMemoryEx; 
extern __D3DXCreateVolumeTextureFromFileInMemoryExFUNC	__D3DXCreateVolumeTextureFromFileInMemoryEx; 
extern __D3DXGetPixelShaderProfileFUNC  __D3DXGetPixelShaderProfile;
extern __D3DXGetVertexShaderProfileFUNC __D3DXGetVertexShaderProfile;
extern __D3DXLoadSurfaceFromSurfaceFUNC __D3DXLoadSurfaceFromSurface;

typedef void (WINAPI * __D3D9SXInputEnableFUNC)(
	BOOL enable);

typedef DWORD (WINAPI * __D3D9SXInputGetStateFUNC)(
	DWORD dwUserIndex,
	XINPUT_STATE* pState);

typedef DWORD (WINAPI * __D3D9SXInputSetStateFUNC)(
	DWORD dwUserIndex,
	XINPUT_VIBRATION* pVibration);

typedef DWORD (WINAPI * __D3D9SXInputGetCapabilitiesFUNC)(
	DWORD dwUserIndex,
	DWORD dwFlags,
	XINPUT_CAPABILITIES* pCapabilities);

#if !defined(HK_PLATFORM_XBOX360)
extern __D3D9SXInputEnableFUNC			__D3D9SXInputEnable;
extern __D3D9SXInputGetStateFUNC		__D3D9SXInputGetState;
extern __D3D9SXInputSetStateFUNC		__D3D9SXInputSetState;
extern __D3D9SXInputGetCapabilitiesFUNC	__D3D9SXInputGetCapabilities;
#endif

class hkgWindowDX9SResetEventHandler
{
public:

	virtual void releaseD3D9S() = 0;
	virtual void resetD3D9S() = 0;
};

#define MAX_DX9_RTS 4

class hkgWindowDX9S : public hkgWindow
{
public:

	inline const LPDIRECT3DDEVICE9 getDevice() const;
	inline LPDIRECT3DDEVICE9 getDevice();

	virtual HKG_WINDOW_DX9S_OPERATING_SYSTEM getOperatingSystem() const { return HKG_WINDOW_DX9S_OS_UNKNOWN; }

	inline const D3DCAPS9& getCaps() const;
	inline DWORD getCreateFlags() const; 

	virtual hkUint32 vertexShaderMinorVersion() const { return ( m_d3dCaps.VertexShaderVersion    ) & 0xFF; }
	virtual hkUint32 vertexShaderMajorVersion() const { return ((m_d3dCaps.VertexShaderVersion)>>8) & 0xFF; }		
	virtual hkUint32 pixelShaderMinorVersion() const { return ( m_d3dCaps.PixelShaderVersion     ) & 0xFF; }
	virtual hkUint32 pixelShaderMajorVersion() const { return ((m_d3dCaps.PixelShaderVersion )>>8) & 0xFF; }		

	virtual void buildCommonShaderDefines( hkArray<const char*>& defines );
	virtual bool supportsShaderCompilation() const { return __D3DXCompileShaderFromFile != HK_NULL; }

	// some DX9 specific window commands (for shadowing etc)
	virtual HKG_SHADOWMAP_SUPPORT getShadowMapSupport();
	virtual void prepareForShadowMap(int maxMaps); // creates depth and render target
	virtual void beginShadowMapRender(class hkgDisplayWorld* world, class hkgCamera* camera, class hkgLight* light  ); // sets the depth and render target to be the current
	virtual const class hkgCamera* startShadowMap( int ss, bool clearMap ); // returns the light frustum which is being used to render
	virtual void endShadowMap( int ss, bool blurMap );
	virtual int endShadowMapRender(int textureStageForMap, bool shaderDriven); // resets to the normal depth and render target
	virtual void revertShadowMapState(); // resets to the normal texture modes etc
	virtual void cleanupShadowMap(); // releases held targets
	virtual void setShadowMapSize(int size); 
	virtual int getShadowMapSize() const;
	virtual void enableDebugShadowMapView(bool on) const { m_debugShadowMaps = on; } 
	virtual void setShadowMapSplits( int numSplits );  // if in PSVSM mode, then this will govern the number of maps to use. Otherwise it will do nothing. 1 Split == 2 maps, 2 Splits == 3 maps. Each map can be a seperate additional pass on top of the render pass.

	void setShadowMapQuality( HKG_SHADOWMAP_QUALITY q );
	HKG_SHADOWMAP_QUALITY getShadowMapQuality();

	inline LPDIRECT3DTEXTURE9 getShadowMap(); // an F32 texture
	virtual const float* getComputedShadowMatrix(bool includeCameraViewMatrix, int i) const; // get the perspective shadow matrix
	virtual const float* getComputedShadowTextureMatrix(bool includeCameraViewMatrix, int i) const; // get the perspective shadow matrix with the texture lookup and bias baked in

	virtual HKG_MESHBLENDING_SUPPORT getMeshBlendingSupport() { return HKG_MESHBLENDING_NOSUPPORT; }//return HKG_MESHBLENDING_HARDWARE; 
	virtual int getMaxBlendMatrices() { return 0; } //20 to 50 for sm3, depending 

	virtual int getMaxTextureBlendStages() { return m_d3dCaps.MaxTextureBlendStages; } 

	virtual bool saveFrontFrameBufferToBMP(const char* filename);
	virtual bool saveFrontFrameBufferToStream(unsigned char * str, int stridebytes, int pixelsize);

	virtual int getVideoMemSizeInMB() const { return 256; } // PC will override this
	virtual int getMaxTextureWidth() const { return m_d3dCaps.MaxTextureWidth; }
	virtual int getMaxTextureHeight() const { return m_d3dCaps.MaxTextureHeight; }
	virtual void getDisplayAdapterDescription(hkString& description) const;

		// DX9 does not support MSAA in conjunction with Multiple Render Targets (use DX10 if you want that combo (SSAO with MSAA etc))
	virtual bool supportsMRT() const { return !m_msaa; }
	virtual bool msaaEnabled() const { return m_msaa; } // MSAA on for RT

	virtual bool startPostEffects();
	virtual void endPostEffects() ;

	// debug utils
	void displayShadowMap(int ss);

	const D3DPRESENT_PARAMETERS& getPresentParams() const { return m_d3dpp;  }

	void addD3DEventHandler( hkgWindowDX9SResetEventHandler* handler );
	void removeD3DEventHandler( hkgWindowDX9SResetEventHandler* handler );

	bool m_supportsHWShadowMaps; //Can do Nvidia style depth map lookup
	bool m_supportsR32F; //D3DFMT_R32F
	bool m_supports16F; //D3DFMT_A16B16G16R16F
	bool m_supportsGR32F;//D3DFMT_G32R32F
	bool m_supports32F;//D3DFMT_A32B32G32R32F
	bool m_supportsVSM; // does if it supports some of the fixed or float render targets

	bool m_supports32FBlending;
	bool m_supports16FBlending;
	
	bool getCurrentRTisMultisampled() const { return m_currentRtIsMsaa; }
	void setCurrentRTisMultisampled(bool on) { m_currentRtIsMsaa = on; }

	LPDIRECT3DSURFACE9 getSceneRenderTargetSurface( int i, int effectIndex ) const; // no ref passed (not ref incl, do not call Release())
	LPDIRECT3DTEXTURE9 getSceneRenderTargetTexture( int i, int effectIndex ) const; // no ref passed (not ref incl, do not call Release())

protected:	

	inline hkgWindowDX9S();
	virtual ~hkgWindowDX9S();

	void initShaderCollection();

	LPDIRECT3DDEVICE9		m_pd3dDevice;
	LPDIRECT3D9				m_pD3D;              
	D3DPRESENT_PARAMETERS	m_d3dpp;   
	D3DCAPS9				m_d3dCaps;           // Caps for the device
    DWORD					m_dwCreateFlags;     // Indicate sw or hw vertex processing

	bool					m_msaa; // Antialias enabled
	int						m_msaaQuality;
	int						m_msaaSamples;
	bool					m_currentRtIsMsaa;

	bool					m_vsync; // VSync / VBlank enabled
	int						m_vsyncInterval;

	// shadow map support
	int						m_shadowMapSize;
	HKG_SHADOWMAP_QUALITY   m_shadowMapQuality;
	bool					m_shadowMultsampled;
	HKG_SHADOWMAP_SUPPORT   m_shadowMapSupport;
	bool					m_shadowNoClearPass;

	LPDIRECT3DSURFACE9      m_pShadowZSurfaceEDRAM;  // may be null
	LPDIRECT3DSURFACE9      m_pShadowColorSurfaceEDRAM;  // may be null
	LPDIRECT3DTEXTURE9      m_pShadowColorMap[HKG_SHADOWMAP_PSVSM_MAX_NUM_SPLITS + 1]; 
	LPDIRECT3DTEXTURE9      m_pShadowColorMapBlur; 
	LPDIRECT3DTEXTURE9      m_pShadowZMap; 
	LPDIRECT3DSURFACE9      m_pShadowColorSurface[HKG_SHADOWMAP_PSVSM_MAX_NUM_SPLITS + 1]; // only when { no AA + PSVSM ] and do we have > 1
	LPDIRECT3DSURFACE9      m_pShadowColorSurfaceAA;
	LPDIRECT3DSURFACE9      m_pShadowColorSurfaceBlur;  
	LPDIRECT3DSURFACE9      m_pShadowZSurface;  

	LPDIRECT3DSURFACE9		m_pOrigRT[MAX_DX9_RTS];
	LPDIRECT3DSURFACE9		m_pOrigDS;

	bool					m_supportsLinearDepth;
	bool					m_supportsColorTex;
	LPDIRECT3DSURFACE9		m_pLinearDepthRT;
	LPDIRECT3DSURFACE9		m_pSceneColorRT;
	LPDIRECT3DSURFACE9		m_pBackBufferRT;
	LPDIRECT3DSURFACE9		m_pLinearDepthRTAA;
	LPDIRECT3DSURFACE9		m_pSceneColorRTAA;
	LPDIRECT3DSURFACE9		m_pSceneColorRTTemp;
	LPDIRECT3DSURFACE9	    m_pSceneDS; 

	LPDIRECT3DTEXTURE9		m_pLinearDepthTex;
	LPDIRECT3DTEXTURE9		m_pSceneColorTex;
	LPDIRECT3DTEXTURE9		m_pSceneColorTexTemp;

	HKG_ENABLED_STATE		m_nonShadowState;

	// to help cull and create the optimal shadow map projection matrices
	int						m_currentShadowTextureStage;
	mutable float			m_shadowTexMatrix[16];
	mutable float			m_shadowLightMatrix[16];
	mutable bool			m_debugShadowMaps;
	class hkgPixelShaderDX9S* m_debugShadowMapPShader;
	class hkgVertexShaderDX9S* m_debugShadowMapVShader;
	
	hkgPixelShaderDX9S* m_blurShadowMapPShader;
	hkgVertexShaderDX9S* m_blurShadowMapVShader;

	hkgPixelShaderDX9S* m_xboxCopyShadowMapPShader;
	hkgVertexShaderDX9S* m_xboxCopyShadowMapVShader;

	hkArray< hkgWindowDX9SResetEventHandler* > m_eventHandlers;

	unsigned char* m_framebuffer; ///
	int m_framebufferSize;
};

#include <Graphics/Dx9s/Shared/Window/hkgWindowDX9S.inl>

#endif //HK_GRAPHICS_WINDOW_DX9S_H
	

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
