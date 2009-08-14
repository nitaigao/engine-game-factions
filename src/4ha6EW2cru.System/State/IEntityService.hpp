/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IEntityService.hpp
*  @date   2009/08/14
*/
#pragma once
#ifndef IENTITYSERVICE_HPP
#define IENTITYSERVICE_HPP

#include "../Service/IService.hpp"

namespace State
{
	/*! 
	 *  A Service to the Entity System
	 */
	class IEntityService : public Services::IService
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~IEntityService( ) { };
		
	};
};

#endif