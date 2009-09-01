/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_GRAPHICS_POST_EFFECT_H
#define HK_GRAPHICS_POST_EFFECT_H

#include <Graphics/Common/Shader/hkgShader.h>

class hkgPostEffect : public hkgReferencedObject
{
public:

	/// Create a blank, platform specific, shader object in the current context as given.
	static hkgPostEffect* (HK_CALL* create)(class hkgDisplayContext* owner); 

	virtual const char* getDefaultFileNameExtension() const { return ""; }
	
	// by default will call realize() below
	virtual bool realizeFromFile( const char* path );

	// parse the file and create any platform resources required.
	virtual bool realize(hkIstream& istream) { return false; }

	// return #rts used from main scene render (each has HKG meaning, 0 == scene color, 1 == linear depth )
	virtual int getNumSceneRenderTargets() { return 0; } 

	// clear extra rts to specific values (full screen quad normaly)
	virtual void applyPostClear() { }  

	// Do the actual work
	virtual bool applyPostScene(int postEffectIndex) { return false; } 

	// release all platform resources.
	virtual void free() {} 	

	inline void setName(const char* n) { m_name = n; }
	inline const char* getName() const { return m_name.cString(); }

		// Assumed this is persistant, so only need to set once per new val
	virtual void setFloatInputByName( const char* name, const float* v, int numV ) { }
	virtual int  getNumFloatInputs( ) const { return 0; }
	virtual const char* getFloatInputName( int i ) const { return HK_NULL; }
	virtual int getFloatInputSize( int i ) const { return 0; /* floats */ }
	virtual bool getFloatInputValue( int i, float* v, int maxSize ) const { return false; }


protected:		

	hkgPostEffect(hkgDisplayContext* context);
	
	hkgWindow* m_owner;
	hkString m_name;
	
};

#endif // HK_GRAPHICS_POST_EFFECT_H

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
