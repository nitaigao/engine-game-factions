/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_GRAPHICS_SHADOW_UTILS__H
#define HK_GRAPHICS_SHADOW_UTILS__H

#include <Graphics/Common/hkgObject.h>
#include <Graphics/Common/Math/hkgBounds.h>
#include <Graphics/Common/Window/hkgWindowDefines.h>
#include <Graphics/Common/Camera/hkgCamera.h>

#define HKG_SHADOW_DEFAULT_SCHEME_WEIGHT 0.5f
#define HKG_SHADOW_DEFAULT_FIT_TOLERANCE 2.0f

class hkgShadowUtils : public hkgReferencedObject
{
public:

	explicit hkgShadowUtils();
	virtual ~hkgShadowUtils();

		// Currently will use PSM as default
	void setMode(HKG_SHADOWMAP_MODE m);
	HKG_SHADOWMAP_MODE getMode() const { return m_mode; }

	void setLightCamera( class hkgCamera* lightCam );
	inline hkgCamera* getLightCamera( ) const { return m_fixedLightCam; }
	void setNumSplits( int numSplits );
	
	inline int getNumSplits( ) const { return m_numSplits; }
	inline float* getSplitDistances( ) const { return (float*) m_splitDistances; } // map 0 far == [0], map 1 far distance == [1], etc

	void setNearDistanceClamp(float firstResMinDist, float firstResMaxDist); // 0,0 will restore fully dynamic ver
	void getNearDistanceClamp(float& firstResMinDist, float& firstResMaxDist);

	void setSplitSchemeWeight( float v = HKG_SHADOW_DEFAULT_SCHEME_WEIGHT ); // 0== Uniform, 1 == log
	float getSplitSchemeWeight( ) { return m_fSplitSchemeWeight; }

	float getNearFarFitTolerance() const { return m_nearFarFitTolerance; }
	void setNearFarFitTolerance(float t = HKG_SHADOW_DEFAULT_FIT_TOLERANCE) { m_nearFarFitTolerance = t; }

	void setFastViewCull(bool on) { m_fastCull = on;}
	bool getFastViewCull() const { return m_fastCull; }


	void setCamera(class hkgCamera* viewCam, float maxShadowZ = 10);
	void setLight(class hkgLight* light);
	void setWorld(class hkgDisplayWorld* world);

	void buildProjectionMatrix();
	void computeCropMatrix();

	inline const float* getLightViewProj() const { return m_mLightViewProj; }
	inline const float* getLightViewProjCS() const { return m_mLightViewProjCS; }

	inline const float* getLightCropMatrix(int split) const { return m_splitCropMatrix[split]; }
	inline const hkgCamera* getSplitLightCamera(int split) const { return m_splitLightCameras[split]; }

	inline float getShadowMapDistance() const { if (m_mode == HKG_SHADOWMAP_MODE_NONE) return 1e10f; else return (m_mode==HKG_SHADOWMAP_MODE_PSM?  m_ppFar  : (m_fixedLightCam->getProjectionMode() == HKG_CAMERA_ORTHOGRAPHIC? m_fixedLightCam->getOrthoFar() : m_fixedLightCam->getFar() ) ); }
	inline const float* getShadowMapStartLocation() const { if (m_mode == HKG_SHADOWMAP_MODE_NONE) return HKG_VEC3_ZERO; else return m_mode==HKG_SHADOWMAP_MODE_PSM? m_vLightFrom : m_fixedLightCam->getFromPtr(); }
	
	void setShadowViewOffsetMatrix(const float* reflection); // identity normally, but the view matrix reflection for reflectiosn with shadows.
	const float* getShadowViewOffsetMatrix() const;

protected:

	void computeBounds();		
	void buildFixedProjection();
	void buildSplitProjections();
	void buildPerspectiveProjection();

	// current state
	HKG_SHADOWMAP_MODE m_mode;
	hkgDisplayWorld* m_world;
	float m_mView[16];
	float m_mProj[16];
	float m_mViewOffset[16];
	float m_vLightDir[3];
	float m_vLightFrom[3];
	float m_fAspect;
	float m_fNearMin;
	float m_fFarMax;
	float m_fShadowZClip;

	float m_fSplitSchemeWeight; 
	float m_nearFarFitTolerance;
	float m_nearDistClampMin;
	float m_nearDistClampMax;

	bool m_fastCull;

		// fixed mode:
	hkgCamera*  m_fixedLightCam;
	hkgCamera*	m_viewCamera;
	
	hkgCamera*  m_splitLightCameras[HKG_SHADOWMAP_PSVSM_MAX_NUM_SPLITS+1]; // we keep these so we can frustum cull against them
	float m_splitCropMatrix[HKG_SHADOWMAP_PSVSM_MAX_NUM_SPLITS+1][16];
	int m_numSplits;
	float m_splitDistances[HKG_SHADOWMAP_PSVSM_MAX_NUM_SPLITS+1]; 

	bool m_bProj01; // DX style unit box of 0..1 not -1 to 1 in z
	bool m_bLeftHanded; // DX style left handed projections
	// computed state
	float m_mLightViewProj[16];
	float m_mLightViewProjCS[16];

	hkgArray<hkgAabb> m_shadowCasterAABBs;
	hkgArray<hkgAabb> m_shadowReceiverAABBs;
	hkgArray<const class hkgDisplayObject*> m_shadowCasterObjects;
	hkgArray<const class hkgDisplayObject*> m_shadowReceiverObjects;

	// computed parameters
	bool m_bShadowTestInverted;
	float m_zNear;
	float m_ppNear;
	float m_zFar;
	float m_ppFar;
	float m_fInfiniteZ;
	float m_fZOffset;
};

#endif //HK_GRAPHICS_SHADOW_UTILS__H

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
