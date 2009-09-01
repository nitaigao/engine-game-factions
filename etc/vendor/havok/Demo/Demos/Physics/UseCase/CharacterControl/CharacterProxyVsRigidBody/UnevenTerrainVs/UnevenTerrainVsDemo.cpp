/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>

#include <Demos/Physics/UseCase/CharacterControl/CharacterProxyVsRigidBody/UnevenTerrainVs/UnevenTerrainVsDemo.h>

#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/Container/LocalArray/hkLocalArray.h>

#include <Demos/DemoCommon/Utilities/GameUtils/Landscape/LandscapeRepository.h>

#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBody.h>
#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBodyListener.h>
#include <Physics/Utilities/CharacterControl/StateMachine/hkpDefaultCharacterStates.h>
#include <Physics/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>

#include <Physics/Utilities/CharacterControl/CharacterProxy/hkpCharacterProxy.h>
#include <Physics/Dynamics/Phantom/hkpSimpleShapePhantom.h>


#include <Common/Base/Types/Color/hkColor.h>
#include <Common/Visualize/hkDebugDisplay.h>


static const hkVector4 UP(0,1,0);
static const hkVector4 characterStart( 60.f, 2.f, -10.f );

DEMO_OPTIONS_DEFINE(UnevenTerrainVsDemo,Options);

UnevenTerrainVsDemo::UnevenTerrainVsDemo(hkDemoEnvironment* env)
:	hkDefaultPhysicsDemo(env)
{

	// Setup the graphics
	{
		forceShadowState(false);
	}

	// Create the world
	{
		hkpWorldCinfo info;
		info.setBroadPhaseWorldSize( 350.0f );  
		info.m_gravity.set(0, -9.8f, 0);
		info.m_contactPointGeneration = hkpWorldCinfo::CONTACT_POINT_ACCEPT_ALWAYS;
		info.m_collisionTolerance = m_options.m_worldCollisionTolerance;
		m_world = new hkpWorld( info );
		m_world->lock();

		hkpAgentRegisterUtil::registerAllAgents(m_world->getCollisionDispatcher());

		setupGraphics();
	}

	// Setup layer collision
	{
		// Replace filter
		hkpGroupFilter* groupFilter = new hkpGroupFilter();

		// We disable collisions between characters
		groupFilter->disableCollisionsBetween(LAYER_CHARACTER_PROXY, LAYER_CHARACTER_RIGIDBODY);
		m_world->setCollisionFilter( groupFilter, true);
		groupFilter->removeReference();
	}

	// Create the ground using the landscape repository
	{
		int landscapeIndex = LandscapeRepository::getInstance().getLandscapeIndexByName("simpleFlatLandOneMetreTris");
		m_landscapeContainer = LandscapeRepository::getInstance().getLandscape(landscapeIndex);

		hkpRigidBodyCinfo groundInfo;
		groundInfo.m_motionType = hkpMotion::MOTION_FIXED;
		groundInfo.m_shape = m_landscapeContainer->m_shape;

		hkpRigidBody* groundbody = new hkpRigidBody(groundInfo);

		m_world->addEntity(groundbody)->removeReference();

		setupDefaultCameras( env, m_landscapeContainer->m_cameraFrom, m_landscapeContainer->m_cameraTo, hkVector4(0,1,0) );

	}

	AabbSpawnUtil spawnUtil( m_landscapeContainer->m_spawnVolumes );

	const hkReal characterMass = 100.0f;
	
	hkpShape* characterShape;
	{
		// Create a capsule to represent the character standing
		hkVector4 top( 0, m_options.m_characterCylinderHeight * 0.5f, 0 );
		hkVector4 bottom( 0, -m_options.m_characterCylinderHeight * 0.5f, 0 );		

		characterShape = new hkpCapsuleShape( top, bottom, m_options.m_characterRadius );
	}

	{
		// Construct a character rigid body
		hkpCharacterRigidBodyCinfo info;
		info.m_mass = characterMass;
		info.m_shape = characterShape;

		info.m_up = UP;
		info.m_position = characterStart;
		info.m_collisionFilterInfo = hkpGroupFilter::calcFilterInfo( LAYER_CHARACTER_RIGIDBODY, 0 );
		info.m_supportDistance = m_options.m_rbSupportDistance;
		info.m_hardSupportDistance = m_options.m_rbHardSupportDistance;
		info.m_allowedPenetrationDepth = m_options.m_rbAllowedPenetrationDepth;

		m_characterRigidBody = new hkpCharacterRigidBody( info );

		hkpCharacterRigidBodyListener* listener = new hkpCharacterRigidBodyListener();
		m_characterRigidBody->setListener( listener );
		listener->removeReference();

		m_world->addEntity( m_characterRigidBody->getRigidBody() );

		characterShape->removeReference();
	}

	// Create the Character state machine and context
	{
		hkpCharacterStateManager* manager;
		hkpCharacterState* state;
		manager = new hkpCharacterStateManager();

		static_cast<hkpCharacterStateOnGround*>( state = new hkpCharacterStateOnGround() )->setSpeed( m_options.m_characterWalkSpeed );
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

	//	Create a character proxy object
	{
		// Construct a shape phantom
		m_phantom = new hkpSimpleShapePhantom( characterShape, hkTransform::getIdentity(), hkpGroupFilter::calcFilterInfo( LAYER_CHARACTER_PROXY, 0 ) );

		// Add the phantom to the world
		m_world->addPhantom(m_phantom);
		m_phantom->removeReference();

		// Construct a character proxy
		hkpCharacterProxyCinfo cpci;
		cpci.m_position = characterStart;
		cpci.m_staticFriction = 0.0f;
		cpci.m_dynamicFriction = 1.0f;
		cpci.m_up = UP;
		cpci.m_userPlanes = 4;
		
		cpci.m_shapePhantom = m_phantom;
		m_characterProxy = new hkpCharacterProxy( cpci );
	}

	// Create the character proxy state machine and context
	{
		hkpCharacterState* state;
		hkpCharacterStateManager* manager = new hkpCharacterStateManager();

		static_cast<hkpCharacterStateOnGround*>( state = new hkpCharacterStateOnGround() )->setSpeed( m_options.m_characterWalkSpeed );
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

		m_characterProxyContext = new hkpCharacterContext(manager, HK_CHARACTER_ON_GROUND);
		manager->removeReference();
	}

	//Initialized the round robin counter
	m_tick = 0;
	m_unsupportedFramesCountRb = 0;
	m_unsupportedFramesCountProxy = 0;

	m_filterRigidBody.m_framesInAir = m_options.m_clientStateFiltering;
	m_filterProxy.m_framesInAir = m_options.m_clientStateFiltering;

	m_world->unlock();
}

UnevenTerrainVsDemo::~UnevenTerrainVsDemo()
{
	m_world->lock();

	m_characterRigidBody->removeReference();	
	delete m_characterContext;
	m_characterProxy->removeReference();
	delete m_characterProxyContext;

	m_world->unlock();
}


void UnevenTerrainVsDemo::filterStates( FilterInfo& filter, hkpSurfaceInfo& ground )
{
	if ( ground.m_supportedState != hkpSurfaceInfo::SUPPORTED )
	{
		if ( filter.m_framesInAir < m_options.m_clientStateFiltering )
		{
			ground = filter.m_previousGround;
		}
		++filter.m_framesInAir;
	}
	else
	{
		filter.m_previousGround = ground;
		// The stored ground might be the edge of a bump. Thus, artificially traveling
		// along it for a few extra frames will only make the bump worse. Instead
		// we store a "flattened" version of it.
		filter.m_previousGround.m_surfaceNormal = UP;
		filter.m_framesInAir = 0;
	}
}


hkDemo::Result UnevenTerrainVsDemo::stepDemo()
{
	HK_TIMER_BEGIN( "simulate multiply characters", HK_NULL );

	m_world->lock();

	hkVector4 up;
	up.setNeg4( m_world->getGravity() );
	up.normalize3();

	m_tick++;

	hkpCharacterInput inputRb;
	hkpCharacterInput inputProxy;
	// Fill in the state machine input structure for character rigid body
	{
		inputRb.m_atLadder = false;
		inputRb.m_up = up;

		// Steer the characters
		inputRb.m_inputLR = 0.0f;
		inputRb.m_inputUD = 1.0f;
		{
			// The factor 70.0f gives a turning circle which fits in the level 
			// for the default walk speed of 10.0f.
			hkReal walkSpeedFactor = m_options.m_characterWalkSpeed / 70.0f;
			hkReal time = hkReal(m_tick) * walkSpeedFactor / 60.0f;
			const hkReal x = hkMath::sin(time);
			const hkReal z = hkMath::cos(time);
			inputRb.m_forward.set( x, 0, z );
			inputRb.m_forward.normalize3();
		}

		inputRb.m_wantJump = false;
	
		hkStepInfo stepInfo;
		stepInfo.m_deltaTime = m_timestep;
		stepInfo.m_invDeltaTime = 1.0f/m_timestep;

		inputRb.m_stepInfo = stepInfo;

		inputRb.m_characterGravity.set( 0.0f, m_options.m_characterGravity, 0.0f );
		
		inputProxy = inputRb;

		// character rigid body specific code

		inputRb.m_velocity = m_characterRigidBody->getLinearVelocity();
		inputRb.m_position = m_characterRigidBody->getPosition();
		m_characterRigidBody->checkSupport(stepInfo, inputRb.m_surfaceInfo);

		filterStates( m_filterRigidBody, inputRb.m_surfaceInfo );

		m_supportHistoryRb <<= 1;
		if ( inputRb.m_surfaceInfo.m_supportedState == hkpSurfaceInfo::SUPPORTED )
		{
			++m_supportHistoryRb;
		}
		else
		{
			++m_unsupportedFramesCountRb;
		}


		// character proxy specific code

		inputProxy.m_velocity = m_characterProxy->getLinearVelocity();
		inputProxy.m_position = m_characterProxy->getPosition();
		hkVector4 down;	down.setNeg4(UP);
		m_characterProxy->checkSupport(down, inputProxy.m_surfaceInfo);

		filterStates( m_filterProxy, inputProxy.m_surfaceInfo );
		
		m_supportHistoryProxy <<= 1;
		if ( inputProxy.m_surfaceInfo.m_supportedState == hkpSurfaceInfo::SUPPORTED )
		{
			++m_supportHistoryProxy;
		}
		else
		{
			++m_unsupportedFramesCountProxy;
		}
	}

	hkpCharacterOutput outputRb;
	hkpCharacterOutput outputProxy;
	// Apply the character state machine
	{
		HK_TIMER_BEGIN( "update character state", HK_NULL );

		m_characterContext->update(inputRb, outputRb);
		m_characterProxyContext->update(inputProxy, outputProxy);

		HK_TIMER_END();

	}

	//Apply the character controllers
	{
		HK_TIMER_BEGIN( "simulate character", HK_NULL );

		// Feed the output velocity from state machine into character rigid body
		m_characterRigidBody->setLinearVelocity(outputRb.m_velocity, m_timestep);
		
		m_characterProxy->setLinearVelocity(outputProxy.m_velocity );
		hkStepInfo si;
		si.m_deltaTime = m_timestep;
		si.m_invDeltaTime = 1.0f/m_timestep;
		m_characterProxy->integrate( si, m_world->getGravity() );

		HK_TIMER_END();
	}

	{
		// If the character has fallen off the world we reposition them
		if ( ( m_characterProxy->getPosition()(1) < -10.0f ) || ( m_characterRigidBody->getPosition()(1) < -10.0f ) )
		{
			m_characterProxy->setPosition( characterStart );
			m_characterProxy->setLinearVelocity( hkVector4::getZero() );
			m_characterRigidBody->getRigidBody()->setPosition(characterStart);
			m_characterRigidBody->setLinearVelocity( hkVector4::getZero(), m_timestep );
			m_tick = 0;
		}
	}

	m_world->unlock();
	
	// Display state
	{
		char historyRb[33];
		char historyProxy[33];
		char buffer[255];

		for ( int i = 0; i < 32; ++i )
		{
			historyRb[i] = m_supportHistoryRb & ( 1 << i ) ? '#' : '_';
			historyProxy[i] = m_supportHistoryProxy & ( 1 << i ) ? '#' : '_';
		}
		historyRb[32] = '\0';
		historyProxy[32] = '\0';

		hkString::sprintf( buffer, "Rigid body unsupported frames: %d\n"
								   "Proxy unsupported frames:      %d\n\n"
								   "Rigid body support history:    %s\n"
								   "Proxy support history:         %s\n", m_unsupportedFramesCountRb, m_unsupportedFramesCountProxy, historyRb, historyProxy );

		m_env->m_textDisplay->outputText( buffer, 20, 200, 0xffffffff );
	}

	// Step the world
	{
		hkDefaultPhysicsDemo::stepDemo();
	}

	HK_TIMER_END();

	return hkDemo::DEMO_OK;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma force_active on
#	pragma fullpath_file on
#endif

static const char helpString[] = \
"A tweakable demo which compares the sensitivity of the two characters controllers with respect to uneven terrain."
"\n"
"An adjustable amount of client-side filtering is applied to the characters' states. "
"This can be disabled by tweaking clientStateFiltering to 0.";

HK_DECLARE_DEMO(UnevenTerrainVsDemo, HK_DEMO_TYPE_PRIME, "UnevenTerrainVsDemo", helpString);

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
