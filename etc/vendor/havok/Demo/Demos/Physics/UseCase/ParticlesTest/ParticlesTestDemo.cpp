/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Demos/Physics/UseCase/ParticlesTest/ParticlesTestDemo.h>
#include <Demos/DemoCommon/Utilities/Particles/HkgParticleSystem/HkgSmokeParticleSystem.h>
#include <Demos/DemoCommon/Utilities/Particles/HkgParticleSystem/HkgDebrisParticleSystem.h>
#include <Demos/DemoCommon/Utilities/Particles/HkgParticleSystem/HkgSparksParticleSystem.h>
#include <Demos/DemoCommon/Utilities/Particles/HkgParticleSystem/HkgExplosionParticleSystem.h>
#include <Demos/DemoCommon/Utilities/Particles/HkgParticleSystem/HkgDustParticleSystem.h>
#include <Demos/DemoCommon/Utilities/Particles/Utilities/DiskEmissionUtil.h>
#include <Demos/DemoCommon/Utilities/Particles/Listener/ScrapeParticleListener.h>
#include <Graphics/Common/DisplayWorld/hkgDisplayWorld.h>
#include <Graphics/Common/DisplayObject/hkgParticleDisplayObject.h>
#include <Graphics/Common/Font/hkgFont.h>
#include <Common/Visualize/hkDebugDisplay.h>
#include <Physics/Dynamics/World/Util/KdTree/hkpKdTreeWorldManager.h>

static const hkUint32 SPARKS_EMIT_PROPERTY_KEY = 583721;

static hkgMaterial* createParticleMaterial( hkDemoEnvironment* env, const char* shaderFile,	const char* textureFile, const char* vertexShaderProg,
	const char* geomShaderProg, const char* pixelShaderProg, void (HK_CALL* vertexShaderBindCallback)(hkgShader* shader) = HK_NULL )
{
	hkgWindow* window = env->m_window;
	hkgDisplayContext* context = window->getContext();

	context->lock();

	// Material
	hkgMaterial* mat = hkgMaterial::create();
	mat->setDiffuseColor(1.0f, 1.0f, 1.0f, 0.3f);

	if(!window->supportsShaderCompilation() || !window->shaderSupportGreaterOrEqualTo(2)) 
	{
		HK_WARN(0x02346, "Particle demos require shader hardware to display properly.");
	}
	else
	{
		// Shaders
		hkgShader* vertexShader = hkgShader::create(HKG_VERTEX_SHADER, context);
		hkgShader* pixelShader = hkgShader::create(HKG_PIXEL_SHADER, context);

		// HKG DX10 requires geom shader to do point to quad/sprite expansion
		hkgShader* geomShader = HK_NULL;
		hkString shaderName;
		if(geomShaderProg && window->geometryShaderMajorVersion() > 0)
		{
			geomShader = hkgShader::create(HKG_GEOMETRY_SHADER, context);
			shaderName = hkString("./Resources/Common/Graphics/Particles/") + hkString(shaderFile) +
				hkString("10") + hkString(vertexShader->getDefaultFileNameExtension());
		}
		else
		{
			shaderName = hkString("./Resources/Common/Graphics/Particles/") + hkString(shaderFile) +
				hkString(vertexShader->getDefaultFileNameExtension());
		}

		// No Shadows
		HKG_SHADER_RENDER_STYLE normalStyle = HKG_SHADER_RENDER_1LIGHTS | HKG_SHADER_RENDER_MODULATE_TEXTURE0;
		const char** defines = HK_NULL;
		vertexShader->realizeCompileFromFile(shaderName.cString(), vertexShaderProg, normalStyle, HK_NULL, defines);
		pixelShader->realizeCompileFromFile(shaderName.cString(), pixelShaderProg, normalStyle, HK_NULL, defines);
		if(geomShader)
		{
			geomShader->realizeCompileFromFile(shaderName.cString(), geomShaderProg, normalStyle, HK_NULL, defines);
		}

		vertexShader->m_userBindCallback = vertexShaderBindCallback;

		// Add shaders and texture to mat
		hkgShaderCollection* effect = hkgShaderCollection::create();

		effect->addShaderGrouping(vertexShader, pixelShader, geomShader);
		vertexShader->removeReference();
		pixelShader->removeReference();
		if(geomShader)
		{
			geomShader->removeReference();
		}

		mat->setShaderCollection(effect);
		effect->removeReference();

		// Texture
		if(textureFile)
		{
			hkgTexture* tex = hkgTexture::create(context);
			hkString textureName = hkString("./Resources/Common/Graphics/Particles/") + hkString(textureFile);
			tex->loadFromFile(textureName.cString());
			tex->realize(); // make the h/w version
			mat->addTexture(tex);
			tex->removeReference();
		}
	}

	context->unlock();

	return mat;
}

static void createPlatformAndBox(hkpWorld* world, const hkVector4& position, hkpRigidBody** platform = HK_NULL, hkpRigidBody** box = HK_NULL)
{
	//
	// Create the fixed platform
	//
	{
		hkVector4 platformSize(4.f, 0.25f, 1.35f);
		hkpBoxShape* platformShape = new hkpBoxShape(platformSize, 0);

		hkpRigidBodyCinfo info;
		info.m_shape = platformShape;
		info.m_motionType = hkpMotion::MOTION_FIXED;
		info.m_position = position;
		info.m_restitution = 0.8f;
		info.m_friction = 1.0f;

		hkpRigidBody* platformRigidBody = new hkpRigidBody(info);
		platformShape->removeReference();
		world->addEntity(platformRigidBody);

		if(platform)
		{
			*platform = platformRigidBody;
		}
		else
		{
			platformRigidBody->removeReference();
		}
	}

	//
	// Create the moving box
	//
	{
		hkVector4 boxSize(0.3f, 0.3f, 0.3f);
		hkpBoxShape* boxShape = new hkpBoxShape(boxSize, 0);

		hkpRigidBodyCinfo info;
		hkpInertiaTensorComputer::setShapeVolumeMassProperties(boxShape, 1.f, info);
		info.m_shape = boxShape;
		info.m_motionType = hkpMotion::MOTION_BOX_INERTIA;
		info.m_position = position;
		info.m_position.add4(hkVector4(0.f, 1.f, 0.f));
		hkVector4 axis(1.f, 2.f, 3.f);
		axis.normalize3();
		info.m_rotation.setAxisAngle(axis, -0.7f);
		info.m_restitution = 0.5f;
		info.m_friction = 0.1f;

		hkpRigidBody* boxRigidBody = new hkpRigidBody(info);
		boxShape->removeReference();
		world->addEntity(boxRigidBody);

		if(box)
		{
			*box = boxRigidBody;
		}
		else
		{
			boxRigidBody->removeReference();
		}
	}
}

static void HK_CALL smokeVertexShaderBindCallback(hkgShader* shader)
{
	float smokeFrontLitColor[] = { 1.f, 1.f, 1.f, 0.25f };
	shader->setFloatInputByName("smokeFrontLitColor", smokeFrontLitColor);

	float smokeBackLitColor[] = { 0.5f, 0.5f, 0.6f, 0.25f };
	shader->setFloatInputByName("smokeBackLitColor", smokeBackLitColor);
}

static void HK_CALL debrisVertexShaderBindCallback(hkgShader* shader)
{
	float debrisFrontLitColor[] = { 1.f, 0.9f, 0.8f, 1.f };
	shader->setFloatInputByName("debrisFrontLitColor", debrisFrontLitColor);

	float debrisBackLitColor[] = { 0.7f, 0.63f, 0.56f, 1.f };
	shader->setFloatInputByName("debrisBackLitColor", debrisBackLitColor);
}

static void HK_CALL dustVertexShaderBindCallback(hkgShader* shader)
{
	float dustColor1[] = { 130/255.f, 110/255.f, 81/255.f, 1.f };
	shader->setFloatInputByName("dustColor1", dustColor1);

	float dustColor2[] = { 60/255.f, 48/255.f, 41/255.f, 1.f };
	shader->setFloatInputByName("dustColor2", dustColor2);

	float nearFadeDist[] = { 1.f, 0.f, 0.f, 0.f };
	shader->setFloatInputByName("nearFadeDist", nearFadeDist);

	float farFadeDist[] = { 2.f, 0.f, 0.f, 0.f };
	shader->setFloatInputByName("farFadeDist", farFadeDist);
}

static void HK_CALL sparkVertexShaderBindCallback(hkgShader* shader)
{
	float sparkSize[] = { 0.04f, 0.f, 0.f, 0.f };
	shader->setFloatInputByName("sparkSize", sparkSize);
}

static void HK_CALL explosionVertexShaderBindCallback(hkgShader* shader)
{
	float explosionAlpha[] = { 0.05f, 0.f, 0.f, 0.f };
	shader->setFloatInputByName("explosionAlpha", explosionAlpha);
}

ParticlesTestDemo::ParticlesTestDemo( hkDemoEnvironment* env)
	: hkDefaultPhysicsDemo(env),
	  m_smokeContinuousEmissionUtil(70.f),
	  m_smokeChimneyEmissionUtil1(hkVector4(0.f, 0.5f, 4.f), 10.f*HK_REAL_DEG_TO_RAD, 4.f, 0.f),
	  m_smokeChimneyEmissionUtil2(hkVector4(0.f, 0.f, 0.f), 10.f*HK_REAL_DEG_TO_RAD, 4.f, 0.63f),
	  m_debrisContinuousEmissionUtil(200.f),
	  m_sparksContinuousEmissionUtil(200.f)
{
	// Set up physics world
	hkpWorldCinfo info;
	info.m_useKdTree = true;
	m_world = new hkpWorld(info);
	m_world->lock();
	hkpAgentRegisterUtil::registerAllAgents(m_world->getCollisionDispatcher());
	createPlatformAndBox(m_world, hkVector4(5.f, 0.f, 4.f), HK_NULL, &m_smokeBox);
	createPlatformAndBox(m_world, hkVector4(5.f, 0.f, 0.f));
	createPlatformAndBox(m_world, hkVector4(5.f, 0.f, -4.f));
	hkpRigidBody* sparksPlatform;
	createPlatformAndBox(m_world, hkVector4(5.f, 0.f, -8.f), &sparksPlatform, &m_sparksBox);
	m_sparksListener = new ScrapeParticleListener(SPARKS_EMIT_PROPERTY_KEY, 2.f);
	sparksPlatform->addProperty(SPARKS_EMIT_PROPERTY_KEY, 0);
	sparksPlatform->removeReference();
	m_sparksBox->addProperty(SPARKS_EMIT_PROPERTY_KEY, 0);
	m_sparksBox->addCollisionListener(m_sparksListener);
	m_world->unlock();

	// Set up graphics
	setupGraphics();
	m_env->m_displayWorld->setAlphaDepthSortEnabled(false);
	const float color[3] = { 0.25f, 0.25f, 0.5f };
	env->m_window->setClearColor(color);

	// Set up camera
	hkVector4 from(14.04f, 5.18f, 10.36f);
	hkVector4 to(6.05f, 1.15f, 1.31f);
	hkVector4 up(0.f, 1.f, 0.f);
	setupDefaultCameras(env, from, to, up);

	// Smoke
	{
		// Create a material which will be shared by Smoke1 and Smoke2
		hkgMaterial* material = createParticleMaterial( m_env, "renderparticle", "smoke_4x1.png",
			"smoke_particle_vp", "smoke_particle_gs", "smoke_particle_fp", smokeVertexShaderBindCallback );
		m_smokeParticleSystem1 = new HkgSmokeParticleSystem(94731, m_env, material, 500);
		m_smokeParticleSystem1->m_windVelocity.set(0.f, 0.f, 5.f);
		m_smokeParticleSystem2 = new HkgSmokeParticleSystem(38366, m_env, material, 500);
		material->release();
	}

	// Debris1
	{
		hkgMaterial* material = createParticleMaterial( m_env, "renderparticle", "debris_4x2.png",
			"debris_particle_vp", "debris_particle_gs", "debris_particle_fp", debrisVertexShaderBindCallback );
		m_debrisParticleSystem1 = new HkgDebrisParticleSystem( 92974, HkgDebrisParticleSystem::ENABLE_COLLISIONS,
			m_world, m_env, material, 2000 );
		m_debrisParticleSystem1->m_depthSortEnabled = true;
		material->release();
	}

	// Debris2
	{
		hkgMaterial* material = createParticleMaterial( m_env, "renderparticle", "rocks_4x2.png",
			"debris_particle_vp", "debris_particle_gs", "debris_particle_fp", debrisVertexShaderBindCallback );
		m_debrisParticleSystem2 = new HkgDebrisParticleSystem( 48094, HkgDebrisParticleSystem::ENABLE_COLLISIONS |
			HkgDebrisParticleSystem::ENABLE_FRACTURES, m_world, m_env, material, 6000 );
		m_debrisParticleSystem2->m_sizeThreshold = 0.025f/12;
		m_debrisParticleSystem2->m_relativeSpeedThreshold = 3.f;
		m_debrisParticleSystem2->m_fractureProbability = 0.6f;
		m_debrisParticleSystem2->m_depthSortEnabled = true;
		material->release();
	}

	// Sparks
	{
		hkgMaterial* material = createParticleMaterial( m_env, "renderparticle", "spark.png",
			"sparks_particle_vp", "sparks_particle_gs", "sparks_particle_fp", sparkVertexShaderBindCallback );
		m_sparksParticleSystem = new HkgSparksParticleSystem( 23482, HkgSparksParticleSystem::ENABLE_COLLISIONS,
			m_world, m_env, material, 1000 );
		material->release();
	}

	// Dust
	{
		hkgMaterial* material = createParticleMaterial( m_env, "renderparticle", "dust_4x1.png",
			"dust_particle_vp", "dust_particle_gs", "dust_particle_fp", dustVertexShaderBindCallback );
		m_dustParticleSystem = new HkgDustParticleSystem(38473, m_env, material, 1000);
		m_dustParticleSystem->m_depthSortEnabled = true;
		material->release();
	}

	// Explosion
	{
		hkgMaterial* material = createParticleMaterial( m_env, "renderparticle", "explosion_4x1.png", "dusty_explosion_particle_vp",
			"explosion_particle_gs", "explosion_particle_fp", explosionVertexShaderBindCallback );
		m_explosionParticleSystem = new HkgExplosionParticleSystem(79836, m_env, material, 1000);
		material->release();
	}

	bindKeyPressed('R', "Reset particles", KeyPressCallback::Method(&ParticlesTestDemo::resetParticles, this) );
	bindKeyPressed('4', "Dust emission at mouse", KeyPressCallback::BoundMethod(&ParticlesTestDemo::emissionAtMouse, this, hkBool32(true)) );
	bindKeyPressed('5', "Explosion emission at mouse", KeyPressCallback::BoundMethod(&ParticlesTestDemo::emissionAtMouse, this, hkBool32(false)) );
}

ParticlesTestDemo::~ParticlesTestDemo()
{
	m_world->lock();
	m_smokeBox->removeReference();
	m_sparksBox->removeCollisionListener(m_sparksListener);
	m_sparksBox->removeReference();
	m_sparksListener->removeReference();
	m_world->unlock();

	m_smokeParticleSystem1->removeReference();
	m_smokeParticleSystem2->removeReference();
	m_debrisParticleSystem1->removeReference();
	m_debrisParticleSystem2->removeReference();
	m_sparksParticleSystem->removeReference();
	m_dustParticleSystem->removeReference();
	m_explosionParticleSystem->removeReference();
}

int ParticlesTestDemo::resetParticles()
{
	m_smokeParticleSystem1->clear();
	m_smokeParticleSystem2->clear();
	m_debrisParticleSystem1->clear();
	m_debrisParticleSystem2->clear();
	m_sparksParticleSystem->clear();
	m_dustParticleSystem->clear();
	m_explosionParticleSystem->clear();
	return 0;
}

// Dust and explosions
int ParticlesTestDemo::emissionAtMouse(hkBool32 isDust)
{
	const hkgMouse& mouse = m_env->m_window->getMouse();
	hkgViewport* vp = m_env->m_window->getCurrentViewport();
	hkgViewportPickData vpd;
	if(vp->pick(mouse.getPosX(), mouse.getPosY(), m_env->m_displayWorld, vpd))
	{
		hkVector4 position;
		position.load3(vpd.m_worldPos);

		// Compute the normal of the vertical plane which goes through the camera position and the
		// emit position. The sign of this normal dotted with the emitted particle's velocity will
		// determine whether the particle should spin clockwise or counterclockwise.
		hkgCamera* camera = m_env->m_window->getCurrentViewport()->getCamera();
		hkVector4 cameraPosition, planeNormal;
		cameraPosition.load4(camera->getFromPtr());
		planeNormal.setSub4(cameraPosition, position);
		planeNormal.set(-planeNormal(2), 0.f, planeNormal(0));

		if(isDust)
		{
			// Dust emission
			DustParticleSystem::EmitParams params;
			params.m_emitPosition = position;
			params.m_emitDirection.set(0.f, 1.f, 0.f);
			params.m_planeNormal = planeNormal;
			hkReal scale = hkMath::randRange(0.5f, 1.5f);
			params.m_speedScale = scale;
			m_dustParticleSystem->emit(hkMath::hkFloorToInt(scale*120.f), m_timestep, &params);
		}
		else
		{
			// Explosion emission
			HkgExplosionParticleSystem::HkgEmitParams params;
			params.m_position = position;
			params.m_planeNormal = planeNormal;
			const hkReal scale = 0.5f;
			params.m_minSpeed *= scale;
			params.m_maxSpeed *= scale;
			params.m_minSize *= scale;
			params.m_maxSize *= scale;
			params.m_minSpriteIndex = 0;
			params.m_maxSpriteIndex = 2;
			m_explosionParticleSystem->emit(50, m_timestep, &params);
		}
	}
	return 0;
}

hkDemo::Result ParticlesTestDemo::stepDemo()
{
	hkDemo::Result res = hkDefaultPhysicsDemo::stepDemo();

	HK_ASSERT(0x5af75c66, m_world->m_kdTreeManager->isUpToDate());

	// Smoke
	{
		// Smoke1 emission
		m_smokeChimneyEmissionUtil1.update(m_timestep);
		HkgSmokeParticleSystem::HkgEmitParams params;
		params.m_emitPosition = m_smokeChimneyEmissionUtil1.getPosition();
		params.m_emitDirection = m_smokeChimneyEmissionUtil1.getDirection();
		params.m_minSpriteIndex = 0;
		params.m_maxSpriteIndex = 3;
		int numParticlesToEmit = m_smokeContinuousEmissionUtil.update(m_timestep);
		m_smokeParticleSystem1->emit(numParticlesToEmit, m_timestep, &params);

		// Smoke2 emission
		hkVector4 localAttachmentPoint(0.f, 0.4f, 0.f);
		m_smokeChimneyEmissionUtil2.update(m_timestep, m_smokeBox->getTransform(), localAttachmentPoint);
		params.m_emitPosition = m_smokeChimneyEmissionUtil2.getPosition();
		params.m_emitDirection = m_smokeChimneyEmissionUtil2.getDirection();
		const hkReal scale = 0.5f;
		params.m_minSpeed *= scale;
		params.m_maxSpeed *= scale;
		params.m_minSize *= scale;
		params.m_maxSize *= scale;
		m_smokeParticleSystem2->emit(numParticlesToEmit, m_timestep, &params);
	}

	// Debris
	{
		// Debris1 emission
		HkgDebrisParticleSystem::HkgEmitParams params;
		hkVector4 direction(3.f, 1.f, 0.f);
		hkReal speed = direction.normalizeWithLength3();
		DiskEmissionUtil deu(hkVector4(0.f, 4.f, 0.f), 0.1f, 0.f, 0.f, direction, HK_REAL_PI/25.f);
		params.m_diskEmissionUtil = &deu;
		params.m_minSpeed = speed;
		params.m_maxSpeed = speed;
		params.m_minSpinRate = -HK_REAL_PI*10.f;
		params.m_maxSpinRate = HK_REAL_PI*10.f;
		params.m_minLifeTime = 3.f;
		params.m_maxLifeTime = 7.f;
		params.m_minSize = 0.18f;
		params.m_maxSize = 0.2f;
		params.m_minSpriteIndex = 0;
		params.m_maxSpriteIndex = 7;
		int numParticlesToEmit = m_debrisContinuousEmissionUtil.update(m_timestep);
		m_debrisParticleSystem1->emit(numParticlesToEmit, m_timestep, &params);

		// Debris2 emission
		DiskEmissionUtil deu2(hkVector4(0.f, 4.f, -4.f), 0.1f, 0.f, 0.f, direction, HK_REAL_PI/25.f);
		params.m_diskEmissionUtil = &deu2;
		params.m_minSpinRate = -HK_REAL_PI*5.f;
		params.m_maxSpinRate = HK_REAL_PI*5.f;
		params.m_minSpriteIndex = 0;
		params.m_maxSpriteIndex = 3;
		m_debrisParticleSystem2->emit(numParticlesToEmit, m_timestep, &params);
	}

	// Sparks
	{
		// Continuous emission
		SparksParticleSystem::EmitParams params;
		hkVector4 direction(0.f, 5.f, 0.f);
		hkReal speed = direction.normalizeWithLength3();
		DiskEmissionUtil deu(hkVector4(3.5f, 0.5f, -8.f), 0.f, 0.f, 0.f, direction, HK_REAL_PI/10.f);
		params.m_diskEmissionUtil = &deu;
		params.m_minSpeed = speed * 0.97f;
		params.m_maxSpeed = speed * 1.03f;
		int numParticlesToEmit = m_sparksContinuousEmissionUtil.update(m_timestep);
		m_sparksParticleSystem->emit(numParticlesToEmit, m_timestep, &params);

		// Emission based on collision listener
		hkArray<ScrapeParticleListener::ContactInfo>& contacts = m_sparksListener->getContacts();
		for(int i = 0; i < contacts.getSize(); ++i)
		{
			DiskEmissionUtil deutil(contacts[i].m_position, 0.f, 0.f, 0.f, contacts[i].m_direction, HK_REAL_PI/3.f);
			params.m_diskEmissionUtil = &deutil;
			hkReal scale = hkMath::sqrt(contacts[i].m_relativeSpeed);	// the sqrt prevents high particle counts
			params.m_minSpeed = scale * 0.95f;
			params.m_maxSpeed = scale * 1.05f;
			params.m_minLifeTime *= scale * 0.06f;
			params.m_maxLifeTime *= scale * 0.06f;
			int numParsToEmit = hkMath::hkFloorToInt(scale*4.f);
			m_sparksParticleSystem->emit(numParsToEmit, m_timestep, &params);
		}
		contacts.clear();
	}

	

	// Update particle systems
	HK_TIMER_BEGIN_LIST("Particle Update", "Smoke1");
	m_smokeParticleSystem1->update(m_timestep);
	HK_TIMER_SPLIT_LIST("Smoke2");
	m_smokeParticleSystem2->update(m_timestep);
	HK_TIMER_SPLIT_LIST("Debris1");
	m_debrisParticleSystem1->update(m_timestep);
	HK_TIMER_SPLIT_LIST("Debris2");
	m_debrisParticleSystem2->update(m_timestep);
	HK_TIMER_SPLIT_LIST("Sparks");
	m_sparksParticleSystem->update(m_timestep);
	HK_TIMER_SPLIT_LIST("Dust");
	m_dustParticleSystem->update(m_timestep);
	HK_TIMER_SPLIT_LIST("Explosion");
	m_explosionParticleSystem->update(m_timestep);
	HK_TIMER_END_LIST();

	// Draw particle systems
	HK_TIMER_BEGIN_LIST("Particle Draw", "Smoke1");
	m_smokeParticleSystem1->draw();
	HK_TIMER_SPLIT_LIST("Smoke2");
	m_smokeParticleSystem2->draw();
	HK_TIMER_SPLIT_LIST("Debris1");
	m_debrisParticleSystem1->draw();
	HK_TIMER_SPLIT_LIST("Debris2");
	m_debrisParticleSystem2->draw();
	HK_TIMER_SPLIT_LIST("Sparks");
	m_sparksParticleSystem->draw();
	HK_TIMER_SPLIT_LIST("Dust");
	m_dustParticleSystem->draw();
	HK_TIMER_SPLIT_LIST("Explosion");
	m_explosionParticleSystem->draw();
	HK_TIMER_END_LIST();

	// Print out the number of particles in each particle system
	const int numLines = 8;
	char text[32*numLines];
	hkString::sprintf( text, "Particle Counts\nSmoke1: %d\nSmoke2: %d\nDebris1: %d\nDebris2: %d\nSparks %d\nDust: %d\nExplosion: %d",
		m_smokeParticleSystem1->getNumParticles(), m_smokeParticleSystem2->getNumParticles(), m_debrisParticleSystem1->getNumParticles(),
		m_debrisParticleSystem2->getNumParticles(), m_sparksParticleSystem->getNumParticles(), m_dustParticleSystem->getNumParticles(),
		m_explosionParticleSystem->getNumParticles() );
	float x = 20.f;
	float y = m_env->m_window->getHeight() - 20.f - numLines*m_env->m_textDisplay->getFont()->getCharHeight();
	m_env->m_textDisplay->outputText(text, x, y, 0xffffffff, 1, 0);

	return res;
}


#if defined(HK_COMPILER_MWERKS)
#	pragma force_active on
#	pragma fullpath_file on
#endif

static const char helpString[] =
	"Particles Demo\n"\
	"Press '4'/'5' while cursor is over an object to trigger a dust puff/explosion.\n"\
	"Drag the box next to the sparks emitter to create contact sparks.";

HK_DECLARE_DEMO(ParticlesTestDemo, HK_DEMO_TYPE_PRIME , "Simple particles demo", helpString);


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
