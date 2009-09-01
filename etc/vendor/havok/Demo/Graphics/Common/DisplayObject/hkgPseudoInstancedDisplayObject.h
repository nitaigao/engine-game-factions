/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_GRAPHICS_PSEUDO_INSTANCED_DISPLAY_OBJECT_H
#define HK_GRAPHICS_PSEUDO_INSTANCED_DISPLAY_OBJECT_H

#include <Graphics/Common/DisplayObject/hkgDisplayObject.h>

extern const hkClass hkgPseudoInstancedDisplayObjectClass;

class hkgInstancedDisplayObject;

class hkgPseudoInstancedDisplayObject : public hkgDisplayObject 
{
	public:

			/// Creates a platform specific display object.
		static hkgPseudoInstancedDisplayObject* (HK_CALL *create)();

			/// Default create function, use ::create instead.
		inline static hkgPseudoInstancedDisplayObject* defaultCreateInternal() { return new hkgPseudoInstancedDisplayObject(); }

			// Will return a new pseudo version referencing the same instanced obj
		virtual hkgDisplayObject* copy( HKG_DISPLAY_OBJECT_COPY_FLAGS f, hkgDisplayContext* ctx ) const;

		virtual void render(hkgDisplayContext* context) const { /* does nothing, you have to render the main wrapped object. The display world will do this for u. */ }

		inline hkgInstancedDisplayObject* getWrappedObject() { return m_mainObject; }
		inline const hkgInstancedDisplayObject* getWrappedObject() const { return m_mainObject; }

		void setWrappedObject(hkgInstancedDisplayObject* o);

	protected:

		hkgPseudoInstancedDisplayObject();
		virtual ~hkgPseudoInstancedDisplayObject();

	public:

		hkgInstancedDisplayObject* m_mainObject;
};

#endif // HK_GRAPHICS_PSEUDO_INSTANCED_DISPLAY_OBJECT_H

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
