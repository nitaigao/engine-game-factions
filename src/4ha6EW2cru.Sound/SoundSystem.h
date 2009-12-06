/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   SoundSystem.h
*  @date   2009/04/27
*/
#pragma once
#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include "Service/IService.hpp"
#include "Service/IServiceManager.h"

#include "Configuration/IConfiguration.hpp"
#include "IO/IResourceCache.hpp"

#include "ISoundSystem.hpp"
#include "ISoundScene.hpp"
#include "ISoundEventSystem.hpp"

namespace Sound
{
	/*!
	 *  The Sound System 
	 */
	class GAMEAPI SoundSystem : public ISoundSystem, public Services::IService
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~SoundSystem( );


		/*! Default Constructor
		*
		*  @return ()
		*/
		SoundSystem( Services::IServiceManager* serviceManager, Resources::IResourceCache* resourceCache, ISoundScene* scene, ISoundEventSystem* eventSystem );

		/*! Initializes the System
		*
		*  @return (void)
		*/
		void Initialize( Configuration::IConfiguration* configuration );


		/*! Steps the System's internal data
		*
		*  @param[in] float deltaMilliseconds
		*  @return (void)
		*/
		void Update( float deltaMilliseconds );


		/*! Releases internal data of the System
		*
		*  @return (System::Types::Type)
		*/
		void Release( );


		/*! Messages the system with a command
		*
		* @param[in] const std::string & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		AnyType::AnyTypeMap ProcessMessage( const System::MessageType& message, AnyType::AnyTypeMap parameters );


		/*! Returns the type of the System
		*
		*  @return (System::Types::Type)
		*/
		inline System::Types::Type GetType( ) const { return System::Types::SOUND; };


		/*! Creates a System Scene
		*
		*  @return (ISystemScene*)
		*/
		ISystemScene* CreateScene( );


		/*! Gets the System's Properties
		*
		*  @return (AnyTypeMap)
		*/
		inline AnyType::AnyTypeMap GetAttributes( ) const { return AnyType::AnyTypeMap( ); };


		/*! Sets a System Property
		*
		*  @param[in] const std::string & name
		*  @param[in] AnyType value
		*  @return (void)
		*/
		inline void SetAttribute( const std::string& name, AnyType value ) { };	


		/*! Opens a sound file for FMOD
		*
		* @param[in] const char * name
		* @param[in] int unicode
		* @param[in] unsigned int * filesize
		* @param[in] void * * handle
		* @param[in] void * * userdata
		* @return ( bool )
		*/
		bool FileOpen( const char* name, int unicode, unsigned int* filesize, void** handle, void** userdata );


	private:

		SoundSystem( const SoundSystem & copy ) { };
		SoundSystem & operator = ( const SoundSystem & copy ) { return *this; };

		static ISoundSystem* m_soundSystem;

		FMOD::System* m_fmodSystem;
		ISoundEventSystem* m_eventSystem;
		Configuration::IConfiguration* m_configuration;
		ISoundScene* m_scene;
		Services::IServiceManager* m_serviceManager;
		Resources::IResourceCache* m_resourceCache;

		static FMOD_RESULT F_CALLBACK FMOD_FileOpen( const char* name, int unicode, unsigned int* filesize, void** handle, void** userdata );
		static FMOD_RESULT F_CALLBACK FMOD_FileClose( void* handle, void*  userdata );
		static FMOD_RESULT F_CALLBACK FMOD_FileRead( void* handle, void* buffer, unsigned int sizebytes, unsigned int* bytesread, void* userdata );
		static FMOD_RESULT F_CALLBACK FMOD_FileSeek( void* handle, unsigned int pos, void* userdata );
	};
};

#endif
