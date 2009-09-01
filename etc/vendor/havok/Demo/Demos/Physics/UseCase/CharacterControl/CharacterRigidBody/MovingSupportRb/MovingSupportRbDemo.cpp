/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Common/Base/Container/LocalArray/hkLocalArray.h>

#include <Demos/Physics/UseCase/CharacterControl/CharacterRigidBody/MovingSupportRb/MovingSupportRbDemo.h>

// Used for character rigid body
#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBody.h>
#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBodyListener.h>
// state machine
#include <Physics/Utilities/CharacterControl/hkpCharacterControl.h>
#include <Physics/Utilities/CharacterControl/StateMachine/hkpDefaultCharacterStates.h>
// capsule shape
#include <Physics/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>

// Used for serialization
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Serialize/Util/hkLoader.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#include <Common/Base/Reflection/Registry/hkTypeInfoRegistry.h>
#include <Physics/Utilities/Serialize/hkpPhysicsData.h>
#include <Common/Base/Container/LocalArray/hkLocalBuffer.h>

// Scene Data
#include <Common/SceneData/Scene/hkxScene.h>

// Camera handling
#include <Common/Visualize/hkDebugDisplay.h>
#include <Graphics/Bridge/DisplayHandler/hkgDisplayHandler.h>
#include <Graphics/Bridge/SceneData/hkgSceneDataConverter.h>
#include <Graphics/Common/DisplayObject/hkgDisplayObject.h>
// Transparency raycasting
#include <Physics/Dynamics/Collide/hkpCollisionListener.h>
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastInput.h>
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>
#include <Physics/Collide/Query/Collector/RayCollector/hkpAllRayHitCollector.h>
// Common
#include <Demos/DemoCommon/Utilities/Asset/hkAssetManagementUtil.h>
#include <Demos/DemoCommon/Utilities/GameUtils/GameUtils.h>
#include <Demos/DemoCommon/Utilities/Character/CharacterUtils.h>
#include <Demos/DemoCommon/DemoFramework/hkTextDisplay.h>


// Level colors
#define NORMAL_GRAY				hkColor::rgbFromChars( 192, 192, 192, 255 )
#define TRANSPARENT_GREY		hkColor::rgbFromChars( 192, 192, 192, 125 )

static const hkVector4 UP (0,0,1);
static const hkVector4 gravity ( 0, 0, -9.8f );
static const hkVector4 characterGravity ( 0, 0, -16.0f );

MovingSupportRbDemo::MovingSupportRbDemo(hkDemoEnvironment* env)
:	hkDefaultPhysicsDemo(env)
{

	// Setup the graphics
	{
		// Disable back face culling
		setGraphicsState(HKG_ENABLED_CULLFACE, false);

		// don't really want shadows as makes it too dark
		if (m_env->m_options->m_enableShadows)
		{
			m_env->m_options->m_enableShadows = false;
			m_forcedShadowsOff = true;
			setupLights(m_env); // so that the extra lights are added
		}
		// allow color change on precreated objects
		m_env->m_displayHandler->setAllowColorChangeOnPrecreated(true);
	}

	{
		hkVector4 from( 0.0f, 30.0f, 10.0f);
		hkVector4 to(0.0f, 0.0f, 0.0f);
		hkVector4 up(0.0f, 0.0f, 1.0f);
		setupDefaultCameras( env, from, to, up );
	}

	// Create the world
	{
		hkpWorldCinfo info;
		info.setBroadPhaseWorldSize( 350.0f );
		info.m_gravity.set(0,0,-9.8f);
		//info.m_collisionTolerance = 0.01f;
		info.m_contactPointGeneration = hkpWorldCinfo::CONTACT_POINT_ACCEPT_ALWAYS;

		m_world = new hkpWorld( info );
		m_world->lock();

		hkpAgentRegisterUtil::registerAllAgents(m_world->getCollisionDispatcher());

		setupGraphics();
	}

	// Create the floor.
	{
		hkpRigidBody* floor1;
		hkVector4 fixedBoxSize( 12.0f, 12.0f, 0.5f );
		hkpBoxShape* fixedBoxShape = new hkpBoxShape( fixedBoxSize );

		hkpRigidBodyCinfo info;
		{
			info.m_shape = fixedBoxShape;
			info.m_motionType = hkpMotion::MOTION_FIXED;
			info.m_position.set( 0.0f, 5.0f, -0.5f);
		}

		floor1 = new hkpRigidBody(info);
		m_world->addEntity(floor1);

		floor1->removeReference();
		fixedBoxShape->removeReference();
	}

	// Add keyframed platform
	{
		hkpShape* platform = new hkpBoxShape(hkVector4(3.0,2.5,0.25));
		// Horizontal platform
		{
			hkpRigidBodyCinfo rbci;
			rbci.m_shape = platform;
			rbci.m_motionType = hkpMotion::MOTION_KEYFRAMED;
			rbci.m_position.set( 5.f, 0.0f, 0.25f);
			rbci.m_friction = 1.0f;
			rbci.m_collisionFilterInfo = hkpGroupFilter::calcFilterInfo(hkpGroupFilter::calcFilterInfo(1));

			m_horPlatform = new hkpRigidBody(rbci);
			m_world->addEntity(m_horPlatform);
			HK_SET_OBJECT_COLOR(hkUlong(m_horPlatform->getCollidable()),hkColor::BLUE);
		}

		// Vertical platform
		{
			hkpRigidBodyCinfo rbci;
			rbci.m_shape = platform;
			rbci.m_motionType = hkpMotion::MOTION_KEYFRAMED;
			rbci.m_position.set(-5.f, 0.0f, 3.25f);
			rbci.m_friction = 1.0f;
			rbci.m_collisionFilterInfo = hkpGroupFilter::calcFilterInfo(hkpGroupFilter::calcFilterInfo(1));

			m_verPlatform = new hkpRigidBody(rbci);
			m_world->addEntity(m_verPlatform);
			HK_SET_OBJECT_COLOR(hkUlong(m_verPlatform->getCollidable()),hkColor::BLUE);
		}
		platform->removeReference();
	}

	{ // Add rigid body on horizontal platform
		hkVector4 halfExtents(1.0,2.0,0.25);
		hkpShape* box = new hkpBoxShape( halfExtents );
		{
			hkpRigidBodyCinfo rbci;
			rbci.m_shape =box;
			rbci.m_motionType = hkpMotion::MOTION_BOX_INERTIA;
			rbci.m_position.set(4.0f, 0.0f, 1.25f);

			rbci.m_mass = 100.0f;

			hkpMassProperties massProperties;
			hkpInertiaTensorComputer::computeBoxVolumeMassProperties( halfExtents, rbci.m_mass, massProperties);
			rbci.m_inertiaTensor = massProperties.m_inertiaTensor;
			rbci.m_friction = 1.0f;
			rbci.m_centerOfMass = massProperties.m_centerOfMass;	

			rbci.m_collisionFilterInfo = hkpGroupFilter::calcFilterInfo(hkpGroupFilter::calcFilterInfo(1));

			hkpRigidBody* body = new hkpRigidBody(rbci);
			m_world->addEntity(body);
			m_bodies.pushBack( body );
			m_bodyType.insert( body, true );
		}
		{
			hkpRigidBodyCinfo rbci;
			rbci.m_shape =box;
			rbci.m_motionType = hkpMotion::MOTION_BOX_INERTIA;
			rbci.m_position.set(7.0f, 0.0f, 1.25f);

			rbci.m_mass = 100.0f;

			hkpMassProperties massProperties;
			hkpInertiaTensorComputer::computeBoxVolumeMassProperties( halfExtents, rbci.m_mass, massProperties);
			rbci.m_inertiaTensor = massProperties.m_inertiaTensor;
			rbci.m_friction = 1.0f;
			rbci.m_centerOfMass = massProperties.m_centerOfMass;	

			rbci.m_collisionFilterInfo = hkpGroupFilter::calcFilterInfo(hkpGroupFilter::calcFilterInfo(1));

			hkpRigidBody* body = new hkpRigidBody(rbci);
			m_world->addEntity(body);
			m_bodies.pushBack( body );
			m_bodyType.insert( body, false );
		}
		{ // Add rigid body on vertical platform
			hkpRigidBodyCinfo rbci;
			rbci.m_shape =box;
			rbci.m_motionType = hkpMotion::MOTION_BOX_INERTIA;
			rbci.m_position.set(-3.5f, 0.0f, 5.25f);

			rbci.m_mass = 100.0f;

			hkpMassProperties massProperties;
			hkpInertiaTensorComputer::computeBoxVolumeMassProperties( halfExtents, rbci.m_mass, massProperties);
			rbci.m_inertiaTensor = massProperties.m_inertiaTensor;
			rbci.m_friction = 1.0f;
			rbci.m_centerOfMass = massProperties.m_centerOfMass;	

			rbci.m_collisionFilterInfo = hkpGroupFilter::calcFilterInfo(hkpGroupFilter::calcFilterInfo(1));

			hkpRigidBody* body = new hkpRigidBody(rbci);
			m_world->addEntity(body);
			m_bodies.pushBack( body );
			m_bodyType.insert( body, true );
		}
		{ // Add rigid body on vertical platform
			hkpRigidBodyCinfo rbci;
			rbci.m_shape =box;
			rbci.m_motionType = hkpMotion::MOTION_BOX_INERTIA;
			rbci.m_position.set(-6.5f, 0.0f, 5.25f);

			rbci.m_mass = 100.0f;

			hkpMassProperties massProperties;
			hkpInertiaTensorComputer::computeBoxVolumeMassProperties( halfExtents, rbci.m_mass, massProperties);
			rbci.m_inertiaTensor = massProperties.m_inertiaTensor;
			rbci.m_friction = 1.0f;
			rbci.m_centerOfMass = massProperties.m_centerOfMass;	

			rbci.m_collisionFilterInfo = hkpGroupFilter::calcFilterInfo(hkpGroupFilter::calcFilterInfo(1));

			hkpRigidBody* body = new hkpRigidBody(rbci);
			m_world->addEntity(body);
			m_bodies.pushBack( body );
			m_bodyType.insert( body, false );
		}
		box->removeReference();
	}


	//	Create a character rigid body
	{
		// Create a capsule to represent the character standing
		hkVector4 vertexA(0,0, 0.4f);
		hkVector4 vertexB(0,0,-0.4f);

		m_standShape = new hkpCapsuleShape(vertexA, vertexB, .6f);

		// Construct a character rigid body
		hkpCharacterRigidBodyCinfo info;
		info.m_mass = 100.0f;
		info.m_shape = m_standShape;
		
		info.m_up = UP;
		info.m_position.set(0.0f, 15.0f, 1.5f);
		info.m_maxSlope = HK_REAL_PI/3.0f;
		
		m_characterRigidBody = new hkpCharacterRigidBody( info );
		info.m_maxForce = 1000.0f;
		{
			hkpCharacterRigidBodyListener* listener = new hkpCharacterRigidBodyListener();
			m_characterRigidBody->setListener( listener );
			listener->removeReference();
		}

		m_world->addEntity( m_characterRigidBody->getRigidBody() );
	}

	// Create the character state machine
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

		m_characterContext = new hkpCharacterContext(manager, HK_CHARACTER_ON_GROUND);
		m_characterContext->setCharacterType(hkpCharacterContext::HK_CHARACTER_RIGIDBODY);
		manager->removeReference();
	}

	// Create some objects
	{
		const hkReal startX = -6;
		const hkReal gapX = 12.0f / ( NUM_IN_ROWS - 1 );
		const hkReal startY = 12.0f;
		const hkReal gapY = -4.0f;
		const hkReal massStart = 100.0f;
		const hkReal massInc = 50.0f;

		for ( int j = 0; j < NUM_OF_ROWS; ++j )
		{
			const hkReal mass = massStart + j * massInc;
			for ( int i = 0; i < NUM_IN_ROWS; ++i )
			{
				hkpRigidBody* body;
				hkVector4 pos( startX + i * gapX, startY + j * gapY, 1.0f );
				switch ( i % 4 )
				{
					case( 0 ):
						body = GameUtils::createSphere( 0.8f, mass, pos );
						break;
					case( 1 ):
						body = GameUtils::createCylinder( 0.6f, 1.3f, mass, pos );
						break;
					case( 2 ):
						body = GameUtils::createCapsuleFromBox( hkVector4( 1.3f, 1.5f, 1.3f), mass, pos );
						break;
					default:
						body = GameUtils::createRandomConvexGeometric( 1.0f, mass, pos , 10 );
						break;
				}			
				m_world->addEntity( body );
				m_bodyType.insert( body, j % 2 );
				m_bodies.pushBack( body );
			}
		}
	}

	const int numBodies = m_bodies.getSize();
	for ( int i = 0; i < numBodies; ++i )
	{
		hkpRigidBody *const body = m_bodies[i];
		HK_SET_OBJECT_COLOR( (hkUlong) body->getCollidable(), m_bodyType.getWithDefault( body, false ) ? hkColor::YELLOW : hkColor::CYAN );
	}

	// Set global time
	m_time = 0.0f;

	m_world->unlock();
}

MovingSupportRbDemo::~MovingSupportRbDemo()
{
	m_world->markForWrite();

	m_characterRigidBody->removeReference();

	m_standShape->removeReference();
	
	m_horPlatform->removeReference();
	m_verPlatform->removeReference();

	delete m_characterContext;

	const int numBodies = m_bodies.getSize();
	for ( int i = 0; i < numBodies; ++i )
	{
		m_bodies[i]->removeReference();
	}

	// need to delete world before we wipe the loader
	if(m_world)
	{
		m_world->removeReference();
		m_world = HK_NULL;
	}
}

/////////////////////////////////////////////////////////////////////

void MovingSupportRbDemo::getGround( const hkArray<hkpCharacterRigidBody::SupportInfo>& supportInfo, hkpSurfaceInfo& ground ) const
{
	// Produce an average version of the ground

	ground.m_surfaceVelocity.setZero4();
	ground.m_surfaceNormal.setZero4();
	ground.m_surfaceDistanceExcess = 0.0f;
	ground.m_surfaceIsDynamic = false;

	const int numSupportInfo = supportInfo.getSize();
	for ( int i = 0; i < numSupportInfo; ++i )
	{
		const hkpCharacterRigidBody::SupportInfo& support = supportInfo[i];
		ground.m_surfaceNormal.add4( support.m_point.getNormal() );
		ground.m_surfaceDistanceExcess += support.m_point.getDistance();
		const hkpMotion::MotionType motionType = support.m_rigidBody->getMotionType();
		if ( motionType == hkpMotion::MOTION_KEYFRAMED )
		{
			hkVector4 pointVelocity;
			support.m_rigidBody->getPointVelocity( support.m_point.getPosition(), pointVelocity );
			ground.m_surfaceVelocity.add4( pointVelocity );
		}
		else if ( motionType != hkpMotion::MOTION_FIXED )
		{
			ground.m_surfaceIsDynamic = true;
			if ( m_bodyType.getWithDefault ( support.m_rigidBody, false ) == hkBool32( true ) )
			{
				hkVector4 pointVelocity;
				support.m_rigidBody->getPointVelocity( support.m_point.getPosition(), pointVelocity );
				ground.m_surfaceVelocity.add4( pointVelocity );
			}
		}
	}

	ground.m_surfaceNormal.normalize3();
	const hkReal portion = 1.f / numSupportInfo;

	ground.m_surfaceVelocity.mul4( portion );
	ground.m_surfaceDistanceExcess = ( ground.m_surfaceDistanceExcess * portion );

	if ( ground.m_surfaceIsDynamic )
	{
		// We need to apply the character's weight onto dynamic bodies. We do this by
		// setting a positive surfaceDistanceExcess which the controller should try
		// to reduce by applying gravity.
		ground.m_surfaceDistanceExcess = 0.01f;
	}
	else
	{
		// For fixed and keyframed bodies, we subtract m_hardSupportDistance from the excess
		// to ensure an extra gap below the character. This improves the smoothness of the
		// character's motion over the ground.
		ground.m_surfaceDistanceExcess -= m_characterRigidBody->m_hardSupportDistance;
	}

	// For dynamic supporting bodies which do keep velocity, we apply gravity representing the 
	// force required to keep the character in position.
	hkVector4 impulse;
	{
		impulse.setMul4( m_characterRigidBody->m_character->getMass() * m_timestep, m_world->getGravity() );
		// We want the component of the impulse tangential to the surface.
		const hkSimdReal normal = impulse.dot3( ground.m_surfaceNormal );
		impulse.setAddMul4( impulse, ground.m_surfaceNormal, -normal );
		// Divide the amount of impulse by the number of supporting surfaces
		impulse.mul4( 1.0f / numSupportInfo );
	}

	for ( int i = 0; i < numSupportInfo; ++i )
	{
		const hkpCharacterRigidBody::SupportInfo& support = supportInfo[i];

		if ( m_bodyType.getWithDefault( support.m_rigidBody, false ) == hkBool32( true ) )
		{
			// Apply the impulse at the contact point.
			support.m_rigidBody->applyPointImpulse( impulse, support.m_point.getPosition() );
		}
	}
}


hkDemo::Result MovingSupportRbDemo::stepDemo()
{
	// Process inputs, calculate state, set new velocity
	{
		m_world->lock();

		// update total run time
		m_time += m_timestep;

		//	Get user input data
		hkReal posX = 0.f;
		hkReal posY = 0.f;
		hkBool wantJump = false;
		{
			getUserInputForCharacter(m_env, posX, posY, wantJump);
		}

		{
			hkpCharacterInput input;
			input.m_inputLR = posX;
			input.m_inputUD = posY;

			input.m_wantJump =  m_env->m_window->getMouse().wasButtonPressed(HKG_MOUSE_LEFT_BUTTON)
				|| m_env->m_gamePad->wasButtonPressed(HKG_PAD_BUTTON_1);
			input.m_atLadder = false;

			input.m_up = UP;
			{
				// We project the camera direction onto the xz-plane to obtain the forward direction.
				float dir[3];
				m_env->m_window->getViewport( 0 )->getCamera()->getDir( dir );
				input.m_forward.set( dir[0], dir[1], 0.0f );
			}

			hkStepInfo stepInfo;
			stepInfo.m_deltaTime = m_timestep;
			stepInfo.m_invDeltaTime = 1.0f/m_timestep;
			stepInfo.m_endTime = m_time;

			input.m_stepInfo = stepInfo;
			input.m_characterGravity.set(0,0,-16);
			input.m_velocity = m_characterRigidBody->getLinearVelocity();
			input.m_position = m_characterRigidBody->getPosition();

			hkArray<hkpCharacterRigidBody::SupportInfo> supportInfo;
			input.m_surfaceInfo.m_supportedState = m_characterRigidBody->getSupportInfo( stepInfo, supportInfo );
			if ( input.m_surfaceInfo.m_supportedState != hkpSurfaceInfo::UNSUPPORTED )
			{
				getGround( supportInfo, input.m_surfaceInfo );
			}
			
			// Apply the state machine
			hkpCharacterOutput output;
			{
				m_characterContext->update(input, output);
			}

			// Feed output velocity from state machine into character rigid body
			m_characterRigidBody->setLinearVelocity(output.m_velocity, m_timestep);
		}

		// Display state
		{
			hkpCharacterStateType state = m_characterContext->getState();
			char * stateStr;

			switch (state)
			{
				case HK_CHARACTER_ON_GROUND:
					stateStr = "On Ground";	break;
				case HK_CHARACTER_JUMPING:
					stateStr = "Jumping"; break;
				case HK_CHARACTER_IN_AIR:
					stateStr = "In Air"; break;
				case HK_CHARACTER_CLIMBING:
					stateStr = "Climbing"; break;
				default:
					stateStr = "Other";	break;
			}
			char buffer[255];
			hkString::snprintf(buffer, 255, "State : %s", stateStr);
			m_env->m_textDisplay->outputText(buffer, 20, 270, 0xffffffff);
		}

		m_world->unlock();
	}

	// Step the world
	{
		hkDefaultPhysicsDemo::stepDemo();
	}

	// Move the platforms
	{
		m_world->lock();

		moveHorizontalPlatform();

		moveVerticalPlatform();

		m_world->unlock();
	}

	return hkDemo::DEMO_OK;
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


void HK_CALL MovingSupportRbDemo::getUserInputForCharacter( hkDemoEnvironment* env, float& posX, float& posY, hkBool& wantJump )
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

void MovingSupportRbDemo::moveHorizontalPlatform()
{
	const hkReal velAplitude = 3.0f; 
	const hkReal velOmega = 1.0f;

	hkVector4 newVelocity; newVelocity = m_horPlatform->getLinearVelocity();
	newVelocity(0) = velAplitude*cos(velOmega*m_time);
	m_horPlatform->setLinearVelocity(newVelocity);
}

void MovingSupportRbDemo::moveVerticalPlatform()
{
	const hkReal velAplitude = 3.0f; 
	const hkReal velOmega = 1.0f;

	hkVector4 newVelocity; newVelocity = m_verPlatform->getLinearVelocity();
	newVelocity(2) = velAplitude*cos(velOmega*m_time);
	m_verPlatform->setLinearVelocity(newVelocity);
}

#if defined(HK_COMPILER_MWERKS)
#	pragma force_active on
#	pragma fullpath_file on
#endif

static const char helpString[] = \
"The motion of the character rigid body controller is defined relative to the surface which supports it. "
"The surface information is obtained by identifying which of the character's contact points provide "
"support, and averaging their properties. "
"\n"
"For fixed and keyframed bodies, averaging contact point velocities is appropriate. "
"However, when a character stands on a dynamic body, it may cause its supporting surface to move. "
"Since motion is defined relative to this surface, this can lead to strange feedback effects. "
"\n"
"To avoid this, the default behavior is to ignore the velocity of dynamic surfaces. "
"Unfortunately, this means that the character cannot ride on a rigid body which is itself "
"supported by a keyframed surface."
"\n"
"This demo shows an approach to this issue. "
"\n"
"There are two kinds of dynamic rigid bodies: "
"\n"
"With CYAN bodies, the contact point velocities are ignored, as would be the default case. "
"\n"
"With YELLOW bodies, the contact point velocities are used, so the character can ride "
"on them when they are top of the keyframed platforms. "
"\n"
"To get a more believable response from the yellow bodies in general, we apply an additional force to them "
"representing the opposite force to the frictional force which is (we assume) keeping the "
"character in its supported position.";

HK_DECLARE_DEMO(MovingSupportRbDemo, HK_DEMO_TYPE_PRIME, "CharacterTest", helpString);

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
