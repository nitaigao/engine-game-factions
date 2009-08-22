/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   EntityService.h
*  @date   2009/08/14
*/
#pragma once
#ifndef ENTITYSERVICE_H
#define ENTITYSERVICE_H

#include "IEntityService.hpp"
#include "IWorld.hpp"

#include "../Export.hpp"

namespace State
{
	/*! 
	 *  A Service interface tot he Entity System
	 */
	class EntityService : public IEntityService
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~EntityService( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		EntityService( IWorld* world )
			: m_world( world )
		{

		}


		/*! Gets the System::Types::Type of the Service
		*
		*  @return (System::Types::Type)
		*/
		inline System::Types::Type GetType( ) const { return System::Types::ENTITY; };


		/*! Messages the system with a command
		*
		* @param[in] const std::string & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		GAMEAPI AnyType::AnyTypeMap ProcessMessage( const System::MessageType& message, AnyType::AnyTypeMap parameters );


	private:

		EntityService( ) { };
		EntityService( const EntityService & copy ) { };
		EntityService & operator = ( const EntityService & copy ) { return *this; };

		IWorld* m_world;
		
	};
};

#endif