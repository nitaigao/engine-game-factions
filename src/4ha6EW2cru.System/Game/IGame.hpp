/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IGame.hpp
*  @date   2009/11/24
*/
#pragma once
#ifndef IGAME_HPP
#define IGAME_HPP

#include "../Export.hpp"

namespace Game
{
	/*! 
	 *  Root of the Game Engine
	 */
	class GAMEAPI IGame
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~IGame( ) { };


		/*! Initializes the GameRoot
		*
		*  @return (void)
		*/
		virtual void Initialize( ) = 0;


		/*! Steps the GameRoot forward
		*
		*  @param[in] float deltaMilliseconds
		*  @return (void)
		*/
		virtual void Update( ) = 0;


		/*! Releases the GameRoot
		*
		*  @return (void)
		*/
		virtual void Release( ) = 0;


		/*! Returns whether or not the GameRoot is ready to Quit
		*
		*  @return (bool)
		*/
		virtual bool IsQuitting( ) const = 0;
		
	};
};

#endif