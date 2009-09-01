/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_TESTING_TOLERANCES_H
#define HK_TESTING_TOLERANCES_H

#include <Demos/DemoCommon/DemoFramework/hkDefaultPhysicsDemo.h>

class hkpCharacterProxy;
class hkpShapePhantom;
class hkpCharacterContext;

class StairClimbingDemo : public hkDefaultPhysicsDemo
{
	public:
		StairClimbingDemo( hkDemoEnvironment* env );
		~StairClimbingDemo();
		virtual hkDemo::Result stepDemo();

		struct Options
		{
			HK_DECLARE_REFLECTION();

			Options()
			:	m_worldCollisionTolerance( 0.1f ),
				m_characterCylinderHeight( 0.8f	),
				m_characterRadius( 0.6f ),
				m_maxSlope( HK_REAL_PI * 0.333f ),
				m_numStaircases( 5 ),
				m_numStepsStart( 5 ),
				m_numStepsIncrement( 4 ),
				m_stairsRun( 5.0f ),
				m_stairsRise( 3.0f ),
				m_stepConvexRadius( hkConvexShapeDefaultRadius )
			{
			}
			
			hkReal m_worldCollisionTolerance; //+default(0.1f) +absmin(0.0) +absmax(1.0f)
				/// The tolerance used by the demo tolerance hack.
			hkReal m_characterCylinderHeight; //+default(0.8f) +absmin(0.1f) +absmax(20.0f)
			hkReal m_characterRadius; //+default(0.6f) +absmin(0.1f) +absmax(20.0f)
			hkReal m_maxSlope; //+default(1.05f) +absmin(0.5f) +absmax(1.57f)
			int m_numStaircases; //+default(5) +absmin(2) +absmax(20)
			int m_numStepsStart; //+default(5) +absmin(2) +absmax(40)
			int m_numStepsIncrement; //+default(4) +absmin(1) +absmax(40)
				/// The angle at which to tilt the left half of the floor in radians.
			hkReal m_stairsRun; //+default(5.f) +absmin(0.5f) +absmax(20.f)
			hkReal m_stairsRise; //+default(3.f) +absmin(0.5f) +absmax(20.f)
			hkReal m_stepConvexRadius; //+default(0.05f) +absmin(0.0) +absmax(1.0)
		};

		DEMO_OPTIONS_DECLARE(Options);
 
	private:
		// Character proxy
		hkpShapePhantom* m_phantom;
		hkpCharacterProxy* m_characterProxy;
		hkpCharacterContext* m_characterProxyContext;

		static void HK_CALL getUserInputForCharacter( hkDemoEnvironment* env, float& posX, float& posY, hkBool& wantJump );

		hkInt32 m_supportHistory;

		void calcStats();
};

#endif // HK_TESTING_TOLERANCES_H

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
