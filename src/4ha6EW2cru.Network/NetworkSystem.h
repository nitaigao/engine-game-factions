/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkSystem.h
*  @date   2009/07/06
*/
#pragma once
#ifndef NETWORKSYSTEM_H
#define NETWORKSYSTEM_H

#include "Service/IService.hpp"

#include "INetworkSystem.hpp"
#include "INetworkSystemScene.hpp"
#include "INetworkClientProvider.hpp"

#include "Configuration/IConfiguration.hpp"
#include "Service/IServiceManager.h"

namespace Network
{
	/*! 
	 *  The Network System
	 */
	class NetworkSystem : public INetworkSystem, public Services::IService
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		GAMEAPI ~NetworkSystem( );

		/*! Default Constructor
		*
		* @return (  )
		*/
		GAMEAPI NetworkSystem( Services::IServiceManager* serviceManager );


		/*! IoC Constructor
		*
		* @return (  )
		*/
		GAMEAPI NetworkSystem( Services::IServiceManager* serviceManager, INetworkSystemScene* scene, INetworkClientProvider* clientProvider );


		/*! Initializes the System
		*
		*  @return (void)
		*/
		GAMEAPI void Initialize( Configuration::IConfiguration* configuration );


		/*! Steps the System's internal data
		*
		*  @param[in] float deltaMilliseconds
		*  @return (void)
		*/
		GAMEAPI void Update( float deltaMilliseconds );


		/*! Releases internal data of the System
		*
		*  @return (System::Types::Type)
		*/
		GAMEAPI void Release( );


		/*! Messages the system with a command
		*
		* @param[in] const std::string & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		GAMEAPI AnyType::AnyTypeMap Message( const System::Message& message, AnyType::AnyTypeMap parameters );


		/*! Returns the type of the System
		*
		*  @return (System::Types::Type)
		*/
		GAMEAPI inline System::Types::Type GetType( ) const { return System::Types::NETWORK; };


		/*! Creates a System Scene
		*
		*  @return (ISystemScene*)
		*/
		GAMEAPI ISystemScene* CreateScene( );


		/*! Gets the System's Properties
		*
		*  @return (AnyTypeMap)
		*/
		GAMEAPI inline AnyType::AnyTypeMap GetAttributes( ) const { return m_attributes; };


		/*! Sets a System Property
		*
		*  @param[in] const std::string & name
		*  @param[in] AnyType value
		*  @return (void)
		*/
		GAMEAPI inline void SetAttribute( const std::string& name, AnyType value ) { m_attributes[ name ] = value; };


		/*! Sends a message to a single client across the network
		*
		* @param[in] const std::string & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		GAMEAPI void PushMessage( const SystemAddress& address, const System::Message& message, AnyType::AnyTypeMap parameters );


		/*! Sends a message across the network
		*
		* @param[in] const SystemAddress & networkAddress
		* @param[in] const std::string & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		GAMEAPI void PushMessage( const System::Message& message, AnyType::AnyTypeMap parameters );


		/*! Sends a message to a local component
		*
		* @param[in] const std::string & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		GAMEAPI void MessageComponent( const std::string& componentName, const std::string& message, AnyType::AnyTypeMap parameters );

	private:

		NetworkSystem( const NetworkSystem & copy ) { };
		NetworkSystem & operator = ( const NetworkSystem & copy ) { return *this; };
	
		Configuration::IConfiguration* m_configuration;

		AnyType::AnyTypeMap m_attributes;
		INetworkSystemScene* m_scene;
		Services::IServiceManager* m_serviceManager;
		INetworkClientProvider* m_clientProvider;
		
	};
};

#endif
