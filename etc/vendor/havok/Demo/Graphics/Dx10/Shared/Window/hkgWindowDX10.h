/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_GRAPHICS_WINDOW_DX10_H
#define HK_GRAPHICS_WINDOW_DX10_H

#include <Graphics/Common/Window/hkgWindow.h>

// we make all explicit DLL calls as function ptrs so 
// that we cvan dynamically load the dll (if present)
// and handle when it is missing and also simplifiy
// the includes required for the exe.

typedef HRESULT (WINAPI *_D3D10CreateDeviceAndSwapChainFUNC)(
    IDXGIAdapter *pAdapter,
    D3D10_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    UINT SDKVersion,
    DXGI_SWAP_CHAIN_DESC *pSwapChainDesc,
    IDXGISwapChain **ppSwapChain,    
	ID3D10Device **ppDevice);

typedef HRESULT (WINAPI *_CreateDXGIFactoryFUNC)( REFIID riid, void **ppFactory );

typedef HRESULT (WINAPI *_D3D10CompileShaderFUNC)(	LPCSTR pSrcData, SIZE_T SrcDataLen, LPCSTR pFileName, CONST D3D10_SHADER_MACRO* pDefines, LPD3D10INCLUDE pInclude, 
													LPCSTR pFunctionName, LPCSTR pProfile, UINT Flags, ID3D10Blob** ppShader, ID3D10Blob** ppErrorMsgs);

typedef HRESULT (WINAPI *_D3D10GetInputSignatureBlobFUNC)(void *pShaderBytecode, SIZE_T BytecodeLength, ID3D10Blob **ppSignatureBlob);

typedef HRESULT (WINAPI *_D3D10ReflectShaderFUNC)(void *pShaderBytecode, SIZE_T BytecodeLength, ID3D10ShaderReflection **ppReflector);

typedef HRESULT (WINAPI *_D3D10CreateEffectFromMemoryFUNC)( void *pData, SIZE_T DataLength, UINT FXFlags, ID3D10Device *pDevice, 
														   ID3D10EffectPool *pEffectPool, ID3D10Effect **ppEffect);

extern _CreateDXGIFactoryFUNC _CreateDXGIFactory;
extern _D3D10CreateDeviceAndSwapChainFUNC _D3D10CreateDeviceAndSwapChain;
extern _D3D10CompileShaderFUNC _D3D10CompileShader;
extern _D3D10GetInputSignatureBlobFUNC _D3D10GetInputSignatureBlob;
extern _D3D10ReflectShaderFUNC _D3D10ReflectShader;
extern _D3D10CreateEffectFromMemoryFUNC _D3D10CreateEffectFromMemory;

// D3DX
typedef HRESULT (WINAPI *_D3DX10CreateTextureFromMemoryFUNC)( ID3D10Device *pDevice, LPCVOID pSrcData, SIZE_T SrcDataSize, D3DX10_IMAGE_LOAD_INFO *pLoadInfo,
									  ID3DX10ThreadPump *pPump, ID3D10Resource **ppTexture, HRESULT *pHResult );

typedef HRESULT (WINAPI *_D3DX10CompileFromFileFUNC)( LPCSTR pSrcFile,CONST D3D10_SHADER_MACRO* pDefines, LPD3D10INCLUDE pInclude,
														LPCSTR pFunctionName, LPCSTR pProfile, UINT Flags1, UINT Flags2, ID3DX10ThreadPump* pPump, 
														ID3D10Blob** ppShader, ID3D10Blob** ppErrorMsgs, HRESULT* pHResult );

typedef HRESULT (WINAPI *_D3DX10CompileFromMemoryFUNC)( LPCSTR pSrcData, SIZE_T SrcDataLen, LPCSTR pFileName, CONST D3D10_SHADER_MACRO *pDefines, LPD3D10INCLUDE pInclude, 
														LPCSTR pFunctionName, LPCSTR pProfile, UINT Flags1, UINT Flags2, ID3DX10ThreadPump *pPump,
														ID3D10Blob **ppShader, ID3D10Blob **ppErrorMsgs, HRESULT *pHResult );


extern _D3DX10CreateTextureFromMemoryFUNC _D3DX10CreateTextureFromMemory;
extern _D3DX10CompileFromFileFUNC _D3DX10CompileFromFile; // Latest compiler (the normal D3D10.dll one is the orig OS one)
extern _D3DX10CompileFromMemoryFUNC _D3DX10CompileFromMemory;


#define HKG_DX10_DEFAULT_SHADOWMAP_SIZE 512 
#define HKG_DX10_NUM_KNOWN_RENDERTARGETS 8

class hkgWindowDX10ResetEventHandler
{
public:

	virtual void releaseD3D10() = 0;
	virtual void resetD3D10() = 0;
};

class hkgWindowDX10 : public hkgWindow
{
public:

	inline const ID3D10Device* getDevice() const;
	inline ID3D10Device* getDevice();
	inline const IDXGISwapChain* getSwapChain() const;
	inline IDXGISwapChain* getSwapChain();
	inline const ID3D10RenderTargetView* getRenderTargetView() const;
	inline ID3D10RenderTargetView* getRenderTargetView();
	inline const ID3D10Texture2D* getDepthStencil() const;
	inline ID3D10Texture2D* getDepthStencil();
	inline const ID3D10DepthStencilView* getDepthStencilView() const;
	inline ID3D10DepthStencilView* getDepthStencilView();

	virtual hkUint32 vertexShaderMinorVersion() const   { return 0; } 
	virtual hkUint32 vertexShaderMajorVersion() const   { return 4; }		
	virtual hkUint32 geometryShaderMinorVersion() const { return 0; }
	virtual hkUint32 geometryShaderMajorVersion() const { return 4; }
	virtual hkUint32 pixelShaderMinorVersion () const   { return 0; }
	virtual hkUint32 pixelShaderMajorVersion () const   { return 4; }		

	virtual HKG_MESHBLENDING_SUPPORT getMeshBlendingSupport() { return HKG_MESHBLENDING_NOSUPPORT; }//return HKG_MESHBLENDING_HARDWARE; 
	virtual int getMaxBlendMatrices() { return 0; } //20
	virtual int getMaxTextureBlendStages() { return 8; } 

	virtual void buildCommonShaderDefines( hkArray<const char*>& defines );
	virtual bool supportsShaderCompilation() const { return true; } // in core dlls 

	virtual HKG_SHADOWMAP_SUPPORT getShadowMapSupport();
	virtual void prepareForShadowMap(int maxMaps); // creates depth and render target
	virtual void beginShadowMapRender(class hkgDisplayWorld* world, class hkgCamera* camera, class hkgLight* light  ); // sets the depth and render target to be the current
	virtual const class hkgCamera* startShadowMap( int ss, bool clearMap ); // returns the light frustum which is being used to render
	virtual void endShadowMap( int ss, bool blurMap);
	virtual int endShadowMapRender(int textureStageForMap, bool shaderDriven); // resets to the normal depth and render target
	virtual void revertShadowMapState(); // resets to the normal texture modes etc
	virtual void cleanupShadowMap(); // releases held targets
	virtual void setShadowMapSize(int size); 
	virtual int getShadowMapSize() const;
	virtual void enableDebugShadowMapView(bool on) const { m_debugShadowMaps = on; } 
	virtual void setShadowMapSplits( int numSplits );  // if in PSVSM mode, then this will govern the number of maps to use. Otherwise it will do nothing. 1 Split == 2 maps, 2 Splits == 3 maps. Each map can be a seperate additional pass on top of the render pass.

	virtual bool supportsMRT() const { return true; /* msaa makes no difference to MRT support in DX10 */ }

	void setShadowMapQuality( HKG_SHADOWMAP_QUALITY q );
	HKG_SHADOWMAP_QUALITY getShadowMapQuality();

	virtual const float* getComputedShadowMatrix(bool includeCameraViewMatrix, int i) const; // get the perspective shadow matrix
	virtual const float* getComputedShadowTextureMatrix(bool includeCameraViewMatrix, int i) const; // get the perspective shadow matrix with the texture lookup and bias baked in

	virtual int getVideoMemSizeInMB() const;
	virtual int getMaxTextureWidth() const;
	virtual int getMaxTextureHeight() const;
	virtual void getDisplayAdapterDescription(hkString& description) const;

	bool startPostEffects();
	void endPostEffects();

	// debug utils
	void displayShadowMap(int ss);

	void addD3DEventHandler( hkgWindowDX10ResetEventHandler* handler );
	void removeD3DEventHandler( hkgWindowDX10ResetEventHandler* handler );

	virtual bool msaaEnabled() const { return m_msaa; } // MSAA on for RT

	bool getCurrentRTisMultisampled() const { return m_currentRtIsMsaa; }
	void setCurrentRTisMultisampled(bool on);

	ID3D10RenderTargetView* getSceneRenderTargetView( int i, int effectIndex ) const;
	ID3D10ShaderResourceView* getSceneShaderResourceView( int i, int effectIndex ) const; 


protected:


	hkgWindowDX10();
	virtual ~hkgWindowDX10();

	IDXGIAdapter*			m_adapter;
	ID3D10Device*           m_device;
	IDXGISwapChain*         m_swapChain;
	DXGI_SWAP_CHAIN_DESC	m_swapChainDesc;
	ID3D10Texture2D*		m_renderTargetBuffer; //AA render target say (from the swap chain)
	ID3D10RenderTargetView* m_renderTargetView; //AA render target say (from the swap chain)

	ID3D10Texture2D*		m_depthStencil;
	ID3D10DepthStencilView*	m_depthStencilView;

	ID3D10Texture2D*			m_shadowMap[HKG_SHADOWMAP_PSVSM_MAX_NUM_SPLITS + 1];
	ID3D10ShaderResourceView*	m_shadowMapSRView[HKG_SHADOWMAP_PSVSM_MAX_NUM_SPLITS + 1];
	ID3D10RenderTargetView*		m_shadowMapRTView[HKG_SHADOWMAP_PSVSM_MAX_NUM_SPLITS + 1];
	ID3D10SamplerState*			m_shadowMapSamplerState;

	ID3D10Texture2D*			m_shadowMapBlur;
	ID3D10ShaderResourceView*	m_shadowMapBlurSRView;
	ID3D10RenderTargetView*		m_shadowMapBlurRTView;

	bool						m_supportsLinearDepth;
	
	ID3D10Texture2D*			m_linearDepthMapAA;
	ID3D10Texture2D*			m_linearDepthMap; // Non AA
	ID3D10ShaderResourceView*	m_linearDepthMapSRView; // Non AA
	ID3D10RenderTargetView*		m_linearDepthMapRTView; // Non AA

	bool						m_supportsColorMap;
	ID3D10Texture2D*			m_sceneColorMap; // Non AA 
	ID3D10ShaderResourceView*	m_sceneColorMapSRView;
	ID3D10RenderTargetView*		m_sceneColorMapRTView;

	ID3D10Texture2D*			m_sceneColorTempMap; // Non AA 
	ID3D10ShaderResourceView*	m_sceneColorTempMapSRView;
	ID3D10RenderTargetView*		m_sceneColorTempMapRTView;

	ID3D10Texture2D*		m_shadowMapDepthStencil;
	ID3D10DepthStencilView*	m_shadowMapDSView;

	ID3D10RenderTargetView* m_origRTView[HKG_DX10_NUM_KNOWN_RENDERTARGETS];
	ID3D10DepthStencilView*	m_origDSView;

	bool					m_msaa; 
	int						m_msaaSamples;
	int						m_msaaQuality;
	bool					m_currentRtIsMsaa;

	bool					m_vsync; // VSync / VBlank enabled
	int						m_vsyncInterval;

	int						m_shadowMapSize;
	HKG_SHADOWMAP_QUALITY   m_shadowMapQuality;
	bool					m_shadowMultsampled;
	HKG_SHADOWMAP_SUPPORT   m_shadowMapSupport;
	bool					m_shadowNoClearPass;

	HKG_ENABLED_STATE		m_nonShadowState;

	int						m_currentShadowTextureStage;
	mutable float			m_shadowTexMatrix[16];
	mutable float			m_shadowLightMatrix[16];
	mutable bool			m_debugShadowMaps;
	class hkgPixelShaderDX10* m_debugShadowMapPShader;
	class hkgVertexShaderDX10* m_debugShadowMapVShader;

	hkgPixelShaderDX10* m_blurShadowMapPShader;
	hkgVertexShaderDX10* m_blurShadowMapVShader;

	hkArray< hkgWindowDX10ResetEventHandler* > m_eventHandlers;

};

#include <Graphics/Dx10/Shared/Window/hkgWindowDX10.inl>

#endif //HK_GRAPHICS_WINDOW_DX10_H
	

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
