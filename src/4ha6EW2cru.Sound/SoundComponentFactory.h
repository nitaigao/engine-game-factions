/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   SoundComponentFactory.h
*  @date   2009/08/26
*/
#pragma once
#ifndef SOUNDCOMPONENTFACTORY_H
#define SOUNDCOMPONENTFACTORY_H

#include "ISoundComponentFactory.hpp"
#include "ISoundEventSystem.hpp"

namespace Sound
{
	/*! 
	 *  Creates Sound Components
	 */
	class GAMEAPI SoundComponentFactory : public ISoundComponentFactory
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~SoundComponentFactory( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		SoundComponentFactory( ISoundEventSystem* eventSystem )
			: m_eventSystem( eventSystem )
		{

		}


		/*! Creates a SoundSystem Component
		*
		* @param[in] const std::string & name
		* @param[in] const std::string & type
		* @return ( ISoundSystemComponent* )
		*/
		ISoundSystemComponent* CreateComponent( const std::string& name, const std::string& type );

	private:

		SoundComponentFactory( const SoundComponentFactory & copy ) { };
		SoundComponentFactory & operator = ( const SoundComponentFactory & copy ) { return *this; };

		ISoundEventSystem* m_eventSystem;
		
	};
};

#endif