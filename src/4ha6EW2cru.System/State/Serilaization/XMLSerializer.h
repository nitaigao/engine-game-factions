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

#include "../../Export.hpp"

#include "IWorldLoader.hpp"
#include "../IWorld.hpp"
#include "../IWorldEntity.hpp"

#include <ticpp.h>

#include "../../Service/IService.hpp"

namespace Serialization
{
	/*!
	 *  De serializes a world from storage  
	 */
	class XMLSerializer : public IWorldSerializer, public Services::IService
	{
		typedef std::queue< ticpp::Node* > NodePtrList;
		typedef std::map< System::Types::Type, ticpp::Node* > NodePtrMap;

	public:

		/*! Default Destructor
		*
		*  @return ()
		*/
		GAMEAPI ~XMLSerializer( );


		/*! Default Constructor
		 *
		 *  @param[in] IWorld * world
		 *  @return ()
		 */
		XMLSerializer( State::IWorld* world )
			: m_world( world )
			, m_loadTotal( 0 )
			, m_loadProgress( 0 )
		{

		}

		/*! Loads a Serialized world from the File System
		*
		*  @param[in] const std::string & levelPath
		*  @return (void)
		*/
		GAMEAPI void Load( const std::string& levelPath );


		/*! Steps the loading process
		*
		*  @param[in] float deltaMilliseconds
		*  @return (void)
		*/
		GAMEAPI void Update( const float& deltaMilliseconds );


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
		GAMEAPI AnyType::AnyTypeMap Message( const System::Message& message, AnyType::AnyTypeMap parameters );

	private:

		XMLSerializer( ) { };
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

		State::IWorld* m_world;

		NodePtrList m_loadQueueEl;

		int m_loadProgress;
		int m_loadTotal;

	};
};

#endif