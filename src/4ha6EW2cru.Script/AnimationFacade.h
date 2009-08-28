/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   AnimationFacade.h
*  @date   2009/06/03
*/
#pragma once
#ifndef ANIMATIONFACADE_H
#define ANIMATIONFACADE_H

#include "IAnimationFacade.h"
#include "System/ISystemComponent.hpp"

#include <luabind/luabind.hpp>

namespace Script
{
	/*! 
	 *  A Facade Interface to the Animation System
	 */
	class AnimationFacade : public IAnimationFacade
	{

	public:

		/*! Registers the Script functions with the given state
		*
		* @param[in] lua_State * state
		* @return ( void )
		*/
		static luabind::scope RegisterFunctions( );

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~AnimationFacade( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		AnimationFacade( ISystemComponent* component )
			: m_component( component )
		{

		}


		/*! Returns the Name that the Facade will use in script
		*
		* @return ( std::string )
		*/
		inline std::string GetName( ) { return "animation"; };


		/*! Instructs the Animation System to Start an Animation for the component
		*
		* @param[in] const std::string & animationName
		* @param[in] const bool & loop
		* @return ( void )
		*/
		void StartAnimation( const std::string& animationName, bool loop );


		/*! Instructs the Animation System to Stop an Animation for the component
		*
		* @param[in] const std::string & animationName
		* @return ( void )
		*/
		void StopAnimation( const std::string& animationName );


		/*! Initializes the Facade with the given ScriptComponent
		*
		* @return ( void )
		*/
		void Initialize( ) { };

	private:

		AnimationFacade( const AnimationFacade & copy ) { };
		AnimationFacade & operator = ( const AnimationFacade & copy ) { return *this; };
	
		ISystemComponent* m_component;
		
	};
};

#endif
