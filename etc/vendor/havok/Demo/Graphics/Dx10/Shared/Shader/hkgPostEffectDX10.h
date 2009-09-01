/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_GRAPHICS_POST_EFFECT_DX10_H
#define HK_GRAPHICS_POST_EFFECT_DX10_H

#include <Graphics/Common/Shader/hkgPostEffect.h>

#define HKG_DX10_MAX_EFFECT_RTS 8
class hkgPostEffectDX10 : public hkgPostEffect, public hkgWindowDX10ResetEventHandler
{
public:
		/// Create a blank, platform specific, shader object in the current context as given.
	static hkgPostEffect* createPostEffectDX10(hkgDisplayContext* context)
	{
		return new hkgPostEffectDX10(context);
	}	
	
	//class hkgPostEffect:
	virtual const char* getDefaultFileNameExtension() const { return "fx"; }
	virtual bool realize(hkIstream& istream);	
	virtual int getNumSceneRenderTargets(); 
	virtual void applyPostClear();
	virtual bool applyPostScene(int postEffectIndex);

	virtual void free();	

	virtual void setFloatInputByName( const char* name, const float* v, int numV );

	virtual int  getNumFloatInputs( ) const;
	virtual const char* getFloatInputName( int i ) const;
	virtual int getFloatInputSize( int i ) const; // in num floats
	virtual bool getFloatInputValue( int i, float* v, int maxSize ) const;

	// hkgWindowDX10ResetEventHandler
	virtual void releaseD3D10();
	virtual void resetD3D10();

protected:		
	
	bool createResources();
	void freeResources();

	bool executeScript(ID3D10EffectPass* pass, const char* str); //DXSAS script
	bool executePostScript(ID3D10EffectTechnique* t); 
	
	void wipeTargets(ID3D10RenderTargetView** curRTView);

	
	hkgPostEffectDX10(hkgDisplayContext* context);
	virtual ~hkgPostEffectDX10();
			
	bool m_needProjMatrix;
	bool m_needProjInvMatrix;

	ID3D10Device*   m_device;
	ID3D10Blob*		m_byteCode;   
	ID3D10Effect*	m_effect;
	
	ID3D10EffectVariable* m_viewportParam;
	ID3D10EffectVariable* m_sceneColorTextureHandle;
	ID3D10EffectVariable* m_linearDepthTextureHandle;

	ID3D10Buffer* m_drawBuffer;
	ID3D10InputLayout* m_drawBufferInputLayoutPT;

	D3D10_VIEWPORT m_curViewport;
	UINT m_origWidth;
	UINT m_origHeight;

	int m_postEffectIndex;

public: 

	struct TextureMap
	{
		LPCSTR name;
		UINT w;
		UINT h;

		ID3D10Texture2D* texture;
		
		ID3D10EffectShaderResourceVariable* textureVar;
		
		ID3D10ShaderResourceView* textureSRV; // not null
		ID3D10RenderTargetView*   textureRTV; // may be null
		ID3D10DepthStencilView*	  textureDSV; // may be null

		bool newBind;
		int boundToRTStage; // -1 == none
		int boundToDSStage; // -1 == none
	};

protected:

	TextureMap* findTexture(const char* name);
	TextureMap* findBoundRtTex( int rt );
	TextureMap* findBoundDsTex( );
	void allBound( );

	hkArray<TextureMap> m_textures;
	
	float m_clearColor0[4];
	float m_clearColor1[4];
};

#endif // HK_GRAPHICS_POST_EFFECT_DX10_H

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
