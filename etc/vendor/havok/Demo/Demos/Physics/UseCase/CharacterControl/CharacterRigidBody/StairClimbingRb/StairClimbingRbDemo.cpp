/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>

#include <Demos/Physics/UseCase/CharacterControl/CharacterRigidBody/StairClimbingRb/StairClimbingRbDemo.h>

// Shapes
#include <Physics/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>

// CharacterRigidBodies
#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBody.h>
#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBodyListener.h>

// Debug and visualization
#include <Common/Visualize/hkDebugDisplay.h>
#include <Common/Visualize/Shape/hkDisplayBox.h>
#include <Common/Base/Types/Color/hkColor.h>

// The alternative shape
#include <Demos/DemoCommon/Utilities/Asset/hkAssetManagementUtil.h>
#include <Common/Serialize/Util/hkLoader.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#include <Physics/Utilities/Serialize/hkpPhysicsData.h>

#include <Physics/Collide/Shape/Misc/Transform/hkpTransformShape.h>
#include <Physics/Collide/Shape/Convex/ConvexTransform/hkpConvexTransformShape.h>

// For ground
#include <Physics/Utilities/CharacterControl/hkpCharacterControl.h>

// State machine
#include <Physics/Utilities/CharacterControl/StateMachine/hkpDefaultCharacterStates.h>
#include <Physics/Utilities/CharacterControl/StateMachine/hkpCharacterStateManager.h>
#include <Physics/Utilities/CharacterControl/StateMachine/hkpCharacterContext.h>

// Reducing collision tolerances between characters and fixed entities.
#include <Physics/Collide/Agent/hkpCollisionQualityInfo.h>
#include <Physics/Collide/Dispatch/hkpCollisionDispatcher.h>

// Needed to gather contact point stats.
#include <Physics/Collide/Agent/ContactMgr/hkpContactMgr.h>
#include <Physics/Dynamics/Collide/hkpSimpleConstraintContactMgr.h>
#include <Physics/Internal/Collide/Agent3/Machine/Nn/hkpAgentNnTrack.h>

// Includes for collector used by checkSupport.
#include <Physics/Collide/Agent/Collidable/hkpCdPoint.h>
#include <Physics/Collide/Agent/Query/hkpCdPointCollector.h>

DEMO_OPTIONS_DEFINE(StairClimbingRbDemo,Options);

StairClimbingRbDemo::StairClimbingRbDemo(hkDemoEnvironment* env)
:	hkDefaultPhysicsDemo(env),
	m_supportHistory( 0 )
{
	// The half-extents of the floor.
	const hkReal floorX = 20.0f;
	const hkReal floorY = 4.0f;
	const hkReal floorZ = 7.0f;

	// const hkReal slopeFactor = 0.5f * HK_REAL_PI;
	
	//
	// Setup the camera.
	//
	{
		hkVector4 from( 0.0f, floorY * 1.5f, floorZ * 3.f );
		hkVector4 to(0.0f, 0.0f, 0.0f);
		hkVector4 up(0.0f, 1.0f, 0.0f);
		setupDefaultCameras( env, from, to, up );
	}

	//
	// Create the world.
	//
	{
		hkpWorldCinfo info;
		info.m_collisionTolerance = m_options.m_worldCollisionTolerance;
		info.m_contactPointGeneration = hkpWorldCinfo::CONTACT_POINT_ACCEPT_ALWAYS;
		m_world = new hkpWorld( info );

		m_world->lock();

		setupGraphics();

		//
		// Register all collision agents.
		//
		hkpAgentRegisterUtil::registerAllAgents( m_world->getCollisionDispatcher() );
	}

	// The loader is needed to load the newShape from file.
	{
		m_loader = new hkLoader();
	}

	// Create the floor
	{
		hkpRigidBody* floor1;
		const hkVector4 fixedBoxSize( 0.5f * floorX , 0.5f * floorY , 0.5f * floorZ );
		hkpBoxShape* fixedBoxShape = new hkpBoxShape( fixedBoxSize );

		hkpRigidBodyCinfo info;
		{
			info.m_shape = fixedBoxShape;
			info.m_motionType = hkpMotion::MOTION_FIXED;
			info.m_position.set( 0.0f, -floorY * 0.5f, 0.0f);
		}

		floor1 = new hkpRigidBody(info);
		m_world->addEntity(floor1);

		floor1->removeReference();
		fixedBoxShape->removeReference();
	}

	//	The default character shape
	{
		const hkVector4 vertexA( 0.0f, m_options.m_characterCylinderHeight + m_options.m_characterRadius, 0.0f );
		const hkVector4 vertexB( 0.0f, m_options.m_characterRadius, 0.0f );
		m_standShape = new hkpCapsuleShape( vertexA, vertexB, m_options.m_characterRadius );
	}

	//	The alternative character shape
	{
		hkString assetFile = hkAssetManagementUtil::getFilePath("Resources/Physics/levels/character_new_shape.hkx");
		hkRootLevelContainer* container = m_loader->load( assetFile.cString() );
		HK_ASSERT2(0x27343437, container != HK_NULL , "Could not load asset");

		hkpPhysicsData* physics = reinterpret_cast<hkpPhysicsData*>( container->findObjectByType( hkpPhysicsDataClass.getName() ));
		HK_ASSERT2(0x27343635, physics, "No physics loaded");

		// Physics
		if (physics)
		{
			const hkArray<hkpPhysicsSystem*>& psys = physics->getPhysicsSystems();

			HK_ASSERT2(0x27343635, psys.getSize() == 1, "Wrong number of physics systems." );

			// Take only the first shape
			hkpRigidBody *const body = psys[0]->getRigidBodies()[0];

			hkpShape *const shape = const_cast<hkpShape*>(body->getCollidable()->getShape());

			// The stored special shape has different axes to this demo, so we need to put
			// it in a transform shape.
			hkTransform transform;
			{
				hkQuaternion quaternion;
				{
					hkVector4 axis( 1.0f, 0.0f, 0.0f );
					hkReal angle = -0.5f * HK_REAL_PI;
					quaternion.setAxisAngle( axis, angle );
				}
				hkVector4 translation( 0.0f, 0.6f, 0.0f );
				transform.set( quaternion, translation );
			}

			if ( shape->isConvex() )
			{
				m_newShape = new hkpConvexTransformShape( static_cast<hkpConvexShape*>( shape ), transform );
			}
			else
			{
				// Using a transform shape here will cause a warning.
				m_newShape = new hkpTransformShape( shape, transform );
			}
		}
	}

	// Construct the character rigid body
	{
		hkpCharacterRigidBodyCinfo info;
		info.m_mass = 100.0f;
		info.m_shape = m_standShape;

		info.m_up.set( 0.0f, 1.0f, 0.0f );
		info.m_position.set( 0.0f, 0.1f, 1.0f );

		info.m_maxSlope = hkMath::min2( m_options.m_maxSlope, HK_REAL_PI * 0.5f );
		info.m_supportDistance = m_options.m_supportDistance;
		info.m_hardSupportDistance = m_options.m_hardSupportDistance;
		info.m_allowedPenetrationDepth = m_options.m_allowedPenetrationDepth;
		
		m_characterRigidBody = new hkpCharacterRigidBody( info );
		{
			hkpCharacterRigidBodyListener* listener = new hkpCharacterRigidBodyListener();
			m_characterRigidBody->setListener( listener );
			listener->removeReference();
		}
		m_world->addEntity( m_characterRigidBody->m_character );

	}

	// Create the Character state machine and context
	{
		hkpCharacterState* state;
		hkpCharacterStateManager* manager = new hkpCharacterStateManager();

		state = new hkpCharacterStateOnGround();
		manager->registerState( state,	HK_CHARACTER_ON_GROUND);
		state->removeReference();

		state = new hkpCharacterStateInAir();
		manager->registerState( state,	HK_CHARACTER_IN_AIR);
		state->removeReference();

		state = new hkpCharacterStateJumping();
		manager->registerState( state,	HK_CHARACTER_JUMPING);
		state->removeReference();

		state = new hkpCharacterStateClimbing();
		manager->registerState( state,	HK_CHARACTER_CLIMBING);
		state->removeReference();

		m_characterContext = new hkpCharacterContext( manager, HK_CHARACTER_ON_GROUND );
		manager->removeReference();

		// Set character type
		m_characterContext->setCharacterType(hkpCharacterContext::HK_CHARACTER_RIGIDBODY);
	}

	// Create the staircases
	{
		const hkReal stepHeight = ( m_options.m_stairsRise / ( m_options.m_numStepsStart + 1 ) ) + 1.0f;
		const hkReal stepDepth = ( m_options.m_stairsRun / ( m_options.m_numStepsStart + 1 ) ) + 1.0f;
		const hkReal stepWidth = floorX / m_options.m_numStaircases;

		hkpShape* stepShape;
		{
			hkVector4 halfExtents( stepWidth * 0.5f, stepHeight * 0.5f, stepDepth * 0.5f );
			stepShape = new hkpBoxShape( halfExtents, m_options.m_stepConvexRadius );
		}
		
		for ( int i = 0; i < m_options.m_numStaircases; ++i )
		{
			// There is a hidden extra step inside the floor
			const int numSteps = m_options.m_numStepsStart + 1 + ( i * m_options.m_numStepsIncrement );
			const hkReal stepDiv = 1.0f / ( numSteps - 1);
			for ( int j = 0; j < numSteps ; ++j )
			{
				hkpRigidBodyCinfo info;
				{
					info.m_shape = stepShape;
					info.m_motionType = hkpMotion::MOTION_FIXED;
					const hkReal x = -0.5f * floorX + 0.5f * stepWidth + ( i * stepWidth );
					// Allow a tiny piece of the hidden step to stick above the floor, to ensure that the
					// initial step encounter is the correct height.
					const hkReal y = -0.49f * stepHeight + ( j * m_options.m_stairsRise * stepDiv );
					const hkReal z = -0.5f * stepDepth - ( j * m_options.m_stairsRun * stepDiv );
					info.m_position.set( x, y, z );
				}
				hkpRigidBody* step = new hkpRigidBody( info );
				m_world->addEntity( step );
				step->removeReference();
			}
		}
		stepShape->removeReference();
	
	}
	
	m_world->unlock();
}


static void HK_CALL _deadzone(float& stickX, float& stickY)
{
	hkReal INPUT_DEADZONE = 0.15f; // PS2 style .. large

	const float deadzoneScale = 1.0f/(1.0f-INPUT_DEADZONE);
	stickX = ( stickX < -INPUT_DEADZONE) ? (stickX + INPUT_DEADZONE) * deadzoneScale : (
		( stickX > INPUT_DEADZONE ) ? (stickX - INPUT_DEADZONE) * deadzoneScale : 0);
	stickY = ( stickY < -INPUT_DEADZONE) ? (stickY + INPUT_DEADZONE) * deadzoneScale : (
		( stickY > INPUT_DEADZONE ) ? (stickY - INPUT_DEADZONE) * deadzoneScale : 0);
}

void HK_CALL StairClimbingRbDemo::getUserInputForCharacter( hkDemoEnvironment* env, float& posX, float& posY, hkBool& wantJump )
{
	// Only run this function if the window is in focus
	if ( GetForegroundWindow() != env->m_window->getPlatformHandle() )
		return;

	// Mouse
	posX = 0.f;
	posY = 0.f;
	const hkgPad& pad = *(env->m_gamePad);

	bool haveProperGamePad = env->m_window->hasGamePads() && !(env->m_options->m_forceKeyboardGamepad);

	// No gamepad (win32 and ps3 default at the mo)
	if (!haveProperGamePad)
	{
		if (env->m_window->getKeyboard().getKeyState( 'A'))
			posX=1.f;
		if (env->m_window->getKeyboard().getKeyState( 'D'))
			posX=-1.f;
		if (env->m_window->getKeyboard().getKeyState( 'W'))
			posY=-1.f;
		if (env->m_window->getKeyboard().getKeyState( 'S'))
			posY=1.f;
	}
	else if (pad.isValid())
	{
		if ( (pad.getButtonState() & HKG_PAD_BUTTON_L1) == 0)
		{
			float stickX = pad.getStickPosX(1);
			float stickY = pad.getStickPosY(1);
			_deadzone(stickX, stickY);
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
		if ((pad.getButtonState() & HKG_PAD_DPAD_UP) != 0)
			posY=-1.f;
		if ((pad.getButtonState() & HKG_PAD_DPAD_LEFT) != 0)
			posX=1.f;
		if ((pad.getButtonState() & HKG_PAD_DPAD_RIGHT) != 0)
			posX=-1.f;
		if ((pad.getButtonState() & HKG_PAD_DPAD_DOWN) != 0)
			posY=1.f;
	}

	wantJump = ( pad.getButtonState() & HKG_PAD_BUTTON_1 ) != 0;

	// Normalize the movement vector
	hkReal lenSqd = posY * posY + posX * posX;
	if (lenSqd > HK_REAL_MIN)
	{
		lenSqd = hkMath::sqrt(lenSqd);
		posY /= lenSqd;
		posX /= lenSqd;
	}
}


StairClimbingRbDemo::~StairClimbingRbDemo()
{
	m_world->markForWrite();
	m_world->removeEntity( m_characterRigidBody->m_character );
	m_world->unmarkForWrite();
	m_characterRigidBody->removeReference();
	m_characterContext->removeReference();
	m_standShape->removeReference();
	m_newShape->removeReference();
	m_loader->removeReference();
}


hkDemo::Result StairClimbingRbDemo::stepDemo()
{
	hkVector4  up (0.0f, 1.0f, 0.0f );
	{
		m_world->lock();

		//	Get user input data
		hkReal posX = 0.f;
		hkReal posY = 0.f;
		hkBool wantJump = false;
		{
			getUserInputForCharacter(m_env, posX, posY, wantJump);
		}

		HK_TIMER_BEGIN( "set character state", HK_NULL );

		hkpCharacterInput input;
		hkpCharacterOutput output;
		{
			input.m_inputLR = posX;
			input.m_inputUD = posY;

			input.m_wantJump =  wantJump;
			input.m_atLadder = false;

			input.m_up = up;
			{
				// We project the camera direction onto the xz-plane to obtain the forward direction.
				float dir[3];
				m_env->m_window->getViewport( 0 )->getCamera()->getDir( dir );
				input.m_forward.set( dir[0], 0.0f, dir[2] );
			}

			hkStepInfo stepInfo;
			stepInfo.m_deltaTime = m_timestep;
			stepInfo.m_invDeltaTime = 1.0f/m_timestep;

			input.m_stepInfo = stepInfo;

			input.m_characterGravity.setMul4( -16.0f, up );
			input.m_velocity = m_characterRigidBody->getRigidBody()->getLinearVelocity();
			input.m_position = m_characterRigidBody->getRigidBody()->getPosition();

	
			{	
				m_characterRigidBody->checkSupport( stepInfo, input.m_surfaceInfo );

				m_supportHistory = ( m_supportHistory << 1 ) | ( input.m_surfaceInfo.m_supportedState == hkpSurfaceInfo::SUPPORTED );

				// Change character rigid body color according to ground state
				switch( input.m_surfaceInfo.m_supportedState )
				{
					case hkpSurfaceInfo::SUPPORTED:
						HK_SET_OBJECT_COLOR( (hkUlong) m_characterRigidBody->getRigidBody()->getCollidable(), hkColor::rgbFromChars( 0, 255, 0, 100 ) );
						break;
					case hkpSurfaceInfo::UNSUPPORTED:
						HK_SET_OBJECT_COLOR( (hkUlong) m_characterRigidBody->getRigidBody()->getCollidable(), hkColor::rgbFromChars( 0, 0, 255, 100 ) );
						break;
					default:
						HK_SET_OBJECT_COLOR( (hkUlong) m_characterRigidBody->getRigidBody()->getCollidable(), hkColor::rgbFromChars( 255, 0, 0, 100 ) );
						break;
				}
			}

			HK_TIMER_END();
		}

		// Apply the character state machine
		{
			HK_TIMER_BEGIN( "update character state", HK_NULL );

			m_characterContext->update( input, output );

			HK_TIMER_END();
		}

		//Apply the player character controller
		{
			HK_TIMER_BEGIN( "simulate character", HK_NULL );

			// Set output velocity from state machine into character rigid body
			m_characterRigidBody->setLinearVelocity(output.m_velocity, m_timestep);

			HK_TIMER_END();

			m_world->unlock();
		}

		//                           /\  //
		// change to the new shape	[  ] //
		//						     \/  //
		{

			if ( m_env->m_gamePad->wasButtonPressed(HKG_PAD_BUTTON_3) )
			{
				m_world->lock();
				if (m_characterRigidBody->getRigidBody()->getCollidable()->getShape() == m_newShape)
				{
					m_characterRigidBody->getRigidBody()->setShape(m_standShape);
				}
				else
				{
					m_characterRigidBody->getRigidBody()->setShape(m_newShape);
				}
				m_world->unlock();

			}

		}

		// Step the world
		{
			hkDefaultPhysicsDemo::stepDemo();
		}

		// Display state
		{
			char buffer[255];

			hkString::sprintf( buffer, "Support history: " );

			for ( int i = 0; i < 32; ++i )
			{
				buffer[17 + i] = m_supportHistory & ( 1 << i ) ? '#' : '_';
			}
			buffer[17 + 32] = '\0';
			
			m_env->m_textDisplay->outputText(buffer, 20, 270, 0xffffffff);
		}
	}

	return hkDemo::DEMO_OK;
}


#if defined(HK_COMPILER_MWERKS)
#	pragma force_active on
#	pragma fullpath_file on
#endif

static const char helpString[] = \
"This tweakable demo illustrates the effect of parameters on the stair-climbing "
"ability of the rigid body character controller. "
"\n"
"You can switch between a capsule shape and the special shape with \223.";

HK_DECLARE_DEMO(StairClimbingRbDemo, HK_DEMO_TYPE_PRIME, "Stairs Demo", helpString);

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
