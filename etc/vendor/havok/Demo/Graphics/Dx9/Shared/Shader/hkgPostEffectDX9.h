/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_GRAPHICS_POST_EFFECT_DX9_H
#define HK_GRAPHICS_POST_EFFECT_DX9_H

#include <Graphics/Common/Shader/hkgPostEffect.h>

class hkgPostEffectDX9 : public hkgPostEffect, public hkgWindowDX9ResetEventHandler
{
public:
		/// Create a blank, platform specific, shader object in the current context as given.
	static hkgPostEffect* createPostEffectDX9(hkgDisplayContext* context)
	{
		return new hkgPostEffectDX9(context);
	}	
	
	//class hkgPostEffect:
	virtual const char* getDefaultFileNameExtension() const { return "fx"; }
	virtual bool realize(hkIstream& istream);	
	virtual bool applyPreScene(); 
	virtual bool applyPostScene();
	virtual void free();	

	//class hkgWindowDX9ResetEventHandler:

	virtual void releaseD3D9(); // invalidate
	virtual void resetD3D9(); // restore
	
protected:		
	
	bool createResources();
	bool executePreScript(const char* str); //DXSAS script
	bool executePostScript(const char* str); //DXSAS script
	bool executePassScript(const char* str);
	bool apply(bool post);

	hkgPostEffectDX9(hkgDisplayContext* context);
	virtual ~hkgPostEffectDX9();
		
	LPDIRECT3DDEVICE9	m_pDevice;
	LPDIRECT3DSURFACE9	m_pOrigRT;
	LPDIRECT3DSURFACE9	m_pOrigDS;
	struct ID3DXEffect*	m_pEffect;
	LPCSTR m_viewportParam;
	bool m_haveChangedRT;
	bool m_haveChangedDS;
	struct TextureMap
	{
		LPCSTR name;
		LPDIRECT3DTEXTURE9 texture;
		UINT w;
		UINT h;
	};

	TextureMap* findTexture(const char* name);
	hkArray<TextureMap> m_textures;
};

#endif // HK_GRAPHICS_POST_EFFECT_DX9_H

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
