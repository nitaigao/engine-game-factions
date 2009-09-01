/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_GRAPHICS_BRIDGE_ASSET_CONV_H
#define HK_GRAPHICS_BRIDGE_ASSET_CONV_H

#include <Common/SceneData/Material/hkxMaterial.h>

class hkgMaterial;
class hkgShaderLib;

/// A collection of asset conversion utilities
class hkgAssetConverter
{
	public:

		enum ConvertMask
		{
			CONVERT_ALL = 0,
			NO_MESHES = 1,
			NO_LIGHTS = 1<<1,
			NO_MATERIALS = 1<<2,
			NO_TEXTURES = 1<<3,
			NO_CAMERAS = 1<<4,
			NO_SHADOW_CAST = 1<<5,
			NO_VERTEX_COLORS = 1<<6,
			FORCE_VERTEX_COLORS = 1<<7,
			FORCE_DYNAMIC_VBS = 1<<8,
			FORCE_DIFFUSE_MAT_ONLY = 1<<9,
			FORCE_WHITE_DIFFUSE_COLOR = 1<<10,
			FORCE_BLACK_SPECULAR_COLOR = 1<<11,
			// For the shader lib, so it can pixck the correct # lights
			// 1 and 2 lights are default / normal, so only 0 or > 2 are required normally as hints 
			HINT_0RENDERLIGHT = 1<<12,
			HINT_1RENDERLIGHT = 1<<13,
			HINT_2RENDERLIGHTS = 1<<14,
			HINT_3RENDERLIGHTS = 1<<15,
			HINT_4RENDERLIGHTS = 1<<16
		};

		struct Mapping
		{
			HKG_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( Mapping );

			Mapping() : m_origObject(HK_NULL), m_hkgObject(HK_NULL) { }
			const void* m_origObject; //The original object from the toolchain e.g. hkxCamera
			hkgReferencedObject* m_hkgObject; //The runtime graphics object we build e.g. hkgCamera
		};

		struct NodeMapping
		{
			HKG_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( Mapping);

			NodeMapping() : m_origNode(HK_NULL), m_hkgObject(HK_NULL) { }
			const class hkxNode* m_origNode; //The original node from the toolchain
			hkgReferencedObject* m_hkgObject; //The runtime graphics object we build e.g. hkgCamera
		};

		struct SkinPaletteMap
		{
			HKG_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( SkinPaletteMap);

			SkinPaletteMap() : m_skin(HK_NULL) { }
			class hkgDisplayObject* m_skin;
			hkArray< class hkgBlendMatrixSet* > m_palettes;
		};

		struct IndexMapping
		{
			hkInt16* m_mapping;
			hkInt32 m_numMapping;
		};

		struct MaterialCache
		{
			HKG_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( MaterialCache);

			MaterialCache() : m_manager(HK_NULL), m_supportsShaders(false) { m_searchOrder.pushBack(HK_NULL); m_searchOrder.pushBack("DDS"); m_searchOrder.pushBack("png"); m_searchOrder.pushBack("PNG"); }
			~MaterialCache();
			class hkgMaterialManager* m_manager;
			bool m_supportsShaders;
			hkgArray<Mapping> m_materials;	
			hkgArray<Mapping> m_textures;
			hkgArray<const char*> m_searchPaths;
			hkgArray<const char*> m_searchOrder;
		};

		enum MaterialVariants
		{
			MAT_NORMAL,
			MAT_SKIN,
			MAT_INSTANCE
		};

		struct MeshConvertInput
		{
			HKG_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( MeshConvertInput);

			MeshConvertInput() : m_enableLighting(true), m_allowMaterialSharing(true), m_allowTextureSharing(true), m_allowTextureMipmaps(true),
								   m_allowTextureCompression(false), m_allowTextureAnisotropicFilter(false), m_invertNormalMapGreenChannel(false), 
								   m_allowHardwareSkinning(true), m_allowPseudoInstancing(false), m_allowPseudoInstancingHardwareAccel(false), m_convMask(CONVERT_ALL), 
								   m_context(HK_NULL), m_materialCache(HK_NULL), m_meshCache(HK_NULL), m_nodeCache(HK_NULL), m_skinVertexBufferCache(HK_NULL), m_shaderLib(HK_NULL)
			{
				m_worldTransform.setIdentity();
			}
			hkBool m_enableLighting;
			hkBool m_allowMaterialSharing; // share hkgMaterial ptrs
			hkBool m_allowTextureSharing;  // share hkgTexture ptrs
			hkBool m_allowTextureMipmaps;
			hkBool m_allowTextureCompression;
			hkBool m_allowTextureAnisotropicFilter;
			hkBool m_invertNormalMapGreenChannel;
			hkBool m_allowHardwareSkinning;
			hkBool m_forceVertexColors;
			hkBool m_allowPseudoInstancing; 
			hkBool m_allowPseudoInstancingHardwareAccel; 
			ConvertMask m_convMask;

			class hkgDisplayContext* m_context; 
			class hkgDisplayWorld* m_world; // for pseudo instances, we may need to replace already added objects 

			MaterialCache*			m_materialCache;			///
			hkgArray<Mapping>*		m_meshCache;				///
			hkgArray<NodeMapping>*	m_nodeCache;				///
			hkgArray<Mapping>*		m_skinVertexBufferCache;	///

			hkMatrix4 m_worldTransform;

			hkgShaderLib* m_shaderLib; // may be null
		};

		struct MeshConvertOutput
		{
			MeshConvertOutput(){ m_materialIndicesToClean = HK_NULL; }
			hkBool m_wasSkin;
			hkgArray<hkgMaterial*>* m_materialIndicesToClean;
		};

		/// materialIndicesToClean - an array of material pointers that need to be cleaned up.
		/// The caller of this function is responsible for cleaning the materials up, if necessary
		static class hkgDisplayObject* HK_CALL convertMesh( const class hkxMesh* mesh, const MeshConvertInput& input, MeshConvertOutput& output );

		static int HK_CALL convertMaterial( const class hkxMaterial* material, hkgDisplayContext* context, MaterialCache& materialCache,
											hkBool allowMatSharing, hkBool allowTexSharing, hkBool doMipmaps, hkBool doCompression, hkBool doAniso, 
											hkBool invertNormalMaps, hkBool diffuseOnly, hkBool forceWhiteDiffuse, hkBool forceBlackSpecular,
											hkgShaderLib* shaderLib, int forNumLights, MaterialVariants matVariant );

		static int HK_CALL convertTexture(  const class hkxTextureInplace* texture, hkgDisplayContext* context, hkxMaterial::TextureType tHint, 
											MaterialCache& materialCache, hkBool allowTexSharing, hkBool doMipmaps, hkBool doCompression, hkBool doAniso, hkBool invertNormalMaps   );

		static int HK_CALL convertTexture(  const class hkxTextureFile* texture, hkgDisplayContext* context, hkxMaterial::TextureType tHint,
											MaterialCache& materialCache, hkBool allowTexSharing, hkBool doMipmaps, hkBool doCompression, hkBool doAniso, hkBool invertNormalMaps   );

		static class hkgLight* HK_CALL convertLight( const class hkxLight* l, class hkgLightManager* manager );

		static class hkgCamera* HK_CALL convertCamera( const class hkxCamera* camera, const char* name );

		static SkinPaletteMap* HK_CALL setupHardwareSkin( hkgDisplayContext* context, hkgDisplayObject* dispObj, 
								IndexMapping* mappings, hkInt32 numMappings, 
								hkInt16 fullPaletteSize, hkBool allowCulling);

		static void HK_CALL updateSkin( hkgDisplayObject* dispObj, 
								hkArray< hkTransform >& matrixPalletes, hkArray< hkgBlendMatrixSet* >& graphicsPalettes, 
								const hkTransform& skinTransform, const class hkAabb* pLocalAabb = HK_NULL);

		// Search for the index of an object to retreive the display object.
		static int HK_CALL findFirstMapping( const hkgArray<Mapping>& inList, const void* original);
		static int HK_CALL findFirstMapping( const hkgArray<SkinPaletteMap*>& inList, const void* original);

		static void HK_CALL findAllMappings( const hkgArray<Mapping>& inList, const void* original, hkgArray<int>& mappedEntries);
		static void HK_CALL findAllMappings( const hkgArray<SkinPaletteMap*>& inList, const void* original, hkgArray<int>& mappedEntries);

			// A dscription of the vertex format for our graphics library
		static class hkxVertexDescription* HK_CALL constructVertexDesc(class hkgVertexSet* v);
};

#endif // HK_GRAPHICS_BRIDGE_ASSET_CONV_H

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
