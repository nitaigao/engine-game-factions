/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IWorldEntityFactory.hpp
*  @date   2009/08/13
*/
#pragma once
#ifndef IWORLDENTITYFACTORY_HPP
#define IWORLDENTITYFACTORY_HPP

#include "IWorldEntity.hpp"

namespace State
{
	/*! 
	 *  A factory that created Entities
	 */
	class IWorldEntityFactory
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~IWorldEntityFactory() { };


		/*! Creates an Entity
		 *
		 * @param[in] const std::string & name
		 * @return (IWorldEntity*)
		 */
		virtual IWorldEntity* CreateEntity(const std::string& name) const = 0;
		
	};
};

#endif