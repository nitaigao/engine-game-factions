/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   XMLSerializer.h
*  @date   2009/04/27
*/
#pragma once
#ifndef WORLDLOADER_H
#define WORLDLOADER_H

#include <queue>

#include "IWorldLoader.hpp"
#include "../IWorld.hpp"
#include "../IWorldEntity.hpp"

#include <ticpp.h>

#include "../../Service/IService.hpp"
#include "../../System/ISystemManager.hpp"
#include "../../Events/IEventManager.hpp"
#include "../../IO/IFileSystem.hpp"
#include "../../IO/IResourceCache.hpp"
#include "../../Service/IServiceManager.h"

namespace Serialization
{
	/*!
	 *  De serializes a world from storage  
	 */
	class GAMEAPI XMLSerializer : public IWorldSerializer, public Services::IService
	{
		typedef std::queue< ticpp::Node* > NodePtrList;
		typedef std::map< System::Types::Type, ticpp::Node* > NodePtrMap;

	public:

		/*! Default Destructor
		*
		*  @return ()
		*/
		~XMLSerializer( );


		/*! Default Constructor
		 *
		 * @param[in] Events::IEventManager * eventManager
		 * @param[in] Resources::IResourceCache * resourceCache
		 * @param[in] ISystemManager * systemManager
		 * @param[in] Services::IServiceManager * serviceManager
		 * @return (  )
		 */
		XMLSerializer( Events::IEventManager* eventManager, Resources::IResourceCache* resourceCache, 
			ISystemManager* systemManager, Services::IServiceManager* serviceManager )
			: m_eventManager( eventManager )
			, m_resourceCache( resourceCache )
			, m_systemManager( systemManager )
			, m_serviceManager( serviceManager )
			, m_loadTotal( 0 )
			, m_loadProgress( 0 )
		{

		}


		/*! De serializes the level path into the world
		*
		* @param[in] IWorld * world
		* @param[in] const std::string & levelPath
		* @return ( void )
		*/
		void DeSerializeLevel( State::IWorld* world, const std::string& levelPath );


		/*! De serializes an entity file into the given entity
		*
		* @param[in] IWorldEntity *
		* @param[in] const std::string & filepath
		* @return ( void )
		*/
		void DeSerializeEntity( State::IWorldEntity* entity, const std::string& filepath );


		/*! Steps the loading process
		*
		*  @param[in] float deltaMilliseconds
		*  @return (void)
		*/
		void Update( float deltaMilliseconds );


		/*! Returns whether or no the Serializer has finished its loading task
		*
		*  @return (bool)
		*/
		inline bool IsFinishedLoading( ) const { return ( m_loadProgress == m_loadTotal ); };


		/*! Gets the System::Types::Type of the Service
		*
		*  @return (System::Types::Type)
		*/
		inline System::Types::Type GetType( ) const { return System::Types::ENTITY; };


		/*! Executes a command on the Service
		*
		*  @param[in] const std::string & actionName
		*  @param[in] AnyType::AnyTypeMap & parameters
		*  @return (AnyType::AnyTypeMap)
		*/
		AnyType::AnyTypeMap ProcessMessage( const System::MessageType& message, AnyType::AnyTypeMap parameters ) { return AnyType::AnyTypeMap( ); };

	private:

		XMLSerializer( const XMLSerializer & copy ) { };
		XMLSerializer & operator = ( const XMLSerializer & copy ) { return *this; };

		void LoadElement( ticpp::Element* element );
		void DeserializeElement( ticpp::Element* element );

		void LoadColor( ticpp::Element* element );
		void LoadEntity( ticpp::Element* element );
		void LoadEntity( const std::string& name, const std::string& entityFilePath );
		void LoadEntityComponents( ticpp::Element* element, NodePtrMap& components );

		void ImportEntity( const std::string& src, NodePtrMap& components );

		State::IWorldEntity* CreateEntity( const std::string& name, NodePtrMap& components );
		void PopulateEntity( State::IWorldEntity* entity, NodePtrMap& components );

		NodePtrList m_loadQueueEl;

		int m_loadProgress;
		int m_loadTotal;

		State::IWorld* m_world;
		Events::IEventManager* m_eventManager;
		Resources::IResourceCache* m_resourceCache;
		ISystemManager* m_systemManager;
		Services::IServiceManager* m_serviceManager;

	};
};

#endif
