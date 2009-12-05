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
#include "../IWorld.hpp"

#include "../../Export.hpp"

namespace Serialization
{
	/*!
	 *  De serializes a world from storage 
	 */
	class GAMEAPI IWorldSerializer
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~IWorldSerializer( ) { };


		
		/*! De serializes the level path into the world
		 *
		 * @param[in] IWorld * world
		 * @param[in] const std::string & levelPath
		 * @return ( void )
		 */
		virtual void DeSerializeLevel( State::IWorld* world, const std::string& levelPath ) = 0;


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
