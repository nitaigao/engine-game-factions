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
#include "Service/IServiceManager.h"
#include "IO/IResourceCache.hpp"

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
		SoundFactory( Services::IServiceManager* serviceManager, Resources::IResourceCache* resourceCache )
			: m_serviceManager( serviceManager )
			, m_resourceCache( resourceCache )
		{

		}


		/*! Creates a SoundSystem Object
		*
		* @return ( ISoundSystem* )
		*/
		ISoundSystem* CreateSoundSystem( );

	private:

		SoundFactory( const SoundFactory & copy ) { };
		SoundFactory & operator = ( const SoundFactory & copy ) { return *this; };

		Services::IServiceManager* m_serviceManager;
		Resources::IResourceCache* m_resourceCache;
		
	};
};

#endif