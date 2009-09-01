/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>

#include <Demos/DemoCommon/Utilities/CameraUtils/CameraUtils.h>
#include <Graphics/Common/Camera/hkgCamera.h>

void HK_CALL CameraUtils::spewCameraDetailsToConsole( const hkgCamera* camera )
{
	HK_ASSERT2(0x7e4dcd1a, camera != HK_NULL, "CameraUtils: provided camera is NULL");
	hkString s;
	float f[3];

	camera->getFrom(f);
	s.printf("hkVector4 from(%.2ff, %.2ff, %.2ff);", f[0], f[1], f[2]);
	hkcout << s << hkendl;

	camera->getTo(f);
	s.printf("hkVector4 to(%.2ff, %.2ff, %.2ff);", f[0], f[1], f[2]);
	hkcout << s << hkendl;

	camera->getUp(f);
	s.printf("hkVector4 up(%.2ff, %.2ff, %.2ff);", f[0], f[1], f[2]);
	hkcout << s << hkendl;

	hkcout << "setupDefaultCameras( env, from, to, up, 0.01f, 500 );" << hkendl;
}

void HK_CALL CameraUtils::spewCameraDetailsToConsole( const hkDemoEnvironment* env )
{
	HK_ASSERT2(0x6f98cd2d, ( (env != HK_NULL) && (env->m_window != HK_NULL) ) ,"CameraUtils: invalid environment provided");
	
	const hkgCamera* camera = env->m_window->getViewport( 0 )->getCamera();
	spewCameraDetailsToConsole( camera );
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
