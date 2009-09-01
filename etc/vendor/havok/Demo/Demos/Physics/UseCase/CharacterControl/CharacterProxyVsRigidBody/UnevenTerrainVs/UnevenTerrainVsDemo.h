/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_BUMPS_DEMO_H
#define HK_BUMPS_DEMO_H

#include <Demos/DemoCommon/DemoFramework/hkDefaultPhysicsDemo.h>

#include <Physics/Utilities/CharacterControl/hkpCharacterControl.h>

class hkpCharacterRigidBody;
class hkpCharacterContext;

class hkpCharacterProxy;
class hkpShapePhantom;
struct hkpCharacterInput;


class UnevenTerrainVsDemo : public hkDefaultPhysicsDemo
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO);

		UnevenTerrainVsDemo(hkDemoEnvironment* env);
		
		~UnevenTerrainVsDemo();

		Result stepDemo();

		// Collision Layers used in this demo.
		// By enabling and disabling collisions between these layers, we can tweak the behaviour of the demo
		// Disable collision between CHARACTER_PROXY and CHARACTER_RIGIDBODY
		enum
		{
			LAYER_LANDSCAPE = 1,
			LAYER_CHARACTER_PROXY = 2,
			LAYER_CHARACTER_RIGIDBODY = 3			
		};

	public:
		struct Options
		{
			HK_DECLARE_REFLECTION();

			Options()
			:	m_worldCollisionTolerance( 0.1f ),
				m_characterCylinderHeight( 0.8f	),
				m_characterRadius( 0.6f ),
				// Gravity as applied to characters is typically higher than world gravity.
				m_characterGravity( -16.0f ),
				m_characterWalkSpeed( 10.0f ),
				m_clientStateFiltering( 3 ),
				m_rbSupportDistance( 0.1f ),
				m_rbHardSupportDistance( 0.0f ),
				m_rbAllowedPenetrationDepth( -0.1f )
			{
			}

			hkReal m_worldCollisionTolerance; //+default(0.1f) +absmin(0.0) +absmax(1.0f)
			hkReal m_characterCylinderHeight; //+default(0.8f) +absmin(0.1f) +absmax(20.0f)
			hkReal m_characterRadius; //+default(0.6f) +absmin(0.1f) +absmax(20.0f)
			hkReal m_characterGravity; //+default(-16.0f) +absmin(-100.0f) +absmax(100.0f)
			hkReal m_characterWalkSpeed; //+default(10.0f) +absmin(1.0f) +absmax(100.0f)
			int m_clientStateFiltering; //+default(3) +absmin(0) +absmax(100)
			// For the character rigid body only
			hkReal m_rbSupportDistance; //+default(0.1f) +absmin(0.0) +absmax(1.0f)
			hkReal m_rbHardSupportDistance; //+default(0.0f) +absmin(-0.1) +absmax(1.0f)
			hkReal m_rbAllowedPenetrationDepth; //+default(-0.1f) +absmin(-5.0) +absmax(5.0f)
		};

		DEMO_OPTIONS_DECLARE(Options);

	protected:
		
		
		hkInt32 m_supportHistoryRb;
		hkInt32 m_supportHistoryProxy;

		hkInt32 m_unsupportedFramesCountRb;
		hkInt32 m_unsupportedFramesCountProxy;

		hkpCharacterRigidBody* m_characterRigidBody;
		hkpCharacterContext* m_characterContext;

		// Character proxy
		hkpShapePhantom* m_phantom;
		hkpCharacterProxy* m_characterProxy;

		hkpCharacterContext* m_characterProxyContext;

		int m_tick;

		class LandscapeContainer* m_landscapeContainer;

	public:

		struct FilterInfo
		{
			hkpSurfaceInfo m_previousGround;
			int m_framesInAir;
		};

			/// Ignore changes in support unless they last for more than a few frames.	
		void filterStates( FilterInfo& filter, hkpSurfaceInfo& input );

		FilterInfo m_filterRigidBody;
		FilterInfo m_filterProxy;
};

#endif // HK_BUMPS_DEMO_H

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
