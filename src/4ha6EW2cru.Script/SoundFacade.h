/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   SoundFacade.h
*  @date   2009/04/28
*/
#pragma once
#ifndef SOUNDFACADE_H
#define SOUNDFACADE_H

#include "ISoundFacade.hpp"
#include "IScriptComponent.hpp"

#include <luabind/luabind.hpp>
#include "Service/IServiceManager.h"

namespace Script
{
	/*!
	 *  An Interface to the Sound System for Script  
	 */
	class SoundFacade : public ISoundFacade
	{

	public:

		/*! Registers the Script functions with the given state
		*
		* @return ( void )
		*/
		static luabind::scope RegisterFunctions( );

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~SoundFacade( ) { };


		/*! Default Constructor
		 *
		 *  @return ()
		 */
		SoundFacade( ISystemComponent* component, Services::IServiceManager* serviceManager )
			: m_component( component )
			, m_serviceManager( serviceManager )
		{

		}

		/*! Returns the Name that the Facade will use in script
		*
		* @return ( std::string )
		*/
		inline std::string GetName( ) { return "sound"; };


		void TriggerEvent( const std::string& eventPath );

		void KeyOutEvent( const std::string& eventPath );

		/*! Instructs the Sound System to play some music from the given event path
		*
		*  @param[in] const std::string & eventPath
		*  @return (void)
		*/
		void PlayMusic( const std::string& eventPath );


		/*! Initializes the Facade with the given ScriptComponent
		*
		* @return ( void )
		*/
		void Initialize( ) { };

	private:

		SoundFacade( const SoundFacade & copy ) { };
		SoundFacade & operator = ( const SoundFacade & copy ) { return *this; };

		ISystemComponent* m_component;
		Services::IServiceManager* m_serviceManager;
	};
};

#endif
