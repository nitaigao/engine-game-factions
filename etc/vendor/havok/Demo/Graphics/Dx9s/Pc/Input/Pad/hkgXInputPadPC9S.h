/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HK_GRAPHICS_XINPUT_PAD_DX9S_H
#define HK_GRAPHICS_XINPUT_PAD_DX9S_H

//-----------------------------------------------------------------------------
// Taken from Xenon framework file: ATGInput.h
//-----------------------------------------------------------------------------

class hkgXInputPad9S : public XINPUT_GAMEPAD
{
public:

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DEMO_FRAMEWORK, hkgXInputPad9S );

	hkgXInputPad9S() : bInitialized(FALSE) {}
	 // The following members are inherited from XINPUT_GAMEPAD:
	//  WORD wButtons;
	//  BYTE bLeftTrigger;
	//  BYTE bRightTrigger;
	//  SHORT sThumbLX;
	//  SHORT sThumbLY;
	//  SHORT sThumbRX;
	//  SHORT sThumbRY;

	// Thumb stick values converted to range [-1,+1]
	FLOAT      fX1;
	FLOAT      fY1;
	FLOAT      fX2;
	FLOAT      fY2;

	// State of buttons tracked since last poll
	WORD       wLastButtons;
	WORD       wPressedButtons;
	BOOL       bPressedTriggerButtons[2];

	// Device properties
	XINPUT_CAPABILITIES caps;
	BOOL       bConnected;

	// Flags for whether game pad was just inserted or removed
	BOOL       bInserted;
	BOOL       bRemoved;

	BOOL       bInitialized;

	VOID	GetInput(INT padNumber);
	VOID	SetVibration(INT padNumber, WORD lowFrequencyStrength, WORD highFrequencyStrength);
};


#endif // HK_GRAPHICS_XINPUT_PAD_DX9S_H

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
