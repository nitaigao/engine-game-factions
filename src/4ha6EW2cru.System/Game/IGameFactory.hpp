/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IGameFactory.hpp
*  @date   2009/11/24
*/
#pragma once
#ifndef IGAMEFACTORY_HPP
#define IGAMEFACTORY_HPP

#include "IGame.hpp"

namespace Game
{
	/*! 
	 *  Create Game Instances
	 */
	class IGameFactory
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~IGameFactory() { };


		/*! Creates a Game System
		 *
		 * @return (IGame*)
		 */
		virtual IGame* CreateGame() const = 0;
		
	};
};

#endif