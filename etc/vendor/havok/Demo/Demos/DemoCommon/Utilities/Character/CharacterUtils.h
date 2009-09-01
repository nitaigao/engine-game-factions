/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_CHARACTER_UTILS_H
#define HK_CHARACTER_UTILS_H

class hkpCharacterContext;
class hkpFirstPersonCharacter;

class CharacterUtils
{
	public:

		struct Sensivity
		{
			Sensivity(){ m_mouseX = m_mouseY = m_padX = m_padY = 1.0f; }
			hkReal m_mouseX;
			hkReal m_mouseY;
			hkReal m_padX;
			hkReal m_padY;
		};

		/// Character control from mouse and/or dpads and sticks
		/// based on what is appropriate for platform
	static void HK_CALL getUserInputForCharacter( hkDemoEnvironment* env,                             float& deltaAngle,                        float& dirX, float& dirY );
	static void HK_CALL getUserInputForCharacter( hkDemoEnvironment* env, const Sensivity& sensivity, float& deltaAngle, float& deltaElevation, float& dirX, float& dirY );


		/// Convenience function to display character state as text on screen
	static void HK_CALL displayCharacterState(hkpCharacterContext* context, hkDemoEnvironment* env );

		/// Compute the blend params that will produce the desired velocity
	static void HK_CALL computeBlendParams( hkReal desiredVel, hkReal walkVel, hkReal runVel, hkReal walkDur, hkReal runDur, hkReal& blend, hkReal& walkSpeed, hkReal& runSpeed );

	static void HK_CALL updateCamera( const hkpFirstPersonCharacter* character, hkgWindow* window );

	static void HK_CALL stepCharacter( hkReal timestep, hkpFirstPersonCharacter* character, hkDemoEnvironment* env );

};

#endif // HK_CHARACTER_UTILS_H

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
