/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_GRAPHICS_POST_EFFECT_DX9S_H
#define HK_GRAPHICS_POST_EFFECT_DX9S_H

#include <Graphics/Common/Shader/hkgPostEffect.h>

#define MAX_EFFECT_RTS 4
class hkgPostEffectDX9S : public hkgPostEffect, public hkgWindowDX9SResetEventHandler
{
public:
		/// Create a blank, platform specific, shader object in the current context as given.
	static hkgPostEffect* createPostEffectDX9S(hkgDisplayContext* context)
	{
		return new hkgPostEffectDX9S(context);
	}	
	
	//class hkgPostEffect:
	virtual const char* getDefaultFileNameExtension() const { return "fx"; }
	virtual bool realize(hkIstream& istream);	
	virtual int getNumSceneRenderTargets(); 
	virtual void applyPostClear();
	virtual bool applyPostScene(int m_postEffectIndex);
	virtual void free();	

	virtual void setFloatInputByName( const char* name, const float* v, int numV );
	
	virtual int  getNumFloatInputs( ) const;
	virtual const char* getFloatInputName( int i ) const;
	virtual int getFloatInputSize( int i ) const; // in num floats
	virtual bool getFloatInputValue( int i, float* v, int maxSize ) const;

	//class hkgWindowDX9SResetEventHandler:

	virtual void releaseD3D9S(); // invalidate
	virtual void resetD3D9S(); // restore

protected:		
	
	bool createResources();
	bool executePostScript(const char* str); //DXSAS script
	bool executePassScript(const char* str);
	void wipeTargets();

	hkgPostEffectDX9S(hkgDisplayContext* context);
	virtual ~hkgPostEffectDX9S();
		
	LPDIRECT3DDEVICE9	m_pDevice;

	struct ID3DXEffect*	m_pEffect;
	
	int m_postEffectIndex;
	hkgShader* m_wipeTargetsVS;
	hkgShader* m_wipeTargetsPS;

	D3DXHANDLE m_viewportParam;

	D3DXHANDLE m_sceneColorTextureHandle;
	D3DXHANDLE m_linearDepthTextureHandle;

	struct TextureMap
	{
		LPCSTR name;
		LPDIRECT3DTEXTURE9 texture;
		UINT w;
		UINT h;
	};

	TextureMap* findTexture(const char* name);
	hkArray<TextureMap> m_textures;

	D3DXCOLOR m_clearColor0;
	D3DXCOLOR m_clearColor1;

};

#endif // HK_GRAPHICS_POST_EFFECT_DX9S_H

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
