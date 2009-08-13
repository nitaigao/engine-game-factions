/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IWorldSerializer.hpp
*  @date   2009/04/27
*/
#pragma once
#ifndef IWORLDLOADER_HPP
#define IWORLDLOADER_HPP

#include "../IWorldEntity.hpp"

namespace Serialization
{
	/*!
	 *  De serializes a world from storage 
	 */
	class IWorldSerializer
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~IWorldSerializer( ) { };


		/*! De serializes the Level File into the component collection
		 *
		 * @param[in] const std::string & levelPath
		 * @param[in] IWorldEntity::WorldEntityMap & entities
		 * @return ( void )
		 */
		virtual void DeSerializeLevel( const std::string& levelPath ) = 0;


		/*! De serializes an entity file into the given entity
		 *
		 * @param[in] IWorldEntity *
		 * @param[in] const std::string & filepath
		 * @return ( void )
		 */
		virtual void DeSerializeEntity( State::IWorldEntity* entity, const std::string& filepath ) = 0;


		/*! Steps the loading process
		 *
		 *  @param[in] float deltaMilliseconds
		 *  @return (void)
		 */
		virtual void Update( float deltaMilliseconds ) = 0;
	};
};

#endif
