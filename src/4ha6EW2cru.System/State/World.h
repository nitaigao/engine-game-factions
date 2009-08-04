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

#include "../Export.hpp"

namespace State
{
	/*!
	 *  The Container for all Entities 
	 */
	class World : public IWorld
	{

	public:

		/*! Default Destructor
		*
		*  @return ()
		*/
		GAMEAPI ~World( );


		/*! Default Constructor
		 *
		 *  @return ()
		 */
		GAMEAPI World( )
			: m_lastEntityId( 0 )
		{

		}


		/*! Creates a World Entity Container
		*
		*  @param[in] const std::string & name
		*  @return (IWorldEntity*)
		*/
		GAMEAPI IWorldEntity* CreateEntity( const std::string& name );


		/*! Creates a World Entity Container
		*
		*  @param[in] const std::string & name
		*  @return (IWorldEntity*)
		*/
		GAMEAPI void DestroyEntity( const std::string& name );


		/*! Adds a System Scene to the internal scene list
		*
		*  @param[in] ISystemScene * systemScene
		*  @return (void)
		*/
		GAMEAPI inline void AddSystemScene( ISystemScene* systemScene ) { m_systemScenes.insert( std::make_pair( systemScene->GetType( ), systemScene ) ); }
		
		
		/*! Gets a list of internal system scenes
		*
		*  @return (const SystemSceneMap&)
		*/
		GAMEAPI inline const ISystemScene::SystemSceneMap& GetSystemScenes( ) const { return m_systemScenes; };


		/*! Destroys all entities within the world
		*
		*  @return (void)
		*/
		GAMEAPI void Clear( );


		/*! Destroys the World and All Registered Scenes
		*
		* @return ( void )
		*/
		GAMEAPI void Destroy( );

	private:

		World( const World & copy ) { };
		World & operator = ( const World & copy ) { return *this; };

		std::string m_name;
		IWorldEntity::WorldEntityMap m_entities;
		ISystemScene::SystemSceneMap m_systemScenes;

		unsigned int m_lastEntityId;
	};
};

#endif
