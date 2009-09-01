/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_CHARACTER_RIGID_BODY_FALLS_PLATFORMS_DEMO_H
#define HK_CHARACTER_RIGID_BODY_FALLS_PLATFORMS_DEMO_H

#include <Demos/DemoCommon/DemoFramework/hkDefaultPhysicsDemo.h>
#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBody.h>

class hkpCharacterContext;
class hkLoader;

class MovingSupportRbDemo : public hkDefaultPhysicsDemo
{
public:

	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO);

	MovingSupportRbDemo(hkDemoEnvironment* env);

	~MovingSupportRbDemo();

	hkDemo::Result stepDemo();

	// Move keyframed horizontal platform left <-> right
	void moveHorizontalPlatform();
	// Move keyframed vertical platform up <-> down 
	void moveVerticalPlatform();

protected:
	static void HK_CALL getUserInputForCharacter( hkDemoEnvironment* env, float& posX, float& posY, hkBool& wantJump );

	void getGround( const hkArray<hkpCharacterRigidBody::SupportInfo>& supportInfo, hkpSurfaceInfo& ground ) const;

	hkReal m_time;

	// Horizontal platform
	hkpRigidBody* m_horPlatform;
	// Vertical platform
	hkpRigidBody* m_verPlatform;		

	hkpShape* m_standShape;

	hkpCharacterRigidBody* m_characterRigidBody;
	hkpCharacterContext* m_characterContext;

	static const int NUM_OF_ROWS = 2;
	static const int NUM_IN_ROWS = 4;

	hkArray<hkpRigidBody*> m_bodies;

	hkPointerMap<hkpRigidBody*,hkBool32> m_bodyType;
};
#endif

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
