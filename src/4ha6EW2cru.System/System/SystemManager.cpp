#include "precompiled.h"
#include "SystemManager.h"

using namespace State;
using namespace Configuration;

#include "../Logging/Logger.h"
using namespace Logging;

#include "SystemExports.hpp"
#include "../Exceptions/FileNotFoundException.hpp"

#include "../State/Serilaization/XMLSerializer.h"
using namespace Serialization;

#include "../State/WorldEntityFactory.h"
using namespace State;

void SystemManager::RegisterSystem( const System::Queues::Queue& systemQueue, ISystem* system )
{
	_systemsByQueue.insert( std::make_pair( systemQueue, system ) );
	_systemsByType.insert( std::make_pair( system->GetType( ), system ) );
}

ISystem* SystemManager::GetSystem( const System::Types::Type& systemType ) const
{
	return ( *( _systemsByType.find( systemType ) ) ).second;
}

void SystemManager::InitializeAllSystems( )
{
	for( ISystem::SystemTypeMap::iterator i = _systemsByType.begin( ); i != _systemsByType.end( ); ++i )
	{
		( *i ).second->Initialize( m_configuration );
	}
}

void SystemManager::Update( float deltaMilliseconds )
{
	m_instrumentation->SetFPS( 1.0f / deltaMilliseconds );

	int loopCount = 0;
	int maxLoops = 10;

	float step = 1.0f / 100.0f;
	m_accumulator += deltaMilliseconds;

	float logicStart = m_platformManager->GetClock( )->GetTime( );

	while( m_accumulator >= deltaMilliseconds && loopCount < maxLoops )
	{
		for( ISystem::SystemQueueMap::iterator i = _systemsByQueue.begin( ); i != _systemsByQueue.end( ); ++i )
		{
			if ( ( *i ).first == System::Queues::LOGIC )
			{
				( *i ).second->Update( step );
			}
		}

		m_accumulator -= step;
		loopCount++;
	}

	float logicEnd = m_platformManager->GetClock( )->GetTime( );

	m_instrumentation->SetRoundTime( System::Queues::LOGIC, logicEnd - logicStart );

	float houseKeepingStart = m_platformManager->GetClock( )->GetTime( );

	for( ISystem::SystemQueueMap::iterator i = _systemsByQueue.begin( ); i != _systemsByQueue.end( ); ++i )
	{
		if ( ( *i ).first == System::Queues::HOUSE )
		{
			( *i ).second->Update( deltaMilliseconds );
		}
	}

	float houseKeepingEnd = m_platformManager->GetClock( )->GetTime( );

	m_instrumentation->SetRoundTime( System::Queues::HOUSE, houseKeepingEnd - houseKeepingStart );

	float presentationStart = m_platformManager->GetClock( )->GetTime( );

	for( ISystem::SystemQueueMap::iterator i = _systemsByQueue.begin( ); i != _systemsByQueue.end( ); ++i )
	{
		if ( ( *i ).first == System::Queues::RENDER )
		{
			( *i ).second->Update( deltaMilliseconds );
		}
	}

	float presentationEnd = m_platformManager->GetClock( )->GetTime( );

	m_instrumentation->SetRoundTime( System::Queues::RENDER, presentationEnd - presentationStart );
}

void SystemManager::Release( )
{
	for( ISystem::SystemTypeMap::const_reverse_iterator i = _systemsByType.rbegin( ); i != _systemsByType.rend( ); ++i )
	{
		( *i ).second->Release( );

		HMODULE library = m_systemLibraries[ ( *i ).second ];

		DestroySystemFunction destroySystem = reinterpret_cast< DestroySystemFunction >( GetProcAddress( library, "DestroySystem" ) );
		destroySystem( ( *i ).second );
	}

	_systemsByType.clear( );
	_systemsByQueue.clear( );

	m_systemLibraries.clear( );
}

IWorld* SystemManager::CreateWorld()
{
	Serialization::IWorldSerializer* serializer = new XMLSerializer( m_eventManager, m_resourceCache, this, m_serviceManager );
	IWorldEntityFactory* factory = new WorldEntityFactory( );
	
	World* world = new World( serializer, factory, m_serviceManager );
	m_serviceManager->RegisterService( world );

	for( ISystem::SystemTypeMap::iterator i = _systemsByType.begin( ); i != _systemsByType.end( ); ++i )
	{
		world->AddSystemScene( ( *i ).second->CreateScene( ) );
	}

	return world;
}

bool SystemManager::HasSystem( const System::Types::Type& systemType ) const
{
	return ( _systemsByType.find( systemType ) != _systemsByType.end( ) );
}

ISystem* SystemManager::LoadSystem( const std::string& systemPath )
{
	HMODULE library = LoadLibrary( systemPath.c_str( ) );

	if ( library == NULL )
	{
		DWORD error = GetLastError( );

		FileNotFoundException e( "SystemManager::LoadSystem - Unable to load the given System dll" );
		Fatal( e.what( ) );
		throw e;
	}

	InitializeSystemFunction initializeSystem = reinterpret_cast< InitializeSystemFunction >( GetProcAddress( library, "Initialize" ) );
	initializeSystem( Logger::Get( ) );

	CreateSystemFunction createSystem = reinterpret_cast< CreateSystemFunction >( GetProcAddress( library, "CreateSystem" ) );
	ISystem* system = createSystem( m_configuration, m_serviceManager, m_resourceCache, m_eventManager, m_instrumentation, m_platformManager );

	m_systemLibraries.insert( std::make_pair( system, library ) );

	return system;
}

void SystemManager::LoadSystems( bool isDedicated )
{
	ISystem* geometrySystem = this->LoadSystem( "4ha6EW2cru.Geometry.dll" );
	this->RegisterSystem( System::Queues::HOUSE, geometrySystem );

	ISystem* scriptSystem = this->LoadSystem( "4ha6EW2cru.Script.dll" );
	this->RegisterSystem( System::Queues::HOUSE, scriptSystem );

	ISystem* networkSystem = this->LoadSystem( "4ha6EW2cru.Network.dll" );
	this->RegisterSystem( System::Queues::HOUSE, networkSystem );


	ISystem* physicsSystem = this->LoadSystem( "4ha6EW2cru.Physics.dll" );
	this->RegisterSystem( System::Queues::LOGIC, physicsSystem );

	//ISystem* aiSystem = this->LoadSystem( "4ha6EW2cru.AI.dll" );
	//this->RegisterSystem( System::Queues::HOUSE, aiSystem );

	if ( !isDedicated )
	{
		ISystem* rendererSystem = this->LoadSystem( "4ha6EW2cru.Renderer.dll" );
		this->RegisterSystem( System::Queues::HOUSE, rendererSystem );

		ISystem* animationSystem = this->LoadSystem( "4ha6EW2cru.Animation.dll" );
		this->RegisterSystem( System::Queues::HOUSE, animationSystem );

		ISystem* inputSystem = this->LoadSystem( "4ha6EW2cru.Input.dll" );
		this->RegisterSystem( System::Queues::HOUSE, inputSystem );

		ISystem* uxSystem = this->LoadSystem( "4ha6EW2cru.UX.dll" );
		this->RegisterSystem( System::Queues::HOUSE, uxSystem );

		ISystem* soundSystem = this->LoadSystem( "4ha6EW2cru.Sound.dll" );
		this->RegisterSystem( System::Queues::HOUSE, soundSystem );
	}
	else
	{		
		networkSystem->SetAttribute( System::Attributes::Network::IsServer, true );
		m_platformManager->CreateConsoleWindow( );
	}
}