/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   World.h
*  @date   2009/04/27
*/
#pragma once
#ifndef WORLD_H
#define WORLD_H

#include "IWorld.hpp"
#include "IWorldEntityFactory.hpp"
#include "IEntityService.hpp"

#include "Serilaization/IWorldLoader.hpp"
#include "../Service/IServiceManager.h"

namespace State
{
	/*!
	 *  The Container for all Entities 
	 */
	class GAMEAPI World : public IWorld
	{

	public:

		/*! Default Destructor
		*
		*  @return ()
		*/
		~World( );


		/*! Default Constructor
		 *
		 * @param[in] Serialization::IWorldSerializer * serializer
		 * @param[in] IWorldEntityFactory * entityFactory
		 * @param[in] IEntityService * entityService
		 * @param[in] Services::IServiceManager * serviceManager
		 * @return (  )
		 */
		World( Serialization::IWorldSerializer* serializer, IWorldEntityFactory* entityFactory, Services::IServiceManager* serviceManager )
			: m_serializer( serializer )
			, m_entityFactory( entityFactory )
			, m_serviceManager( serviceManager )
		{

		}


		/*! Creates a World Entity Container
		*
		*  @param[in] const std::string & name
		*  @return (IWorldEntity*)
		*/
		IWorldEntity* CreateEntity( const std::string& name );


		/*! Loads an Entity from the given file path
		*
		* @param[in] const std::string & name
		* @param[in] const std::string & filePath
		* @return ( IWorldEntity& )
		*/
		IWorldEntity* CreateEntity( const std::string& name, const std::string& filePath, const std::string& entityType );


		/*! Creates a World Entity Container
		*
		*  @param[in] const std::string & name
		*  @return (IWorldEntity*)
		*/
		void DestroyEntity( const std::string& name );


		/*! Adds a System Scene to the internal scene list
		*
		*  @param[in] ISystemScene * systemScene
		*  @return (void)
		*/
		inline void AddSystemScene( ISystemScene* systemScene ) { m_systemScenes.insert( std::make_pair( systemScene->GetType( ), systemScene ) ); }
		
		
		/*! Gets a list of internal system scenes
		*
		*  @return (const SystemSceneMap&)
		*/
		inline const ISystemScene::SystemSceneMap& GetSystemScenes( ) const { return m_systemScenes; };


		/*! Destroys all entities within the world
		*
		*  @return (void)
		*/
		void Clear( );


		/*! Destroys the World and All Registered Scenes
		*
		* @return ( void )
		*/
		void Destroy( );


		/*! Updates the world and all of its internal data structures
		*
		* @param[in] float deltaMilliseconds
		* @return ( void )
		*/
		void Update( float deltaMilliseconds );


		/*! Loads a level from the file system
		*
		* @param[in] const std::string & levelpath
		* @return ( void )
		*/
		void LoadLevel( const std::string& levelpath );


		/*! Serializes the contents of the world to the Stream
		*
		* @param[in] IO::IStream * stream
		* @return ( void )
		*/
		void Serialize( IO::IStream* stream );


		/*! De serializes the contents of the stream into the World
		*
		* @param[in] IO::IStream * stream
		* @return ( void )
		*/
		void DeSerialize( IO::IStream* stream );

	private:

		World( const World & copy ) { };
		World & operator = ( const World & copy ) { return *this; };

		std::string m_name;

		Services::IServiceManager* m_serviceManager;
		IWorldEntity::WorldEntityMap m_entities;
		ISystemScene::SystemSceneMap m_systemScenes;

		Serialization::IWorldSerializer* m_serializer;
		IWorldEntityFactory* m_entityFactory;

		unsigned int m_lastEntityId;
	};
};

#endif
