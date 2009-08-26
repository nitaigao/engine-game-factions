/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   SoundFactory.h
*  @date   2009/08/26
*/
#pragma once
#ifndef SOUNDFACTORY_H
#define SOUNDFACTORY_H

#include "ISoundFactory.hpp"

namespace Sound
{
	/*! 
	 *  A Factory to Create the Sound System Object Graph
	 */
	class SoundFactory : public ISoundFactory
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~SoundFactory( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		SoundFactory( ) { };


		/*! Creates a SoundSystem Object
		*
		* @return ( ISoundSystem* )
		*/
		ISoundSystem* CreateSoundSystem( );

	private:

		SoundFactory( const SoundFactory & copy ) { };
		SoundFactory & operator = ( const SoundFactory & copy ) { return *this; };
		
	};
};

#endif