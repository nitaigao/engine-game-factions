/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>

#include <Demos/DemoCommon/Utilities/Character/CharacterUtils.h>
#include <Common/Visualize/hkDebugDisplay.h>
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastInput.h>
#include <Physics/Collide/Query/Collector/RayCollector/hkpAllRayHitCollector.h>
#include <Physics/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>
#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBody.h>
#include <Physics/Utilities/CharacterControl/StateMachine/hkpDefaultCharacterStates.h>
#include <Physics/Utilities/Weapons/hkpFirstPersonGun.h>
#include <Physics/Utilities/CharacterControl/FirstPersonCharacter/hkpFirstPersonCharacter.h>

	#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
	#undef _WIN32_WINNT
	#define _WIN32_WINNT 0x0500	  // win2000
	#undef _WIN32_WINDOWS 
	#define _WIN32_WINDOWS 0x0500 // win2000
	#undef WINVER	
	#define WINVER 0x0500	      // win2000

	#include <windows.h>


static void HK_CALL _deadzone(float& stickX, float& stickY)
{
	hkReal INPUT_DEADZONE = 0.15f; // PS2 style .. large

	const float deadzoneScale = 1.0f/(1.0f-INPUT_DEADZONE);
	stickX = ( stickX < -INPUT_DEADZONE) ? (stickX + INPUT_DEADZONE) * deadzoneScale : (
		( stickX > INPUT_DEADZONE ) ? (stickX - INPUT_DEADZONE) * deadzoneScale : 0);
	stickY = ( stickY < -INPUT_DEADZONE) ? (stickY + INPUT_DEADZONE) * deadzoneScale : (
		( stickY > INPUT_DEADZONE ) ? (stickY - INPUT_DEADZONE) * deadzoneScale : 0);
}


void HK_CALL CharacterUtils::getUserInputForCharacter( hkDemoEnvironment* env, float& deltaAngle, float& posX, float& posY )
{
	// Only run this function if the window is in focus, because it grabs the mouse
	if ( GetForegroundWindow() != env->m_window->getPlatformHandle() )
		return;

	// Mouse
	deltaAngle = 0.f;
	posX = 0.f;
	posY = 0.f;
	const hkgPad& pad = *(env->m_gamePad);

	bool haveProperGamePad = env->m_window->hasGamePads() && !(env->m_options->m_forceKeyboardGamepad);

	// No gamepad (win32 and PLAYSTATION(R)3 default at the mo)
	if (!haveProperGamePad)
	{
		const hkReal MOUSE_SENSITIVITY = 1.0f;
		int mouseX = env->m_window->getMouse().getPosX();
		int halfWindowWidth = env->m_window->getCurrentViewport()->getWidth() >> 1;
		int halfWindowHeight = env->m_window->getCurrentViewport()->getHeight() >> 1;

		{
			hkReal inc  = hkReal(halfWindowWidth - mouseX) / halfWindowWidth;
			inc = (inc < -1.0f) ? -1.0f : inc;
			inc = (inc >  1.0f) ?  1.0f : inc;
			deltaAngle = 3.4f * inc * MOUSE_SENSITIVITY;
		}


		// Snap mouse back to middle
		env->m_window->setMousePosition(halfWindowWidth, halfWindowHeight);

		const hkgKeyboard& keyboard = env->m_window->getKeyboard();
		if (keyboard.getKeyState('A')) posX=1.f;
		if (keyboard.getKeyState('D')) posX=-1.f;
		if (keyboard.getKeyState('W')) posY=-1.f;
		if (keyboard.getKeyState('S')) posY=1.f;

	}
	else if (pad.isValid())
	{
		if ( (pad.getButtonState() & HKG_PAD_BUTTON_L1) == 0)
		{
			const hkReal PAD_SENSITIVITY = 0.05f;
			float stickX = pad.getStickPosX(1);
			float stickY = pad.getStickPosY(1);
			_deadzone(stickX, stickY);
			deltaAngle = 3.4f * -stickX * PAD_SENSITIVITY;
			posY = -stickY;
		}

		{
			float stickZ = pad.getStickPosX(0);
			float stickZZ = 0;
			_deadzone(stickZ, stickZZ);
			posX = -stickZ; // strafe on stick0
		}
	}

	// dpad == dir keys on PC
	{
		if ((pad.getButtonState() & HKG_PAD_DPAD_UP) != 0)   posY=-1.f;
		if ((pad.getButtonState() & HKG_PAD_DPAD_LEFT) != 0) posX=1.f;
		if ((pad.getButtonState() & HKG_PAD_DPAD_RIGHT) != 0)posX=-1.f;
		if ((pad.getButtonState() & HKG_PAD_DPAD_DOWN) != 0) posY=1.f;
	}

	// Normalize the movement vector
	hkReal lenSqd = posY * posY + posX * posX;
	if (lenSqd > HK_REAL_MIN)
	{
		lenSqd = hkMath::sqrt(lenSqd);
		posY /= lenSqd;
		posX /= lenSqd;
	}
}

void HK_CALL CharacterUtils::getUserInputForCharacter( hkDemoEnvironment* env, const Sensivity& sensivity, float& deltaAngle, float& deltaElevation, float& posX, float& posY )
{
	// Mouse
	deltaAngle = 0.f;
	deltaElevation = 0.f;
	posX = 0.f;
	posY = 0.f;

	// Only run this function if the window is in focus, because it grabs the mouse
	if ( GetForegroundWindow() != env->m_window->getPlatformHandle() )
	{
		return;
	}

	const hkgPad& pad = *(env->m_gamePad);

	if (pad.isValid())
	{
		if ( (pad.getButtonState() & HKG_PAD_BUTTON_L1) == 0)
		{
			float stickX = pad.getStickPosX(1);
			float stickY = pad.getStickPosY(1);
			_deadzone(stickX, stickY);
			posX = -stickX; // strafe on stick1
			posY = -stickY;
		}

		{
			const hkReal PAD_SENSITIVITY = 0.02f;
			float stickX = pad.getStickPosX(0);
			float stickY = pad.getStickPosY(0);
			_deadzone(stickX, stickY);
			deltaAngle		= 3.4f * -stickX * PAD_SENSITIVITY * sensivity.m_padX;
			deltaElevation	= 3.4f * -stickY * PAD_SENSITIVITY * sensivity.m_padY;
		}

		// dpad == dir keys on PC
		{
			if ((pad.getButtonState() & HKG_PAD_DPAD_UP) != 0)   posY=-1.f;
			if ((pad.getButtonState() & HKG_PAD_DPAD_LEFT) != 0) posX=1.f;
			if ((pad.getButtonState() & HKG_PAD_DPAD_RIGHT) != 0)posX=-1.f;
			if ((pad.getButtonState() & HKG_PAD_DPAD_DOWN) != 0) posY=1.f;
		}
	}

	// No gamepad (win32 and PLAYSTATION(R)3 default at the mo)
	if( env->m_window->getMouse().isValid() )
	{
		int mouseX = env->m_window->getMouse().getPosX();
		int halfWindowWidth = env->m_window->getCurrentViewport()->getWidth() >> 1;

		{
			hkReal inc  = hkReal(halfWindowWidth - mouseX) / halfWindowWidth;
			inc = (inc < -1.0f) ? -1.0f : inc;
			inc = (inc >  1.0f) ?  1.0f : inc;
			if ( inc != 0 )
			{
				deltaAngle = 3.4f * inc * sensivity.m_mouseX;
			}
		}

		int mouseY = env->m_window->getMouse().getPosY();
		int halfWindowHeight = env->m_window->getCurrentViewport()->getHeight() >> 1;
		{
			hkReal inc  = hkReal(halfWindowHeight - mouseY) / halfWindowHeight;
			inc = (inc < -1.0f) ? -1.0f : inc;
			inc = (inc >  1.0f) ?  1.0f : inc;
			if ( inc != 0.0f )
			{
				deltaElevation = 3.4f * inc * sensivity.m_mouseY;
			}
		}

		// Snap mouse back to middle
		env->m_window->setMousePosition(halfWindowWidth, halfWindowHeight);

		const hkgKeyboard& keyboard = env->m_window->getKeyboard();
		if (keyboard.getKeyState( 'A')) posX=1.f;
		if (keyboard.getKeyState( 'D')) posX=-1.f;
		if (keyboard.getKeyState( 'W')) posY=-1.f;
		if (keyboard.getKeyState( 'S')) posY=1.f;
	}


	// Normalize the movement vector
	hkReal lenSqd = posY * posY + posX * posX;
	if (lenSqd > 1.0f)
	{
		lenSqd = hkMath::sqrt(lenSqd);
		posY /= lenSqd;
		posX /= lenSqd;
	}
}

// Compute the blend params that will produce the desired velocity
void HK_CALL CharacterUtils::computeBlendParams( hkReal desiredVel, hkReal walkVel, hkReal runVel, hkReal walkDur, hkReal runDur, hkReal& blend, hkReal& walkSpeed, hkReal& runSpeed )
{
	// Analytical solution of blending aproximation
	// Solution is second root of quadratic equation 

	const hkReal runWalkRatio = runDur / walkDur;

	const hkReal wVratio = walkVel*runWalkRatio;
	const hkReal rVratio = runVel*runWalkRatio;
	const hkReal rVratio2 = rVratio*runWalkRatio;
	const hkReal dVratio = desiredVel*runWalkRatio;

	blend = (-2.0f*wVratio+walkVel+rVratio2-sqrt(walkVel*walkVel-2.0f*walkVel*rVratio2+runVel*rVratio2*runWalkRatio*runWalkRatio+4.0f*(-walkVel*dVratio+wVratio*dVratio+rVratio2*desiredVel-rVratio2*dVratio)))/(2.0f*(walkVel-wVratio-rVratio+rVratio2));

	blend = hkMath::clamp(blend, 0.f, 1.f);
	runSpeed  = (1.0f-blend) * runWalkRatio + blend;
	walkSpeed = blend * (1.0f / runWalkRatio) + (1.0f - blend);	

}



void HK_CALL CharacterUtils::displayCharacterState(hkpCharacterContext* context, hkDemoEnvironment* env )
{

	// Rigid body controller state
	hkpCharacterStateType stateRBC = context->getState();
	char * stateStrRBC;

	switch (stateRBC)
	{
	case HK_CHARACTER_ON_GROUND:
		stateStrRBC = "On Ground";	break;
	case HK_CHARACTER_JUMPING:
		stateStrRBC = "Jumping"; break;
	case HK_CHARACTER_IN_AIR:
		stateStrRBC = "In Air"; break;
	case HK_CHARACTER_CLIMBING:
		stateStrRBC = "Climbing"; break;
	default:
		stateStrRBC = "Other";	break;
	}

	char buffer[255];
	hkString::snprintf(buffer, 255, "State: %s", stateStrRBC);
	env->m_textDisplay->outputText(buffer, 20, 450, 0xffffffff);
}

// Objects colors
#define NORMAL_GRAY				hkColor::rgbFromChars( 192, 192, 192, 255 )
#define TRANSPARENT_GREY		hkColor::rgbFromChars( 192, 192, 192, 125 )

void HK_CALL CharacterUtils::updateCamera( const hkpFirstPersonCharacter* character, hkgWindow* window )
{
	const hkReal height = character->m_eyeHeight; 

	hkVector4 from;
	from = character->m_characterRb->getPosition();
	from.addMul4(height, character->m_characterRb->m_up );

	hkVector4 forward;
	character->getForwardDir( forward );

	hkVector4 to;
	to.setAddMul4( from, forward, 4 );

/*
	hkVector4 to;
	to = character->m_characterRb->getPosition();
	to.addMul4(height, character->m_characterRb->m_up );


	hkVector4 dir;
	dir.setMul4( height, character->m_characterRb->m_up );
	dir.addMul4( -4.f, forward);

	hkVector4 from;
	from.setAdd4(to, dir);
*/
/*	// Make object in the line of sight transparent
	if(m_makeOccludingObjectsTransparent)
	{
		// Cast down to landscape to get an accurate position
		hkpWorldRayCastInput raycastIn;

		// Reverse direction for raycasting
		raycastIn.m_from = to;
		raycastIn.m_to = from;
		raycastIn.m_filterInfo = hkpGroupFilter::calcFilterInfo(0);

		hkpAllRayHitCollector collector;

		world->castRay( raycastIn, collector);

		for (int i = 0; i < m_transparentObjects.getSize(); ++i )
		{
			HK_SET_OBJECT_COLOR(m_transparentObjects[i], NORMAL_GRAY );
		}
		m_transparentObjects.clear();

		// Loop over all collected objects
		for(int i=0; i < collector.getHits().getSize();i++)
		{				
			hkpWorldRayCastOutput raycastOut = collector.getHits()[i];
			hkpRigidBody* rb = hkGetRigidBody(raycastOut.m_rootCollidable);
			if (rb && rb->isFixedOrKeyframed())
			{
				HK_SET_OBJECT_COLOR((hkUlong)raycastOut.m_rootCollidable, TRANSPARENT_GREY );

				m_transparentObjects.pushBack((hkUlong)raycastOut.m_rootCollidable);
			}
		}
	}
*/
	window->getContext()->lock();
	for(int i = 0; i < window->getNumViewports(); ++i)
	{
		hkgViewport* viewPort = window->getViewport(i);
		hkgCamera* c = viewPort->getCamera();

		float upN[3];
		hkgVec3Copy(upN, &character->m_characterRb->m_up(0));
		hkgVec3Normalize(upN);
		// set up camera
		c->setFrom(&from(0));
		c->setTo(&to(0));
		c->setUp(upN);
		c->orthogonalize();
		c->computeModelView();
		c->computeProjection();
		//c->setHandednessMode(HKG_CAMERA_HANDEDNESS_MODE( rightHanded ? HKG_CAMERA_HANDEDNESS_RIGHT : HKG_CAMERA_HANDEDNESS_LEFT) );
		viewPort->setFlyModeUp( upN );
	}
	window->getContext()->unlock();
}


static void setInputFromUserControls( hkpFirstPersonCharacter* character, hkDemoEnvironment* env, hkpFirstPersonCharacter::CharacterControls& controls )
{
	// Get user input data
	hkReal deltaAngle;
	hkReal deltaElevation;

	CharacterUtils::Sensivity sensivity;
	{
		sensivity.m_mouseX = character->m_horizontalSensitivity;
		sensivity.m_mouseY = character->m_verticalSensitivity;
		sensivity.m_padX = character->m_sensivityPadX;
		sensivity.m_padY = character->m_sensivityPadY;
	}

	CharacterUtils::getUserInputForCharacter(env, sensivity, deltaAngle, deltaElevation, controls.m_straffeLeftRight, controls.m_forwardBack );

	controls.m_straffeLeftRight *= character->m_leftRightSpeedModifier;
	controls.m_forwardBack      *= character->m_forwardBackwardSpeedModifier;

	if (! (character->m_flags & hkpFirstPersonCharacter::INVERT_UP_DOWN)) 
	{
		deltaElevation = -deltaElevation;
	}

	character->m_currentAngle += deltaAngle;
	character->m_currentElevation += deltaElevation;
	
	if (character->m_currentElevation < -character->m_maxUpDownAngle) character->m_currentElevation = -character->m_maxUpDownAngle;
	if (character->m_currentElevation > character->m_maxUpDownAngle)  character->m_currentElevation = character->m_maxUpDownAngle;

	hkQuaternion currentOrient; currentOrient.setAxisAngle(character->m_characterRb->m_up, character->m_currentAngle);
 
	controls.m_wantJump = env->m_window->getKeyboard().wasKeyPressed( HKG_VKEY_SPACE ) || ((env->m_gamePad->getButtonState() & HKG_PAD_BUTTON_1) != 0);

	controls.m_forward.set(1,0,0);
	controls.m_forward.setRotatedDir( currentOrient, controls.m_forward );

	controls.m_fire = false;
	if ( (env->m_window->getMouse().getButtonState() & HKG_MOUSE_LEFT_BUTTON) ||
		 (env->m_gamePad->getButtonState() & HKG_PAD_BUTTON_R1) )
	{
		if ( character->m_gunCounter-- < 0 )
		{
			character->m_gunCounter = 10;
			controls.m_fire = true;
		}
	}
	else
	{
		character->m_gunCounter = 0;
	}

	controls.m_fireRmb = false;
	if ( (env->m_window->getMouse().getButtonState() & HKG_MOUSE_RIGHT_BUTTON) ||
		 (env->m_gamePad->getButtonState() & HKG_PAD_BUTTON_R2) )
	{
		if ( character->m_gunCounterRmb-- < 0 )
		{
			character->m_gunCounterRmb = 20;
			controls.m_fireRmb = true;
		}
	}
	else
	{
		character->m_gunCounterRmb = 0;
	}
}

void HK_CALL CharacterUtils::stepCharacter( hkReal timestep, hkpFirstPersonCharacter* character, hkDemoEnvironment* env )
{
	if ( character->m_flags & hkpFirstPersonCharacter::HAS_USER_CONTROL )
	{
		character->m_world->lock();
		hkpFirstPersonCharacter::CharacterControls controls;
		setInputFromUserControls( character, env, controls );

		if ( character->m_flags & hkpFirstPersonCharacter::DISABLE_JUMP )
		{
			controls.m_wantJump = false;
		}

		if ( controls.m_fire && character->m_currentGun )
		{
			hkTransform viewTransform;
			character->getViewTransform( viewTransform );
			character->m_currentGun->fireGun( character->m_world, viewTransform );
		}

		character->update( timestep, controls, false );
		updateCamera( character, env->m_window );

		if (character->m_currentGun)
		{
			hkpRigidBody* body = character->m_characterRb->m_character;
			hkTransform viewTransform; character->getViewTransform(viewTransform);
			character->m_currentGun->stepGun( timestep, character->m_world, body, viewTransform, controls.m_fire, controls.m_fireRmb );
		}
		character->m_world->unlock();
	}


	const hkgKeyboard& keyBoard = env->m_window->getKeyboard();
	if (keyBoard.wasKeyPressed('P') || keyBoard.wasKeyPressed('O') )
	{
		if (character->m_flags & hkpFirstPersonCharacter::HAS_USER_CONTROL)
		{
			character->m_flags = character->m_flags & (~hkpFirstPersonCharacter::HAS_USER_CONTROL);
		}
		else
		{
			character->m_flags = character->m_flags | hkpFirstPersonCharacter::HAS_USER_CONTROL;
		}
		if (character->m_flags & hkpFirstPersonCharacter::HAS_USER_CONTROL)
		{
			// Snap mouse back to middle
			env->m_window->setMousePosition(env->m_window->getWidth() >> 1, env->m_window->getHeight() >> 1);
			env->m_mousePickingEnabled = false;

			// position rigid body at camera position
			hkgViewport* viewPort = env->m_window->getViewport(0);
			hkgCamera* c = viewPort->getCamera();

			hkVector4 position; position.setZero4();
			c->getFrom( &position(0) );
			hkVector4 to; to.setZero4();
			c->getTo( &to(0) );
			hkVector4 dir; dir.setSub4( to, position );
			dir.normalize3();

			{
				position.subMul4( character->m_eyeHeight, character->m_characterRb->m_up);
				hkpRigidBody* body = character->getRigidBody();
				body->setPosition( position );
				body->setLinearVelocity( hkVector4::getZero() );
			}
			character->setForwardDir( dir );
			if ( keyBoard.wasKeyPressed('O') )
			{
				character->m_gravity.setZero4();
				character->m_specialGravity = true;
			}
			else
			{
				character->m_specialGravity = false;
			}
		}
		else
		{
			env->m_mousePickingEnabled = true;
		}
	}
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
